"""校准接口: 配准 / X轴定位校准 / 云台校准。

参考 visual_localization 项目的:
  - calibration_window.py (_CalibrationWorker): X轴定位校准逻辑
  - inspection_execution_window.py (_PtzCalibrationWorker): 云台校准迭代逻辑

配准(仅配准不移动):
  调整云台/升降杆 → 抓拍 → ORB配准 → 返回X偏移和配准指标(不移动机器人)

X轴定位校准:
  1. 通过 rid 找到机器人 → 读取 WaypointsTree.json
  2. 根据 node_id 找到航点(若为动作点则向上找第一个航点)
  3. 在航点子树中查找第一个 OrbRegistration 节点
  4. 没有 OrbRegistration → 直接返回成功
  5. 有 → 调整云台/升降杆 → 抓拍 → ORB配准 → 提取X偏移 → 坐标变换 → 移动机器人

云台校准:
  流程类似, 但迭代8次: 抓拍→配准→检查收敛→调整pan/tilt
"""
import base64
import json
import logging
import math
import time
import uuid
from pathlib import Path
from typing import Any, Optional

from fastapi import APIRouter, Depends, HTTPException, Query
from fastapi.responses import FileResponse
from pydantic import BaseModel
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot
from ..auth import engineer_only
from ..config import DATA_DIR
from ..services import robot_api, ssh_client

router = APIRouter(prefix="/api/calibration", tags=["calibration"])
logger = logging.getLogger(__name__)


# ========== 常量 ==========

# 云台pan角方向系数: (起始角度, 结束角度, 系数)
# pan ∈ [0°, 90°]   → +1 (前进)
# pan ∈ [90°, 270°] → -1 (后退)
# pan ∈ [270°, 360°] → +1 (前进)
PAN_DIRECTION_CONFIG = [
    (0, 90, 1),
    (90, 270, -1),
    (270, 360, 1),
]

# 像素→物理距离基础系数 (m/px @ zoom=1x)
BASE_SCALE_M_PER_PX = 0.0005

# 云台校准参数
PTZ_THRESHOLD_PX = 21.0       # 收敛阈值(像素)
PTZ_MAX_ITERATIONS = 8        # 最大迭代次数
PTZ_BASE_PIXEL_TO_DEGREE = 0.03  # 像素→角度转换系数(度/像素 @ zoom=1x)

# ORB 匹配参数 (与 visual_localization 参考代码一致)
ORB_MAX_FEATURES = 4000
ORB_TOP_K = 80
ORB_MIN_MATCHES = 12
ORB_MASK_TOP_RATIO = 0.12
ORB_MASK_BOTTOM_RATIO = 0.18
ORB_LOWE_RATIO = 0.75
ORB_RANSAC_THRESHOLD = 5.0

# X轴校准参数
X_AXIS_THRESHOLD_PX = 15.0       # 收敛阈值(像素): |x_offset| <= 15px 判定成功
X_AXIS_MAX_ITERATIONS = 10       # 最大迭代次数
MIN_MOVE_DISTANCE_M = 0.01       # 最小移动距离(m): 计算距离小于此值时取此值


# ========== 机器人查找 ==========

def _robot_by_rid(rid: int, db: Session) -> Robot:
    """按 robot_id（工控机自身ID）查找，兼容 C++ 调用方传入的 rid 是 robot_id。"""
    # 优先按 robot_id（工控机自身标识）查找
    r = db.query(Robot).filter(Robot.robot_id == rid).first()
    if r:
        return r
    # 兜底按 DB 主键 id 查找（前端调用）
    r = db.query(Robot).filter(Robot.id == rid).first()
    if r:
        return r
    raise HTTPException(404, f"未找到 rid={rid} 的机器人（按 robot_id 和 id 均未匹配）")


def _tree_path(rid: int) -> Path:
    return DATA_DIR / "robot" / str(rid) / "WaypointsTree.json"


# ========== 树遍历 ==========

def _find_node_with_ancestors(tree: dict, node_id: str,
                              ancestors: list = None) -> tuple[Optional[dict], list]:
    """DFS 查找节点, 返回 (node, ancestor_chain)。
    ancestor_chain 从根到直接父节点, 如 [root, waypoint, action_parent]。
    """
    if ancestors is None:
        ancestors = []
    if tree.get("id") == node_id:
        return tree, ancestors
    for child in tree.get("children", []):
        found, chain = _find_node_with_ancestors(child, node_id, ancestors + [tree])
        if found:
            return found, chain
    return None, []


def _find_waypoint_for_node(tree: dict, node_id: str) -> Optional[dict]:
    """根据 node_id 找到对应的航点节点。
    - 如果 node_id 是 WaypointNode, 直接返回
    - 如果是其他类型(如 ActionNode), 向上找第一个 WaypointNode 祖先
    """
    node, ancestors = _find_node_with_ancestors(tree, node_id)
    if node is None:
        return None
    if node.get("nodeType") == "WaypointNode":
        return node
    # 从最近的祖先开始向上找
    for ancestor in reversed(ancestors):
        if ancestor.get("nodeType") == "WaypointNode":
            return ancestor
    return None


def _find_first_orb(node: dict) -> Optional[dict]:
    """在节点的子树中查找第一个 OrbRegistration 节点 (DFS)。"""
    if node.get("nodeType") == "OrbRegistration":
        return node
    for child in node.get("children", []):
        found = _find_first_orb(child)
        if found:
            return found
    return None


# ========== 机器人 API 封装 ==========

def _get_pose(r: Robot) -> Optional[dict]:
    """cmd=30 获取机器人位姿。"""
    t0 = time.time()
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 30, timeout=4.0)
        dt = time.time() - t0
        if code != 0 or not d:
            logger.warning("[get_pose] cmd=30 失败 code=%s msg=%s 耗时=%.2fs ip=%s", code, msg, dt, r.ip)
            return None
        x = d.get("x", 0) or (d.get("point", {}) or {}).get("x", 0)
        y = d.get("y", 0) or (d.get("point", {}) or {}).get("y", 0)
        theta = d.get("theta", 0)
        pose = {"x": float(x), "y": float(y), "theta": float(theta)}
        logger.info("[get_pose] cmd=30 成功 x=%.4f y=%.4f θ=%.2f 耗时=%.2fs", pose["x"], pose["y"], pose["theta"], dt)
        return pose
    except Exception as e:
        logger.warning("[get_pose] cmd=30 异常: %s 耗时=%.2fs ip=%s", e, time.time() - t0, r.ip)
        return None


def _get_ptz(r: Robot) -> Optional[dict]:
    """cmd=35 获取云台位姿。"""
    t0 = time.time()
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 35, timeout=4.0)
        dt = time.time() - t0
        if code != 0 or not d:
            logger.warning("[get_ptz] cmd=35 失败 code=%s msg=%s 耗时=%.2fs ip=%s", code, msg, dt, r.ip)
            return None
        ptz = {
            "pan": float(d.get("pan", 0)),
            "tilt": float(d.get("tilt", 0)),
            "zoom": float(d.get("zoom", 1)),
        }
        logger.info("[get_ptz] cmd=35 成功 pan=%.2f tilt=%.2f zoom=%.2f 耗时=%.2fs",
                    ptz["pan"], ptz["tilt"], ptz["zoom"], dt)
        return ptz
    except Exception as e:
        logger.warning("[get_ptz] cmd=35 异常: %s 耗时=%.2fs ip=%s", e, time.time() - t0, r.ip)
        return None


def _set_ptz(r: Robot, pan: float, tilt: float, zoom: float,
             tolerance: float = 0.1) -> tuple[bool, str]:
    """cmd=36 设置云台位姿（先读当前位姿, 已在容差内则跳过）。"""
    t0 = time.time()
    cur = _get_ptz(r)
    if cur:
        if (abs(cur["pan"] - pan) <= tolerance and
            abs(cur["tilt"] - tilt) <= tolerance and
            abs(cur["zoom"] - zoom) <= 0.1):
            logger.info("[set_ptz] 已在目标位姿 pan=%.2f tilt=%.2f zoom=%.2f 跳过 ip=%s",
                        pan, tilt, zoom, r.ip)
            return True, f"已在目标位姿 (pan={cur['pan']:.2f} tilt={cur['tilt']:.2f})"
    logger.info("[set_ptz] cmd=36 下发 pan=%.4f tilt=%.4f zoom=%.4f (当前 pan=%s tilt=%s) ip=%s",
                pan, tilt, zoom,
                f"{cur['pan']:.2f}" if cur else "?", f"{cur['tilt']:.2f}" if cur else "?",
                r.ip)
    code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 36,
                                  {"pan": pan, "tilt": tilt, "zoom": zoom})
    dt = time.time() - t0
    ok = code == 0
    if ok:
        logger.info("[set_ptz] cmd=36 成功 耗时=%.2fs", dt)
    else:
        logger.warning("[set_ptz] cmd=36 失败 code=%s msg=%s 耗时=%.2fs", code, msg, dt)
    return ok, msg


def _get_lift(r: Robot) -> Optional[float]:
    """cmd=40 获取当前升降杆高度, 失败返回 None。"""
    code, msg, data = robot_api.call(r.ip, r.api_port, r.robot_id, 40)
    if code == 0 and data:
        return float(data.get("height", 0))
    logger.warning("[get_lift] cmd=40 失败 code=%s msg=%s ip=%s", code, msg, r.ip)
    return None


def _set_lift(r: Robot, height: float, tolerance: float = 0.01) -> tuple[bool, str]:
    """cmd=41 升降杆到指定高度（先读当前高度, 已在容差内则跳过）。"""
    t0 = time.time()
    cur = _get_lift(r)
    if cur is not None and abs(cur - height) <= tolerance:
        logger.info("[set_lift] 已在目标高度 cur=%.3f target=%.3f 跳过 ip=%s", cur, height, r.ip)
        return True, f"已在目标高度 ({cur:.3f}m)"
    logger.info("[set_lift] cmd=41 下发 height=%.3f (当前=%.3f) ip=%s",
                height, cur if cur is not None else -1, r.ip)
    code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 41,
                                  {"command": 3, "height": height})
    dt = time.time() - t0
    ok = code == 0
    if ok:
        logger.info("[set_lift] cmd=41 成功 耗时=%.2fs", dt)
    else:
        logger.warning("[set_lift] cmd=41 失败 code=%s msg=%s 耗时=%.2fs", code, msg, dt)
    return ok, msg


def _move_to(r: Robot, x: float, y: float, theta: float,
             pan: float = None, tilt: float = None, zoom: float = None,
             safety_check: bool = False) -> tuple[bool, str]:
    """cmd=31 移动到指定位姿。safety_check=False 保持原行为(校准自管升降杆)。"""
    t0 = time.time()
    payload = {"point": {"x": x, "y": y}, "theta": theta, "safety_check": safety_check}
    if pan is not None:
        payload["ptz"] = {"pan": pan, "tilt": tilt or 0, "zoom": zoom or 0}
    logger.info("[move_to] cmd=31 下发 x=%.4f y=%.4f θ=%.2f ptz=%s ip=%s",
                x, y, theta, payload.get("ptz"), r.ip)
    code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 31, payload)
    dt = time.time() - t0
    ok = code == 0
    if ok:
        logger.info("[move_to] cmd=31 成功 耗时=%.2fs", dt)
    else:
        logger.warning("[move_to] cmd=31 失败 code=%s msg=%s 耗时=%.2fs", code, msg, dt)
    return ok, msg


def _wait_for_arrival(r: Robot, target_x: float, target_y: float,
                      timeout: float = 10.0, tol: float = 0.02) -> tuple[bool, Optional[dict]]:
    """cmd=31 移动后轮询位姿, 等待机器人到位或停下。

    cmd=31 下发后立即返回(机器人仍在移动), 若不等待, 下一轮抓拍/读位姿会
    拿到中间位置 → 欠执行。这里轮询 cmd=30 位姿, 满足任一条件即返回:
      ① 到位: |cur - target| < tol
      ② 停下: 连续 2 次位置变化 < 0.005m (机器人因死区到位后停住)
      ③ 超时: timeout 秒
    """
    t0 = time.time()
    time.sleep(0.5)  # 给机器人起步时间, 避免读到移动前的旧位置
    last = None
    stable_count = 0
    pose = None
    while time.time() - t0 < timeout:
        pose = _get_pose(r)
        if pose is None:
            time.sleep(0.3)
            continue
        # ① 到位
        if abs(pose["x"] - target_x) < tol and abs(pose["y"] - target_y) < tol:
            logger.info("[wait_arrival] 已到位 x=%.4f y=%.4f (目标 %.4f,%.4f) 耗时=%.2fs",
                        pose["x"], pose["y"], target_x, target_y, time.time() - t0)
            return True, pose
        # ② 停下(位置不再变化)
        if last and abs(pose["x"] - last["x"]) < 0.005 and abs(pose["y"] - last["y"]) < 0.005:
            stable_count += 1
            if stable_count >= 2:
                logger.info("[wait_arrival] 已停下 x=%.4f y=%.4f (距目标 dx=%.4f dy=%.4f) 耗时=%.2fs",
                            pose["x"], pose["y"], pose["x"] - target_x,
                            pose["y"] - target_y, time.time() - t0)
                return True, pose
        else:
            stable_count = 0
        last = pose
        time.sleep(0.3)
    logger.warning("[wait_arrival] 超时 末次 x=%.4f y=%.4f (距目标 dx=%.4f) 耗时=%.2fs",
                   pose["x"] if pose else 0, pose["y"] if pose else 0,
                   (pose["x"] - target_x) if pose else 0, time.time() - t0)
    return False, pose


def _wait_for_ptz(r: Robot, target_pan: float, target_tilt: float, target_zoom: float,
                  timeout: float = 20.0, poll_interval: float = 0.1,
                  tol: float = 0.1) -> bool:
    """轮询等待云台到位。连续2次稳定即认为到位。"""
    t0 = time.time()
    logger.info("[wait_ptz] 等待云台到位 target=(pan=%.2f tilt=%.2f zoom=%.2f) timeout=%.0fs",
                target_pan, target_tilt, target_zoom, timeout)
    stable_count = 0
    last_ptz = None
    while time.time() - t0 < timeout:
        ptz = _get_ptz(r)
        if ptz:
            last_ptz = ptz
            pan_ok = abs(ptz["pan"] - target_pan) < tol
            tilt_ok = abs(ptz["tilt"] - target_tilt) < tol
            zoom_ok = abs(ptz["zoom"] - target_zoom) < 0.1
            if pan_ok and tilt_ok and zoom_ok:
                stable_count += 1
                if stable_count >= 2:
                    dt = time.time() - t0
                    logger.info("[wait_ptz] 已到位 耗时=%.2fs pan=%.2f tilt=%.2f zoom=%.2f",
                                dt, ptz["pan"], ptz["tilt"], ptz["zoom"])
                    return True
            else:
                stable_count = 0
        time.sleep(poll_interval)
    dt = time.time() - t0
    logger.warning("[wait_ptz] 超时(%.0fs) 未到位 当前=%s", dt, last_ptz or "无数据")
    return False


# ========== 图像获取 ==========

def _capture_image(r: Robot, timeout: float = 5.0):
    """从机器人 RTSP 子码流(H.264)抓取一帧, 返回 (cv2_image, error_msg)。
    用 ffmpeg subprocess 抓帧(tcp传输, 硬超时), 比 OpenCV VideoCapture 更可靠。
    """
    import cv2, subprocess, numpy as np

    if not r.ip:
        return None, "未配置机器人 IP"

    t0 = time.time()
    # 可见光子码流 (Channels/102=通道1子码流), ffmpeg 可解 HEVC/H.264
    rtsp_url = f"rtsp://admin:hxzh2019@{r.ip}:554/Streaming/Channels/102"
    logger.info("[capture] RTSP 抓帧(ffmpeg) ip=%s timeout=%.1fs", r.ip, timeout)

    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-rtsp_transport", "tcp",
        "-i", rtsp_url,
        "-vframes", "1", "-f", "image2pipe", "-vcodec", "mjpeg", "-",
    ]
    try:
        proc = subprocess.run(cmd, capture_output=True, timeout=timeout)
        dt = time.time() - t0
        if proc.returncode != 0 or len(proc.stdout) < 1000:
            err_msg = proc.stderr.decode(errors="replace")[-200:] if proc.stderr else "无输出"
            logger.warning("[capture] ffmpeg 失败 rc=%d 耗时=%.2fs ip=%s stderr=%s",
                          proc.returncode, dt, r.ip, err_msg)
            return None, f"RTSP 抓帧失败(ffmpeg rc={proc.returncode})"
        arr = np.frombuffer(proc.stdout, np.uint8)
        frame = cv2.imdecode(arr, cv2.IMREAD_COLOR)
        if frame is None:
            logger.warning("[capture] ffmpeg 输出无法解码 耗时=%.2fs ip=%s", dt, r.ip)
            return None, "RTSP 抓帧解码失败"
        logger.info("[capture] 抓帧成功 shape=%s 耗时=%.2fs ip=%s", frame.shape, dt, r.ip)
        return frame, None
    except subprocess.TimeoutExpired:
        dt = time.time() - t0
        logger.warning("[capture] RTSP 抓帧超时(>%.1fs) ip=%s 耗时=%.2fs", timeout, r.ip, dt)
        return None, f"RTSP 抓帧超时(>{timeout:.0f}s)"
    except Exception as e:
        dt = time.time() - t0
        logger.warning("[capture] RTSP 抓帧异常: %s 耗时=%.2fs ip=%s", e, dt, r.ip)
        return None, f"RTSP 抓帧异常: {e}"


def _load_ref_image(rid: int, ref_image_url: str):
    """加载 ORB 参考图。ref_image_url 如 'navRefImg/xxx.jpg'。"""
    import cv2

    t0 = time.time()
    ref_path = DATA_DIR / "robot" / str(rid) / ref_image_url
    if not ref_path.exists():
        logger.warning("[load_ref] 参考图不存在: %s rid=%d", ref_path, rid)
        return None, f"参考图不存在: {ref_path}"
    img = cv2.imread(str(ref_path))
    if img is None:
        logger.warning("[load_ref] 参考图读取失败: %s rid=%d", ref_path, rid)
        return None, f"参考图读取失败: {ref_path}"
    logger.info("[load_ref] 参考图加载成功 path=%s shape=%s 耗时=%.2fs",
                ref_path, img.shape, time.time() - t0)
    return img, None


# ========== ORB 配准 ==========

def _create_top_bottom_mask(shape, top_ratio: float, bottom_ratio: float):
    """创建上下掩膜: 顶部和底部按比例置零。"""
    import numpy as np
    h, w = shape[:2]
    mask = np.ones((h, w), dtype=np.uint8) * 255
    if top_ratio > 0:
        mask[:int(h * top_ratio), :] = 0
    if bottom_ratio > 0:
        mask[int(h * (1 - bottom_ratio)):, :] = 0
    return mask


def _draw_mask_overlay(img, mask):
    """在图片上半透明叠加掩膜区域(蓝色覆盖被掩膜的区域)。"""
    import numpy as np
    overlay = img.copy()
    color = np.array([255, 100, 0], dtype=np.uint8)  # 蓝色
    masked_region = mask == 0
    overlay[masked_region] = (overlay[masked_region] * 0.5 + color * 0.5).astype(np.uint8)
    return overlay


def _draw_reference_outline(ref_img, cur_img, H):
    """在当前图上绘制参考图四角变换后的轮廓。"""
    import cv2
    import numpy as np
    h, w = ref_img.shape[:2]
    corners = np.float32([[0, 0], [w, 0], [w, h], [0, h]]).reshape(-1, 1, 2)
    if H is not None:
        transformed = cv2.perspectiveTransform(corners, H)
        result = cur_img.copy()
        pts = np.int32(transformed.reshape(-1, 2))
        cv2.polylines(result, [pts], True, (0, 255, 0), 2)
        return result
    return cur_img.copy()


def _warp_and_blend(ref_img, cur_img, H):
    """将参考图变换到当前图视角, 返回 (变换后图, 叠加图)。"""
    import cv2
    import numpy as np
    h, w = cur_img.shape[:2]
    if H is None:
        return ref_img.copy(), cv2.addWeighted(ref_img, 0.5, cur_img, 0.5, 0)
    warped = cv2.warpPerspective(ref_img, H, (w, h))
    blended = cv2.addWeighted(warped, 0.5, cur_img, 0.5, 0)
    return warped, blended


def _run_orb_matching(ref_img, cur_img, output_dir: str = None) -> dict:
    """ORB 特征匹配, 返回仿射矩阵(3x3齐次)和配准指标。

    使用 estimateAffinePartial2D 估计部分仿射变换(平移+旋转+等比缩放, 4 DOF),
    比 findHomography(8 DOF) 更适合轨道机器人校准场景(偏移以平移为主)。

    参考 orb_homography_registration.py 的 detect_match_estimate:
      - max_features=4000, top_k=80, min_matches=12
      - mask_top_ratio=0.12, mask_bottom_ratio=0.18
      - Lowe's ratio=0.75, RANSAC threshold=5.0
      - 重复匹配点检测: 若存在重复点, 交换两图重新匹配后再估计

    返回的 homography 为 3x3 齐次矩阵(最后一行 [0,0,1]),
    后续 perspectiveTransform / warpPerspective 无需改动。
    H[0][2] 和 H[1][2] 分别为 X、Y 方向平移(像素)。

    如果提供 output_dir, 会生成可视化图片并返回图片文件名列表:
      ref_mask, cur_mask, ref_keypoints, cur_keypoints,
      matches, reference_outline, warped_reference, blended
    """
    import cv2
    import numpy as np
    import os

    t0 = time.time()

    # 尺寸不一致时缩放参考图到当前帧尺寸
    ref_h, ref_w = ref_img.shape[:2]
    cur_h, cur_w = cur_img.shape[:2]
    if (ref_w, ref_h) != (cur_w, cur_h):
        ref_img = cv2.resize(ref_img, (cur_w, cur_h), interpolation=cv2.INTER_AREA)

    ref_gray = cv2.cvtColor(ref_img, cv2.COLOR_BGR2GRAY)
    cur_gray = cv2.cvtColor(cur_img, cv2.COLOR_BGR2GRAY)

    ref_mask = _create_top_bottom_mask(ref_img.shape, ORB_MASK_TOP_RATIO, ORB_MASK_BOTTOM_RATIO)
    cur_mask = _create_top_bottom_mask(cur_img.shape, ORB_MASK_TOP_RATIO, ORB_MASK_BOTTOM_RATIO)

    # 生成掩膜叠加图
    debug_images = {}

    def _save_debug_images() -> list[str]:
        """将已生成的 debug_images 保存到 output_dir, 返回文件名列表。"""
        if not output_dir or not debug_images:
            return []
        os.makedirs(output_dir, exist_ok=True)
        name_map = {
            "ref_mask": "00_ref_mask.jpg",
            "cur_mask": "00_cur_mask.jpg",
            "ref_keypoints": "01_ref_keypoints.jpg",
            "cur_keypoints": "01_cur_keypoints.jpg",
            "matches": "02_matches.jpg",
            "reference_outline": "03_reference_outline.jpg",
            "warped_reference": "04_warped_reference.jpg",
            "blended": "05_blended.jpg",
        }
        files = []
        for key, fname in name_map.items():
            if key in debug_images:
                fpath = os.path.join(output_dir, fname)
                cv2.imwrite(fpath, debug_images[key])
                files.append(fname)
        return files

    if output_dir:
        ref_mask_overlay = _draw_mask_overlay(ref_img, ref_mask)
        cur_mask_overlay = _draw_mask_overlay(cur_img, cur_mask)
        debug_images["ref_mask"] = ref_mask_overlay
        debug_images["cur_mask"] = cur_mask_overlay

    # ORB 特征提取
    logger.info("[orb] 开始 ORB 特征提取 max_features=%d", ORB_MAX_FEATURES)
    orb = cv2.ORB_create(nfeatures=ORB_MAX_FEATURES)
    ref_kp, ref_des = orb.detectAndCompute(ref_gray, ref_mask)
    cur_kp, cur_des = orb.detectAndCompute(cur_gray, cur_mask)
    logger.info("[orb] 特征点: ref=%d cur=%d 耗时=%.2fs",
                len(ref_kp) if ref_kp else 0, len(cur_kp) if cur_kp else 0, time.time() - t0)

    if ref_des is None or cur_des is None:
        logger.warning("[orb] 特征点提取失败 ref_des=%s cur_des=%s", ref_des is not None, cur_des is not None)
        return {"homography": None, "total_matches": 0, "inlier_count": 0,
                "error": "特征点提取失败", "debug_images": _save_debug_images()}

    if len(ref_kp) < ORB_MIN_MATCHES or len(cur_kp) < ORB_MIN_MATCHES:
        logger.warning("[orb] 特征点不足 ref=%d cur=%d (要求≥%d)",
                       len(ref_kp), len(cur_kp), ORB_MIN_MATCHES)
        return {"homography": None, "total_matches": 0, "inlier_count": 0,
                "ref_keypoints": len(ref_kp) if ref_kp else 0,
                "cur_keypoints": len(cur_kp) if cur_kp else 0,
                "error": "特征点不足", "debug_images": _save_debug_images()}

    # 生成特征点图
    if output_dir:
        ref_kp_img = cv2.drawKeypoints(ref_mask_overlay, ref_kp, None,
                                        color=(0, 255, 0),
                                        flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        cur_kp_img = cv2.drawKeypoints(cur_mask_overlay, cur_kp, None,
                                        color=(0, 255, 0),
                                        flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        debug_images["ref_keypoints"] = ref_kp_img
        debug_images["cur_keypoints"] = cur_kp_img

    # BFMatcher + Lowe's ratio test + top-k 过滤
    def _match_and_filter(des1, des2):
        bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=False)
        raw = bf.knnMatch(des1, des2, k=2)
        good = []
        for m_n in raw:
            if len(m_n) == 2:
                m, n = m_n
                if m.distance < ORB_LOWE_RATIO * n.distance:
                    good.append(m)
        if len(good) > ORB_TOP_K:
            good = sorted(good, key=lambda x: x.distance)[:ORB_TOP_K]
        return good

    good_matches = _match_and_filter(ref_des, cur_des)
    logger.info("[orb] 匹配: good=%d (top_k=%d)", len(good_matches), ORB_TOP_K)

    if len(good_matches) < ORB_MIN_MATCHES:
        logger.warning("[orb] 有效匹配点不足: %d < %d", len(good_matches), ORB_MIN_MATCHES)
        return {"homography": None, "total_matches": len(good_matches),
                "inlier_count": 0, "error": "有效匹配点不足", "debug_images": _save_debug_images()}

    # 重复匹配点检测: 若多个匹配指向同一特征点, 交换两图重新匹配后反转方向
    # (参考 orb_homography_registration.py 的 detect_match_estimate)
    def _has_duplicate_points(matches):
        qids, tids = set(), set()
        for m in matches:
            if m.queryIdx in qids or m.trainIdx in tids:
                return True
            qids.add(m.queryIdx)
            tids.add(m.trainIdx)
        return False

    if _has_duplicate_points(good_matches):
        # 跳过重复点交换 — 改用 estimateAffinePartial2D 直接处理
        logger.info("[orb] 检测到重复匹配点(%d个), 信任RANSAC过滤", len(good_matches))

    # estimateAffinePartial2D: 部分仿射(平移+旋转+等比缩放, 4 DOF)
    # 轨道机器人校准偏移以平移为主, 比 findHomography(8 DOF) 更稳健
    src_pts = np.float32([ref_kp[m.queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
    dst_pts = np.float32([cur_kp[m.trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)
    affine, inlier_mask = cv2.estimateAffinePartial2D(
        src_pts, dst_pts, method=cv2.RANSAC, ransacReprojThreshold=ORB_RANSAC_THRESHOLD)
    if affine is None or inlier_mask is None:
        logger.warning("[orb] estimateAffinePartial2D 估计失败 matches=%d", len(good_matches))
        return {"homography": None, "total_matches": len(good_matches),
                "inlier_count": 0, "error": "仿射变换估计失败", "debug_images": _save_debug_images()}
    # 2x3 仿射矩阵 → 3x3 齐次形式, 后续 perspectiveTransform / warpPerspective 兼容
    H = np.vstack([affine, [0.0, 0.0, 1.0]])
    inlier_count = int(inlier_mask.sum())
    dt = time.time() - t0
    logger.info("[orb] 配准成功 matches=%d inliers=%d H[0][2]=%.4f H[1][2]=%.4f 总耗时=%.2fs",
                len(good_matches), inlier_count, float(H[0][2]), float(H[1][2]), dt)

    # 生成匹配结果图、参考轮廓图、变换叠加图
    if output_dir and H is not None:
        # 匹配结果图 (只画内点)
        match_img = cv2.drawMatches(
            ref_img, ref_kp, cur_img, cur_kp, good_matches, None,
            matchColor=(0, 255, 0), singlePointColor=(255, 0, 0),
            matchesMask=inlier_mask.ravel().tolist(),
            flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS,
        )
        debug_images["matches"] = match_img

        # 参考轮廓映射图
        outline_img = _draw_reference_outline(ref_img, cur_img, H)
        debug_images["reference_outline"] = outline_img

        # 变换后参考图 + 叠加图
        warped_img, blended_img = _warp_and_blend(ref_img, cur_img, H)
        debug_images["warped_reference"] = warped_img
        debug_images["blended"] = blended_img

    debug_files = _save_debug_images()

    return {
        "homography": H.tolist() if H is not None else None,
        "total_matches": len(good_matches),
        "inlier_count": inlier_count,
        "debug_images": debug_files,
    }


# ========== 方向系数 ==========

def _get_pan_coef(pan_deg: float) -> float:
    """根据云台pan角度查配置表返回方向系数。"""
    norm_pan = pan_deg % 360.0
    for lo, hi, coef in PAN_DIRECTION_CONFIG:
        if lo <= norm_pan < hi:
            return float(coef)
    return 1.0


# ========== 请求模型 ==========

class CalibIn(BaseModel):
    rid: int              # 机器人 PK
    node_id: str          # 航点或动作点 ID
    inspection_id: Optional[str] = None  # 巡检ID, 用于关联校准数据到巡检


# ========== 共享: 查找航点和ORB节点 ==========

def _resolve_waypoint_and_orb(r: Robot, node_id: str) -> tuple[dict, dict]:
    """通用流程: 从 WaypointsTree.json 中找到航点和第一个 OrbRegistration 节点。

    返回 (waypoint_node, orb_node)。
    如果 OrbRegistration 不存在, orb_node 返回 None。
    """
    t0 = time.time()
    p = _tree_path(r.id)
    if not p.exists():
        logger.warning("[resolve_wp_orb] 航点树不存在 rid=%d", r.id)
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    wp = _find_waypoint_for_node(tree, node_id)
    if wp is None:
        logger.warning("[resolve_wp_orb] 未找到节点 %s 对应的航点 rid=%d", node_id, r.id)
        raise HTTPException(404, f"未找到节点 {node_id} 对应的航点")

    orb_node = _find_first_orb(wp)
    logger.info("[resolve_wp_orb] rid=%d node_id=%s waypoint=%s orb=%s 耗时=%.2fs",
                r.id, node_id, wp.get("name", ""), orb_node is not None, time.time() - t0)
    return wp, orb_node


def _resolve_action_node(r: Robot, node_id: str) -> dict:
    """从 WaypointsTree.json 中找到 node_id 对应的动作点节点本身。

    云台校准使用动作点自身的 snap_shot_url 作为参考图,
    不需要查找 OrbRegistration 节点。
    """
    t0 = time.time()
    p = _tree_path(r.id)
    if not p.exists():
        logger.warning("[resolve_action] 航点树不存在 rid=%d", r.id)
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    node, _ancestors = _find_node_with_ancestors(tree, node_id)
    if node is None:
        logger.warning("[resolve_action] 未找到节点 %s rid=%d", node_id, r.id)
        raise HTTPException(404, f"未找到节点 {node_id}")
    if node.get("nodeType") != "ActionNode":
        logger.warning("[resolve_action] 节点 %s 不是动作点 nodeType=%s rid=%d",
                       node_id, node.get("nodeType"), r.id)
        raise HTTPException(400, f"节点 {node_id} 不是动作点 (nodeType={node.get('nodeType')})")
    logger.info("[resolve_action] rid=%d node_id=%s name=%s snap_shot_url=%s 耗时=%.2fs",
                r.id, node_id, node.get("name", ""), node.get("snap_shot_url", ""), time.time() - t0)
    return node


def _load_image_from_url(rid: int, url: str, cache_key: str = None):
    """加载参考图, 兼容多种 URL 格式:
      - 相对路径 'navRefImg/xxx.jpg' → data/robot/{rid}/navRefImg/xxx.jpg
      - 完整 HTTP URL → httpx 下载; 若有 cache_key 则缓存到 actionRefImg/
      - /api/waypoint-tree/{rid}/ref-image/xxx.jpg → 提取文件名后走本地路径
    """
    import cv2
    import numpy as np

    t0 = time.time()
    if not url:
        logger.warning("[load_img] 参考图 URL 为空 rid=%d", rid)
        return None, "参考图 URL 为空"

    # 完整 HTTP URL: 下载后解码
    if url.startswith("http://") or url.startswith("https://"):
        # 本地缓存: actionRefImg/{cache_key}.jpg
        if cache_key:
            cache_dir = DATA_DIR / "robot" / str(rid) / "actionRefImg"
            cache_dir.mkdir(parents=True, exist_ok=True)
            cache_path = cache_dir / f"{cache_key}.jpg"
            if cache_path.exists():
                img = cv2.imread(str(cache_path))
                if img is not None:
                    logger.info("[load_img] 缓存命中 cache=%s shape=%s 耗时=%.2fs rid=%d",
                                cache_path.name, img.shape, time.time() - t0, rid)
                    return img, None
                logger.warning("[load_img] 缓存文件损坏, 重新下载: %s", cache_path)

        import httpx
        try:
            resp = httpx.get(url, timeout=10.0)
            if resp.status_code != 200 or not resp.content:
                logger.warning("[load_img] HTTP下载失败 status=%d url=%s rid=%d", resp.status_code, url, rid)
                return None, f"下载图片失败: HTTP {resp.status_code}"
            arr = np.frombuffer(resp.content, np.uint8)
            img = cv2.imdecode(arr, cv2.IMREAD_COLOR)
            if img is None:
                logger.warning("[load_img] HTTP下载的数据无法解码 url=%s rid=%d", url, rid)
                return None, "下载的数据无法解码为图像"
            logger.info("[load_img] HTTP下载成功 url=%s shape=%s 耗时=%.2fs rid=%d",
                        url, img.shape, time.time() - t0, rid)
            # 保存到本地缓存
            if cache_key:
                cv2.imwrite(str(cache_path), img)
                logger.info("[load_img] 已缓存到 %s", cache_path)
            return img, None
        except Exception as e:
            logger.warning("[load_img] HTTP下载异常: %s url=%s rid=%d 耗时=%.2fs", e, url, rid, time.time() - t0)
            return None, f"下载图片异常: {e}"

    # /api/waypoint-tree/{rid}/ref-image/{filename} → 提取 filename 走本地
    if "/ref-image/" in url:
        filename = url.split("/ref-image/")[-1].split("?")[0]
        url = f"navRefImg/{filename}"

    # 相对路径: data/robot/{rid}/{url}
    ref_path = DATA_DIR / "robot" / str(rid) / url
    if not ref_path.exists():
        logger.warning("[load_img] 参考图不存在: %s rid=%d", ref_path, rid)
        return None, f"参考图不存在: {ref_path}"
    img = cv2.imread(str(ref_path))
    if img is None:
        logger.warning("[load_img] 参考图读取失败: %s rid=%d", ref_path, rid)
        return None, f"参考图读取失败: {ref_path}"
    logger.info("[load_img] 本地参考图加载成功 path=%s shape=%s 耗时=%.2fs rid=%d",
                ref_path, img.shape, time.time() - t0, rid)
    return img, None


def _adjust_ptz_and_lift(r: Robot, orb_node: dict, steps: list) -> dict:
    """调整云台和升降杆到 OrbRegistration 节点记录的位姿。返回当前PTZ位姿。"""
    t0 = time.time()
    ptz = orb_node.get("ptz", {})
    pan = float(ptz.get("pan", 0))
    tilt = float(ptz.get("tilt", 0))
    zoom = float(ptz.get("zoom", 1))
    lift_height = float(orb_node.get("lift_height", 0))
    logger.info("[adjust_ptz_lift] 开始 pan=%.2f tilt=%.2f zoom=%.2f lift=%.3f ip=%s",
                pan, tilt, zoom, lift_height, r.ip)

    steps.append(f"调整云台: pan={pan:.2f}° tilt={tilt:.2f}° zoom={zoom:.2f}x")
    ok, msg = _set_ptz(r, pan, tilt, zoom)
    steps.append(f"  云台指令 (cmd=36): {'成功' if ok else '失败'} {msg}")

    if lift_height > 0:
        steps.append(f"调整升降杆: height={lift_height:.3f}m")
        ok, msg = _set_lift(r, lift_height)
        steps.append(f"  升降杆指令 (cmd=41): {'成功' if ok else '失败'} {msg}")

    # 等待云台到位
    arrived = _wait_for_ptz(r, pan, tilt, zoom)
    steps.append(f"云台到位: {'已到位' if arrived else '超时,继续'}")

    # 读取当前 PTZ 位姿
    cur_ptz = _get_ptz(r) or {"pan": pan, "tilt": tilt, "zoom": zoom}
    logger.info("[adjust_ptz_lift] 完成 耗时=%.2fs cur_ptz=%s", time.time() - t0, cur_ptz)
    return cur_ptz


# ========== 调试图片管理 ==========

def _calib_data_dir(rid: int, inspection_id: str = None) -> Path:
    """校准数据根目录: 
    - 有 inspection_id → data/robot/{rid}/inspection/{inspection_id}/
    - 无 → data/robot/{rid}/calib_debug/ (兼容手动调试)
    """
    if inspection_id:
        return DATA_DIR / "robot" / str(rid) / "inspection" / inspection_id
    return DATA_DIR / "robot" / str(rid) / "calib_debug"


def _calib_debug_base(rid: int) -> Path:
    """兼容旧接口。"""
    return _calib_data_dir(rid)


def _debug_single_dir(rid: int, node_id: str, inspection_id: str = None) -> Path:
    """单次调试目录: {base}/single/wps_{node_id}/"""
    safe = node_id.replace("/", "_")[:32]
    d = _calib_data_dir(rid, inspection_id) / "single" / f"wps_{safe}"
    if d.exists():
        import shutil; shutil.rmtree(d)
    d.mkdir(parents=True, exist_ok=True)
    return d


def _debug_multiple_dir(rid: int, wps_id: str, node_id: str,
                        suffix: str = "", inspection_id: str = None) -> Path:
    """迭代调试目录: {base}/multiple/wps_{wps_id}/{node_id}_{suffix}/"""
    safe_wps = wps_id.replace("/", "_")[:32]
    safe_node = node_id.replace("/", "_")[:32]
    name = safe_node + ("_" + suffix if suffix else "")
    d = _calib_data_dir(rid, inspection_id) / "multiple" / f"wps_{safe_wps}" / name
    if d.exists():
        import shutil; shutil.rmtree(d)
    d.mkdir(parents=True, exist_ok=True)
    return d


def _save_iteration(iter_dir: Path, iteration: int, steps: list, debug_images: list):
    """保存一次迭代的过程图和日志到 iter_dir/{iteration}/ (复制, 保留根目录供前端直接访问)。"""
    sub = iter_dir / str(iteration)
    sub.mkdir(parents=True, exist_ok=True)
    # 保存步骤日志
    (sub / "steps.txt").write_text("\n".join(steps), encoding="utf-8")
    # 复制过程图到子目录(保留根目录的原文件, 前端直接引用根目录)
    import shutil
    for fname in debug_images:
        src = iter_dir / fname
        if src.exists():
            shutil.copy2(str(src), str(sub / fname))
    return str(sub.relative_to(iter_dir))


@router.get("/debug-image/{rid}/{path:path}")
def get_debug_image(rid: int, path: str):
    """提供校准调试图片。支持 calib_debug/ 和 inspection/{id}/ 路径。"""
    if ".." in path:
        raise HTTPException(400, "非法路径")
    # 先查 inspection 目录, 再查 calib_debug
    insp_base = DATA_DIR / "robot" / str(rid) / "inspection"
    fpath = insp_base / path
    if not fpath.exists():
        fpath = _calib_debug_base(rid) / path
    if not fpath.exists() or not fpath.is_file():
        raise HTTPException(404, "图片不存在")
    mt = "image/png" if fpath.suffix == ".png" else "image/jpeg"
    return FileResponse(str(fpath), media_type=mt)


@router.get("/debug-sessions/{rid}")
def list_debug_sessions(rid: int, include_inspection: bool = Query(False),
                        node_id: str = Query(None, description="按节点ID过滤(前12位匹配)"),
                        db: Session = Depends(get_db)):
    """列出机器人的调试会话。node_id 提供时只查匹配目录(快)。"""
    _robot_by_rid(rid, db)

    def _collect_files(d: Path, files: list, prefix: str = ""):
        for child in sorted(d.iterdir()):
            rel = f"{prefix}/{child.name}" if prefix else child.name
            if child.is_file() and child.suffix in ('.jpg', '.png', '.txt'):
                files.append(rel)
            elif child.is_dir():
                _collect_files(child, files, rel)

    all_files: list[str] = []
    metrics_map: dict[str, dict] = {}

    base_dirs = [_calib_debug_base(rid)]
    if include_inspection:
        base_dirs.append(DATA_DIR / "robot" / str(rid) / "inspection")

    # 如果有 node_id, 精准定位到具体目录(跳过全局扫描)
    if node_id:
        prefix = node_id[:12]
        for base_dir in base_dirs:
            if not base_dir.exists():
                continue
            base = base_dir / "multiple"
            if not base.exists():
                continue
            for wps_dir in sorted(base.iterdir()):
                if not wps_dir.is_dir(): continue
                for sess_dir in sorted(wps_dir.iterdir()):
                    if not sess_dir.is_dir(): continue
                    if prefix not in sess_dir.name:
                        continue
                    # 找到匹配目录
                    rel = str(sess_dir.relative_to(base_dir))
                    mf = sess_dir / "metrics.json"
                    if mf.exists():
                        try:
                            metrics_map[rel] = json.loads(mf.read_text(encoding="utf-8"))
                        except Exception:
                            pass
                    _collect_files(sess_dir, all_files, rel)
        return {"files": all_files, "metrics": metrics_map}

    # 无 node_id: 全局扫描(兼容旧行为)
    def _walk_dir(d: Path, depth=0):
        if depth > 5: return None
        if d.is_file(): return d.name
        result = {}
        for child in sorted(d.iterdir()):
            v = _walk_dir(child, depth + 1)
            if v is not None:
                result[child.name] = v
        return result if result else None

    all_tree: dict = {}
    for base_dir in base_dirs:
        if not base_dir.exists():
            continue
        tree = _walk_dir(base_dir)
        if tree:
            all_tree.update(tree)
        _collect_files(base_dir, all_files, "")
        for mf in base_dir.rglob("metrics.json"):
            try:
                rel = str(mf.parent.relative_to(base_dir))
                metrics_map[rel] = json.loads(mf.read_text(encoding="utf-8"))
            except Exception:
                pass

    return {
        "sessions": all_tree,
        "files": all_files,
        "metrics": metrics_map,
    }


# ========== 移动到航点位置 ==========

@router.post("/move-to-waypoint")
def move_to_waypoint(body: CalibIn, db: Session = Depends(get_db),
                     _=Depends(engineer_only)):
    """移动机器人到航点记录的坐标位姿。

    读取 WaypointsTree.json 中航点的 pose, 控制机器人移动到该坐标。
    移动时保持当前云台位姿不变。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    t0 = time.time()
    logger.info("[move_to_wp] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    p = _tree_path(r.id)
    if not p.exists():
        logger.warning("[move_to_wp] 航点树不存在 rid=%d", r.id)
        raise HTTPException(404, "航点树不存在")
    tree = json.loads(p.read_text(encoding="utf-8"))

    wp = _find_waypoint_for_node(tree, body.node_id)
    if wp is None:
        logger.warning("[move_to_wp] 未找到节点 %s 对应的航点 rid=%d", body.node_id, r.id)
        raise HTTPException(404, f"未找到节点 {body.node_id} 对应的航点")

    wp_name = wp.get("name", "")
    pose = wp.get("pose", {})
    pt = pose.get("point", {})
    target_x = float(pt.get("x", 0))
    target_y = float(pt.get("y", 0))
    target_theta = float(pose.get("theta", 0))

    steps.append(f"航点: {wp_name} (ID: {wp.get('id', '')[:16]}…)")
    steps.append(f"目标位姿: x={target_x:.4f} y={target_y:.4f} θ={target_theta:.2f}°")

    # 读取当前云台位姿(移动时保持)
    cur_ptz = _get_ptz(r)
    if cur_ptz:
        steps.append(f"保持云台: pan={cur_ptz['pan']:.2f}° tilt={cur_ptz['tilt']:.2f}° zoom={cur_ptz['zoom']:.2f}x")
    else:
        cur_ptz = {"pan": 0, "tilt": 0, "zoom": 0}

    ok, msg = _move_to(r, target_x, target_y, target_theta,
                       pan=cur_ptz["pan"], tilt=cur_ptz["tilt"], zoom=cur_ptz["zoom"])
    steps.append(f"移动指令 (cmd=31): {'成功' if ok else '失败'} {msg}")

    logger.info("[move_to_wp] 出口 ok=%s 总耗时=%.2fs", ok, time.time() - t0)
    return {
        "ok": ok,
        "message": f"移动到 ({target_x:.4f}, {target_y:.4f}, θ={target_theta:.2f}°)" if ok else msg,
        "steps": steps,
    }


# ========== 配准(仅配准不移动) ==========

@router.post("/register")
def register_only(body: CalibIn, db: Session = Depends(get_db),
                  _=Depends(engineer_only)):
    """仅执行配准(不移动机器人)。

    流程:
      1. 调整云台/升降杆到 OrbRegistration 节点位姿
      2. 抓拍当前图
      3. ORB 配准, 提取 X 偏移和配准指标
      4. 返回结果(不移动机器人)

    用于逐步调试: 先配准查看偏移量, 再决定是否执行定位校准。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    t0 = time.time()
    logger.info("[register] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    # 查找航点和ORB节点
    try:
        wp, orb_node = _resolve_waypoint_and_orb(r, body.node_id)
    except HTTPException as e:
        logger.warning("[register] 解析航点失败 rid=%d node_id=%s err=%s", body.rid, body.node_id, e.detail)
        return {"ok": False, "registered": False,
                "message": f"配准失败: {e.detail} (node_id={body.node_id})", "steps": steps}
    wp_name = wp.get("name", "")
    steps.append(f"航点: {wp_name} (ID: {wp.get('id', '')[:16]}…)")

    if orb_node is None:
        steps.append("未找到 OrbRegistration 节点")
        logger.info("[register] 无ORB配准节点, 直接返回 总耗时=%.2fs", time.time() - t0)
        return {"ok": True, "registered": False,
                "message": "无ORB配准节点", "steps": steps}

    ref_url = orb_node.get("refImageUrl", "")
    steps.append(f"ORB配准节点: refImageUrl={ref_url}")

    # 1. 调整云台和升降杆
    steps.append("── 调整云台/升降杆 ──")
    cur_ptz = _adjust_ptz_and_lift(r, orb_node, steps)

    # 2. 抓拍当前图
    steps.append("── 抓拍当前图 ──")
    cur_img, err = _capture_image(r)
    if cur_img is None:
        logger.warning("[register] 抓拍失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "registered": False, "message": err, "steps": steps}
    steps.append("抓拍成功")

    # 3. 加载参考图
    ref_img, err = _load_ref_image(r.id, ref_url)
    if ref_img is None:
        logger.warning("[register] 参考图加载失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "registered": False, "message": err, "steps": steps}
    steps.append("参考图加载成功")

    # 4. ORB 配准
    steps.append("── ORB 配准 ──")
    output_dir = str(_debug_single_dir(r.id, wp.get("id", ""), body.inspection_id))
    
    result = _run_orb_matching(ref_img, cur_img, output_dir)
    debug_images = result.get("debug_images", [])
    if result.get("homography") is None:
        steps.append(f"ORB配准失败: {result.get('error', '未知错误')}")
        logger.warning("[register] ORB配准失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "registered": False,
                "message": f"ORB配准失败: {result.get('error', '')}", "steps": steps,
                "debug_session": output_dir, "debug_images": debug_images}

    H = result["homography"]
    total_matches = result["total_matches"]
    inlier_count = result["inlier_count"]
    x_offset_px = float(H[0][2])
    y_offset_px = float(H[1][2])

    steps.append(f"匹配数: {total_matches}, 内点数: {inlier_count}")
    steps.append(f"X方向偏移: {x_offset_px:.4f}px  Y方向偏移: {y_offset_px:.4f}px")
    steps.append(f"仿射矩阵 H[0][2]={x_offset_px:.6f}  H[1][2]={y_offset_px:.6f}")

    logger.info("[register] 配准成功 x_off=%.4f y_off=%.4f matches=%d inliers=%d 总耗时=%.2fs",
                x_offset_px, y_offset_px, total_matches, inlier_count, time.time() - t0)
    return {
        "ok": True,
        "registered": True,
        "message": f"配准完成: X偏移={x_offset_px:.4f}px Y偏移={y_offset_px:.4f}px",
        "steps": steps,
        "debug_session": output_dir,
        "debug_images": debug_images,
        "details": {
            "x_offset_px": round(x_offset_px, 4),
            "y_offset_px": round(y_offset_px, 4),
            "total_matches": total_matches,
            "inlier_count": inlier_count,
            "homography": H,
        },
    }


# ========== 辅助: 单次X轴校准步骤 ==========

def _do_x_axis_step(r: Robot, orb_node: dict, ref_img, steps: list,
                    adjust_ptz: bool = True, cached_ptz: dict = None,
                    output_dir: str = None) -> dict:
    """执行单次X轴定位校准步骤。

    adjust_ptz=True 时先调整云台/升降杆到ORB节点位姿。
    cached_ptz 提供时跳过 _get_ptz 调用(云台在x_axis全程不变)。
    然后: 抓拍 → ORB配准 → 坐标变换 → 移动机器人(最小移动距离0.01m)。

    返回 dict:
      ok, message, x_offset_px, total_matches, inlier_count,
      converged (|x_offset_px| <= 15px),
      scale_m_per_px, delta_d_m, pan_coef, move_distance_m, world_dx, world_dy,
      from, to, debug_images
    """
    t0 = time.time()
    logger.info("[x_axis_step] 开始 ip=%s adjust_ptz=%s", r.ip, adjust_ptz)

    # 调整云台
    if adjust_ptz:
        steps.append("── 调整云台/升降杆 ──")
        cur_ptz = _adjust_ptz_and_lift(r, orb_node, steps)
    elif cached_ptz:
        cur_ptz = cached_ptz
    else:
        cur_ptz = _get_ptz(r) or {"pan": 0, "tilt": 0, "zoom": 1}

    # 抓拍
    steps.append("── 抓拍当前图 ──")
    cur_img, err = _capture_image(r)
    if cur_img is None:
        logger.warning("[x_axis_step] 抓拍失败: %s 耗时=%.2fs", err, time.time() - t0)
        return {"ok": False, "message": err}
    steps.append("抓拍成功")

    # ORB 配准
    steps.append("── ORB 配准 ──")
    result = _run_orb_matching(ref_img, cur_img, output_dir)
    debug_images = result.get("debug_images", [])
    if result.get("homography") is None:
        err_msg = f"ORB配准失败: {result.get('error', '未知错误')}"
        steps.append(err_msg)
        logger.warning("[x_axis_step] ORB配准失败: %s 耗时=%.2fs", result.get('error', ''), time.time() - t0)
        return {"ok": False, "message": err_msg, "debug_images": debug_images}

    H = result["homography"]
    total_matches = result["total_matches"]
    inlier_count = result["inlier_count"]
    x_offset_px = float(H[0][2])

    steps.append(f"匹配数: {total_matches}, 内点数: {inlier_count}")
    steps.append(f"X方向偏移: {x_offset_px:.4f}px")

    logger.info("[x_axis_step] 配准结果: x_off=%.4fpx matches=%d inliers=%d",
                x_offset_px, total_matches, inlier_count)

    # 收敛判定
    converged = abs(x_offset_px) <= X_AXIS_THRESHOLD_PX
    if converged:
        steps.append(f"X偏移 {abs(x_offset_px):.4f}px ≤ {X_AXIS_THRESHOLD_PX:.0f}px, 已收敛")
        logger.info("[x_axis_step] 已收敛 x_off=%.4fpx 耗时=%.2fs", abs(x_offset_px), time.time() - t0)
        return {
            "ok": True,
            "message": f"已收敛 (X偏移 {x_offset_px:.4f}px ≤ {X_AXIS_THRESHOLD_PX:.0f}px)",
            "x_offset_px": x_offset_px,
            "total_matches": total_matches,
            "inlier_count": inlier_count,
            "converged": True,
            "debug_images": debug_images,
        }

    # 坐标变换
    steps.append("── 坐标变换 ──")
    cur_pan = cur_ptz["pan"]
    cur_zoom = cur_ptz["zoom"]

    pose = _get_pose(r)
    if pose is None:
        return {"ok": False, "message": "无法获取机器人位姿", "debug_images": debug_images}
    cur_x = pose["x"]
    cur_y = pose["y"]
    cur_theta = pose["theta"]

    # ① 像素 → 物理距离 (取反: 当前图→参考图)
    scale = BASE_SCALE_M_PER_PX / max(cur_zoom, 0.1)
    delta_d = (-x_offset_px) * scale

    # ② 云台方向系数
    pan_coef = _get_pan_coef(cur_pan)
    move_distance = delta_d * pan_coef

    # ③ 最小移动距离保护: |move_distance| < 0.01m 时取 0.01m (保留方向)
    if abs(move_distance) < MIN_MOVE_DISTANCE_M:
        sign = 1 if move_distance >= 0 else -1
        steps.append(f"移动距离 {abs(move_distance):.6f}m < 最小移动距离 {MIN_MOVE_DISTANCE_M}m, "
                     f"取最小移动距离 {sign * MIN_MOVE_DISTANCE_M:.4f}m")
        move_distance = sign * MIN_MOVE_DISTANCE_M

    # ④ 本体坐标 → 世界坐标 (沿机器人朝向θ)
    theta_rad = math.radians(cur_theta)
    world_dx = move_distance * math.cos(theta_rad)
    world_dy = move_distance * math.sin(theta_rad)

    target_x = cur_x + world_dx
    target_y = cur_y + world_dy

    steps.append(f"当前位姿: x={cur_x:.4f} y={cur_y:.4f} θ={cur_theta:.2f}°")
    steps.append(f"云台: pan={cur_pan:.2f}° zoom={cur_zoom:.2f}x  方向系数={pan_coef:+.0f}")
    steps.append(f"像素→物理: scale={scale:.6f} m/px  Δd={delta_d:.6f} m")
    steps.append(f"移动距离: {move_distance:.6f} m")
    steps.append(f"世界位移: Δx={world_dx:+.6f}  Δy={world_dy:+.6f}")
    steps.append(f"目标位姿: x={target_x:.4f} y={target_y:.4f} θ={cur_theta:.4f}°")

    # 移动机器人
    steps.append("── 移动机器人 ──")
    ok, msg = _move_to(r, target_x, target_y, cur_theta,
                       pan=cur_ptz["pan"], tilt=cur_ptz["tilt"], zoom=cur_ptz["zoom"])
    steps.append(f"移动指令 (cmd=31): {'成功' if ok else '失败'} {msg}")
    if ok:
        # cmd=31 异步返回, 须等待机器人真正到位/停下, 否则下一轮读到中间位置 → 欠执行
        arrived, final_pose = _wait_for_arrival(r, target_x, target_y)
        if final_pose:
            steps.append(f"等待到位: {'已到位' if arrived else '超时'} 实际 x={final_pose['x']:.4f} y={final_pose['y']:.4f}")

    logger.info("[x_axis_step] 移动完成 (%.4f,%.4f)→(%.4f,%.4f) move=%.6fm 耗时=%.2fs",
                cur_x, cur_y, target_x, target_y, move_distance, time.time() - t0)

    return {
        "ok": True,
        "message": f"({cur_x:.4f},{cur_y:.4f}) → ({target_x:.4f},{target_y:.4f})",
        "x_offset_px": x_offset_px,
        "total_matches": total_matches,
        "inlier_count": inlier_count,
        "converged": False,
        "scale_m_per_px": scale,
        "delta_d_m": delta_d,
        "pan_coef": pan_coef,
        "move_distance_m": move_distance,
        "world_dx": world_dx,
        "world_dy": world_dy,
        "from": {"x": cur_x, "y": cur_y, "theta": cur_theta},
        "to": {"x": target_x, "y": target_y, "theta": cur_theta},
        "debug_images": debug_images,
    }


# ========== 辅助: 单次云台校准步骤 ==========

def _do_ptz_step(r: Robot, ref_img, target_zoom: float, steps: list,
                 output_dir: str = None) -> dict:
    """执行单次云台校准步骤。

    抓拍 → ORB配准 → 检查收敛 → 计算并应用pan/tilt修正。

    返回 dict:
      ok, message, x_offset_px, y_offset_px, total_offset_px,
      total_matches, inlier_count, converged,
      pan_delta, tilt_delta, ptz_from, ptz_to, debug_images
    """
    t0 = time.time()
    logger.info("[ptz_step] 开始 ip=%s target_zoom=%.2f", r.ip, target_zoom)

    # 抓拍
    cur_img, err = _capture_image(r)
    if cur_img is None:
        steps.append(f"抓拍失败: {err}")
        logger.warning("[ptz_step] 抓拍失败: %s 耗时=%.2fs", err, time.time() - t0)
        return {"ok": False, "message": err}
    steps.append("抓拍成功")

    # ORB 配准
    result = _run_orb_matching(ref_img, cur_img, output_dir)
    debug_images = result.get("debug_images", [])
    if result.get("homography") is None:
        err_msg = f"ORB配准失败: {result.get('error', '未知错误')}"
        steps.append(err_msg)
        logger.warning("[ptz_step] ORB配准失败: %s 耗时=%.2fs", result.get('error', ''), time.time() - t0)
        return {"ok": False, "message": err_msg, "debug_images": debug_images}

    H = result["homography"]
    x_offset_px = float(H[0][2])
    y_offset_px = float(H[1][2])
    total_matches = result["total_matches"]
    inlier_count = result["inlier_count"]
    abs_offset = math.sqrt(x_offset_px ** 2 + y_offset_px ** 2)

    steps.append(f"匹配数: {total_matches}, 内点数: {inlier_count}")
    steps.append(f"X偏移: {x_offset_px:.4f}px  Y偏移: {y_offset_px:.4f}px  "
                 f"总偏移: {abs_offset:.4f}px (阈值: {PTZ_THRESHOLD_PX:.0f}px)")
    logger.info("[ptz_step] 配准结果: x_off=%.4f y_off=%.4f total=%.4fpx matches=%d inliers=%d",
                x_offset_px, y_offset_px, abs_offset, total_matches, inlier_count)

    converged = abs_offset < PTZ_THRESHOLD_PX
    if converged:
        steps.append(f"校准成功! 总偏移 {abs_offset:.4f}px < {PTZ_THRESHOLD_PX:.0f}px")
        logger.info("[ptz_step] 已收敛 total=%.4fpx 耗时=%.2fs", abs_offset, time.time() - t0)
        return {
            "ok": True,
            "message": f"已收敛 (总偏移 {abs_offset:.4f}px)",
            "x_offset_px": x_offset_px,
            "y_offset_px": y_offset_px,
            "total_offset_px": abs_offset,
            "total_matches": total_matches,
            "inlier_count": inlier_count,
            "converged": True,
            "debug_images": debug_images,
        }

    # 未收敛, 计算 pan/tilt 修正
    pixel_to_degree = PTZ_BASE_PIXEL_TO_DEGREE / max(target_zoom, 0.1)
    # x_offset > 0: 当前图相对参考图右移 → 需要减小 pan (向左转)
    pan_delta = -x_offset_px * pixel_to_degree
    # y_offset > 0: 当前图相对参考图下移 → 需要增大 tilt (向下转)
    tilt_delta = y_offset_px * pixel_to_degree

    cur_ptz = _get_ptz(r) or {"pan": 0, "tilt": 0, "zoom": target_zoom}
    cur_pan = cur_ptz["pan"]
    cur_tilt = cur_ptz["tilt"]
    cur_zoom = cur_ptz["zoom"]

    new_pan = cur_pan + pan_delta
    new_tilt = cur_tilt + tilt_delta

    steps.append(f"像素→角度: {pixel_to_degree:.6f} °/px")
    steps.append(f"pan修正: {pan_delta:+.4f}° ({cur_pan:.4f}° → {new_pan:.4f}°)")
    steps.append(f"tilt修正: {tilt_delta:+.4f}° ({cur_tilt:.4f}° → {new_tilt:.4f}°)")

    # 执行 PTZ 修正
    ok, msg = _set_ptz(r, new_pan, new_tilt, cur_zoom)
    steps.append(f"云台修正指令: {'成功' if ok else '失败'} {msg}")

    # 等待到位
    arrived = _wait_for_ptz(r, new_pan, new_tilt, cur_zoom)
    steps.append(f"云台修正到位: {'已到位' if arrived else '超时,继续'}")

    logger.info("[ptz_step] PTZ修正完成 pan=%.2f→%.2f tilt=%.2f→%.2f arrived=%s 耗时=%.2fs",
                cur_pan, new_pan, cur_tilt, new_tilt, arrived, time.time() - t0)
    return {
        "ok": True,
        "message": f"pan: {cur_pan:.2f}°→{new_pan:.2f}°  tilt: {cur_tilt:.2f}°→{new_tilt:.2f}°",
        "x_offset_px": x_offset_px,
        "y_offset_px": y_offset_px,
        "total_offset_px": abs_offset,
        "total_matches": total_matches,
        "inlier_count": inlier_count,
        "converged": False,
        "pan_delta": pan_delta,
        "tilt_delta": tilt_delta,
        "ptz_from": {"pan": cur_pan, "tilt": cur_tilt, "zoom": cur_zoom},
        "ptz_to": {"pan": new_pan, "tilt": new_tilt, "zoom": cur_zoom},
        "debug_images": debug_images,
    }


# ========== 单次X轴定位校准 ==========

@router.post("/x-axis-step")
def x_axis_step(body: CalibIn, db: Session = Depends(get_db),
                _=Depends(engineer_only)):
    """单次X轴定位校准。

    调整云台/升降杆 → 抓拍 → ORB配准 → 坐标变换 → 移动机器人(最小移动距离0.01m)。
    返回X偏移和是否收敛(≤15px)。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    t0 = time.time()
    logger.info("[x_axis_step_ep] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    # 查找航点
    try:
        wp, orb_node = _resolve_waypoint_and_orb(r, body.node_id)
    except HTTPException as e:
        logger.warning("[x_axis_step_ep] 解析航点失败 rid=%d node_id=%s err=%s", body.rid, body.node_id, e.detail)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": f"定位校准失败: {e.detail} (node_id={body.node_id})", "steps": steps}
    steps.append(f"航点: {wp.get('name', '')} (ID: {wp.get('id', '')[:16]}…)")

    if orb_node is None:
        steps.append("未找到 OrbRegistration 节点, 无需校准")
        logger.info("[x_axis_step_ep] 无ORB配准节点, 直接返回 总耗时=%.2fs", time.time() - t0)
        return {"ok": True, "calibrated": False, "converged": False,
                "message": "无ORB配准节点", "steps": steps}

    ref_url = orb_node.get("refImageUrl", "")
    steps.append(f"ORB配准节点: refImageUrl={ref_url}")

    ref_img, err = _load_ref_image(r.id, ref_url)
    if ref_img is None:
        logger.warning("[x_axis_step_ep] 参考图加载失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": err, "steps": steps}
    steps.append("参考图加载成功")

    # 创建调试会话
    output_dir = str(_debug_single_dir(r.id, wp.get("id", ""), body.inspection_id))
    

    result = _do_x_axis_step(r, orb_node, ref_img, steps, adjust_ptz=True,
                             output_dir=output_dir)

    if not result["ok"]:
        logger.warning("[x_axis_step_ep] 校准失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": result["message"], "steps": steps,
                "debug_session": output_dir,
                "debug_images": result.get("debug_images", [])}

    logger.info("[x_axis_step_ep] 校准完成 converged=%s 总耗时=%.2fs",
                result.get("converged", False), time.time() - t0)
    return {
        "ok": True,
        "calibrated": True,
        "converged": result.get("converged", False),
        "message": f"定位校准完成: {result['message']}",
        "steps": steps,
        "debug_session": output_dir,
        "debug_images": result.get("debug_images", []),
        "details": {
            "x_offset_px": round(result["x_offset_px"], 4),
            "total_matches": result["total_matches"],
            "inlier_count": result["inlier_count"],
            "scale_m_per_px": round(result.get("scale_m_per_px", 0), 8),
            "delta_d_m": round(result.get("delta_d_m", 0), 6),
            "pan_coef": result.get("pan_coef", 0),
            "move_distance_m": round(result.get("move_distance_m", 0), 6),
            "world_dx": round(result.get("world_dx", 0), 6),
            "world_dy": round(result.get("world_dy", 0), 6),
            "from": {k: round(v, 4) for k, v in result.get("from", {}).items()},
            "to": {k: round(v, 4) for k, v in result.get("to", {}).items()},
        },
    }


# ========== 迭代X轴定位校准 ==========

@router.post("/x-axis-iter")
def x_axis_iter(body: CalibIn, db: Session = Depends(get_db)):
    """迭代X轴定位校准。

    注意: 此接口供机器人巡检时内部调用, 不需要前端认证。


    循环执行单次X轴校准, 直到X偏移 ≤ 15px 或达到最大迭代次数(10次)。
    每次迭代: 抓拍 → ORB配准 → 检查收敛 → 坐标变换 → 移动机器人(最小0.01m)。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    iterations: list[dict] = []
    t0 = time.time()
    logger.info("[x_axis_iter] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    # 查找航点和ORB节点, 找不到时返回明确错误
    try:
        wp, orb_node = _resolve_waypoint_and_orb(r, body.node_id)
    except HTTPException as e:
        logger.warning("[x_axis_iter] 解析航点失败 rid=%d node_id=%s err=%s", body.rid, body.node_id, e.detail)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": f"X轴校准失败: {e.detail} (node_id={body.node_id})",
                "steps": steps, "iterations": iterations}
    steps.append(f"航点: {wp.get('name', '')} (ID: {wp.get('id', '')[:16]}…)")

    if orb_node is None:
        steps.append("未找到 OrbRegistration 节点, 无需校准")
        logger.info("[x_axis_iter] 无ORB配准节点, 直接返回 总耗时=%.2fs", time.time() - t0)
        return {"ok": True, "calibrated": False, "converged": False,
                "message": "无ORB配准节点", "steps": steps, "iterations": iterations}

    ref_url = orb_node.get("refImageUrl", "")
    steps.append(f"ORB配准节点: refImageUrl={ref_url}")

    ref_img, err = _load_ref_image(r.id, ref_url)
    if ref_img is None:
        logger.warning("[x_axis_iter] 参考图加载失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": err, "steps": steps, "iterations": iterations}
    steps.append("参考图加载成功")

    # 创建调试会话 (multiple)
    iter_dir = _debug_multiple_dir(r.id, wp.get("id", ""), orb_node.get("id", ""), "xaxis", body.inspection_id)

    steps.append(f"── 开始迭代X轴校准 (最多{X_AXIS_MAX_ITERATIONS}次, 阈值{X_AXIS_THRESHOLD_PX:.0f}px) ──")
    converged = False
    cached_ptz = None  # 缓存 pan/zoom, x_axis 全程云台不动
    logger.info("[x_axis_iter] 开始迭代 max_iter=%d threshold=%.0fpx", X_AXIS_MAX_ITERATIONS, X_AXIS_THRESHOLD_PX)

    for iteration in range(1, X_AXIS_MAX_ITERATIONS + 1):
        iter_t0 = time.time()
        steps.append(f"━━━ 第 {iteration} 轮 ━━━")
        iter_info: dict[str, Any] = {"iteration": iteration}
        logger.info("[x_axis_iter] 第%d轮开始", iteration)

        # 直接用 iter_dir 存图, 每次覆盖
        result = _do_x_axis_step(r, orb_node, ref_img, steps,
                                 adjust_ptz=(iteration == 1),
                                 cached_ptz=cached_ptz,
                                 output_dir=str(iter_dir))

        if not result["ok"]:
            iter_info["error"] = result["message"]
            iter_info["debug_images"] = result.get("debug_images", [])
            iterations.append(iter_info)
            _save_iteration(iter_dir, iteration, steps[-15:], result.get("debug_images", []))
            (iter_dir / "steps.txt").write_text("\n".join(steps[-15:]), encoding="utf-8")
            logger.warning("[x_axis_iter] 第%d轮ORB失败, 继续下一轮: %s 总耗时=%.2fs",
                           iteration, result["message"], time.time() - t0)
            if iteration >= X_AXIS_MAX_ITERATIONS:
                return {"ok": False, "calibrated": False, "converged": False,
                        "message": f"全部{X_AXIS_MAX_ITERATIONS}轮ORB匹配失败, 最后一轮: {result['message']}",
                        "steps": steps, "iterations": iterations,
                        "debug_session": str(iter_dir)}
            continue

        x_offset_px = result["x_offset_px"]
        iter_info.update({
            "x_offset_px": round(x_offset_px, 4),
            "total_matches": result["total_matches"],
            "inlier_count": result["inlier_count"],
            "converged": result.get("converged", False),
            "debug_images": result.get("debug_images", []),
        })

        # 保存本轮过程图到子目录
        _save_iteration(iter_dir, iteration, steps[-10:], result.get("debug_images", []))

        # 第1轮完成后缓存 pan/zoom, 后续轮次复用(云台全程不动)
        if iteration == 1 and cached_ptz is None:
            cached_ptz = _get_ptz(r) or {"pan": 0, "tilt": 0, "zoom": 1}

        if result.get("move_distance_m") is not None:
            iter_info["move_distance_m"] = round(result["move_distance_m"], 6)
        if result.get("from"):
            iter_info["from"] = {k: round(v, 4) for k, v in result["from"].items()}
        if result.get("to"):
            iter_info["to"] = {k: round(v, 4) for k, v in result["to"].items()}

        if result.get("converged"):
            steps.append(f"第{iteration}轮已收敛, 停止迭代")
            iterations.append(iter_info)
            converged = True
            logger.info("[x_axis_iter] 第%d轮已收敛, 停止迭代 本轮耗时=%.2fs 累计=%.2fs",
                        iteration, time.time() - iter_t0, time.time() - t0)
            break

        if iteration < X_AXIS_MAX_ITERATIONS:
            steps.append("等待机器人移动到位(1秒)…")
            time.sleep(0.3)  # _do_x_axis_step 内部已 _wait_for_arrival, 这里只留小缓冲
        else:
            steps.append(f"已达到最大迭代次数 {X_AXIS_MAX_ITERATIONS}, "
                         f"当前X偏移 {abs(x_offset_px):.4f}px, 停止校准")

        logger.info("[x_axis_iter] 第%d轮完成 x_off=%.4fpx 本轮耗时=%.2fs 累计=%.2fs",
                    iteration, x_offset_px, time.time() - iter_t0, time.time() - t0)
        iterations.append(iter_info)

    logger.info("[x_axis_iter] 出口 converged=%s iterations=%d 总耗时=%.2fs",
                converged, len(iterations), time.time() - t0)
    # 保存步骤日志和指标
    (iter_dir / "steps.txt").write_text("\n".join(steps), encoding="utf-8")
    import json as _json
    (iter_dir / "metrics.json").write_text(_json.dumps({
        "converged": converged, "iterations": len(iterations),
        "max_iterations": X_AXIS_MAX_ITERATIONS, "threshold_px": X_AXIS_THRESHOLD_PX,
        "iterations_detail": iterations,
    }, ensure_ascii=False, indent=2), encoding="utf-8")
    return {
        "ok": True,
        "calibrated": True,
        "converged": converged,
        "message": f"X轴校准{'成功' if converged else '未收敛'} "
                   f"({'已收敛' if converged else f'已达{X_AXIS_MAX_ITERATIONS}次上限'})",
        "steps": steps,
        "iterations": iterations,
        "debug_session": str(iter_dir),
        "max_iterations": X_AXIS_MAX_ITERATIONS,
        "threshold_px": X_AXIS_THRESHOLD_PX,
    }


# ========== 单次云台校准 ==========

@router.post("/ptz-step")
def ptz_step(body: CalibIn, db: Session = Depends(get_db),
             _=Depends(engineer_only)):
    """单次云台校准。

    抓拍 → ORB配准 → 检查收敛(总偏移<10px) → 计算并应用pan/tilt修正。
    使用动作点自身的 snap_shot_url 作为参考图, 不依赖 OrbRegistration 节点。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    t0 = time.time()
    logger.info("[ptz_step_ep] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    # 查找动作点节点
    try:
        action_node = _resolve_action_node(r, body.node_id)
    except HTTPException as e:
        logger.warning("[ptz_step_ep] 解析动作点失败 rid=%d node_id=%s err=%s", body.rid, body.node_id, e.detail)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": f"云台校准失败: {e.detail} (node_id={body.node_id})"}
    steps.append(f"动作点: {action_node.get('name', '')} (ID: {action_node.get('id', '')[:16]}…)")

    snap_url = action_node.get("snap_shot_url", "")
    steps.append(f"参考图: snap_shot_url={snap_url}")

    ref_img, err = _load_image_from_url(r.id, snap_url, cache_key=action_node.get("id"))
    if ref_img is None:
        logger.warning("[ptz_step_ep] 参考图加载失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": err, "steps": steps}
    steps.append("参考图加载成功")

    ptz_param = action_node.get("ptz_param", {})
    target_zoom = float(ptz_param.get("zoom", 1))

    # 创建调试会话 (single)
    output_dir = str(_debug_single_dir(r.id, action_node.get("id", ""), body.inspection_id))


    result = _do_ptz_step(r, ref_img, target_zoom, steps, output_dir=output_dir)

    if not result["ok"]:
        logger.warning("[ptz_step_ep] 校准失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": result["message"], "steps": steps,
                "debug_session": output_dir,
                "debug_images": result.get("debug_images", [])}

    logger.info("[ptz_step_ep] 校准完成 converged=%s 总耗时=%.2fs",
                result.get("converged", False), time.time() - t0)
    return {
        "ok": True,
        "calibrated": True,
        "converged": result.get("converged", False),
        "message": f"单次云台校准: {result['message']}",
        "steps": steps,
        "debug_session": output_dir,
        "debug_images": result.get("debug_images", []),
        "details": {
            "x_offset_px": round(result["x_offset_px"], 4),
            "y_offset_px": round(result["y_offset_px"], 4),
            "total_offset_px": round(result["total_offset_px"], 4),
            "total_matches": result["total_matches"],
            "inlier_count": result["inlier_count"],
            "pan_delta": round(result.get("pan_delta", 0), 4),
            "tilt_delta": round(result.get("tilt_delta", 0), 4),
            "ptz_from": {k: round(v, 4) for k, v in result.get("ptz_from", {}).items()},
            "ptz_to": {k: round(v, 4) for k, v in result.get("ptz_to", {}).items()},
        },
    }


# ========== 迭代云台校准 ==========

@router.post("/ptz-iter")
def ptz_iter(body: CalibIn, db: Session = Depends(get_db)):
    """迭代云台校准 (最多8次)。

    注意: 此接口供机器人巡检时内部调用, 不需要前端认证。


    使用动作点自身的 snap_shot_url 作为参考图, 不依赖 OrbRegistration 节点。
    迭代(最多8次): 等待视频流稳定 → 抓拍 → ORB配准 → 检查收敛(总偏移<10px) → 调整pan/tilt。
    """
    r = _robot_by_rid(body.rid, db)
    steps: list[str] = []
    iterations: list[dict] = []
    t0 = time.time()
    logger.info("[ptz_iter] 入口 rid=%d node_id=%s ip=%s", body.rid, body.node_id, r.ip)

    # 查找动作点节点, 找不到时返回明确错误
    try:
        action_node = _resolve_action_node(r, body.node_id)
    except HTTPException as e:
        logger.warning("[ptz_iter] 解析动作点失败 rid=%d node_id=%s err=%s", body.rid, body.node_id, e.detail)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": f"云台校准失败: {e.detail} (node_id={body.node_id})",
                "steps": steps, "iterations": iterations}
    steps.append(f"动作点: {action_node.get('name', '')} (ID: {action_node.get('id', '')[:16]}…)" )

    snap_url = action_node.get("snap_shot_url", "")
    steps.append(f"参考图: snap_shot_url={snap_url}")

    ptz_param = action_node.get("ptz_param", {})
    target_zoom = float(ptz_param.get("zoom", 1))

    # 加载参考图
    ref_img, err = _load_image_from_url(r.id, snap_url, cache_key=action_node.get("id"))
    if ref_img is None:
        logger.warning("[ptz_iter] 参考图加载失败, 退出 总耗时=%.2fs", time.time() - t0)
        return {"ok": False, "calibrated": False, "converged": False,
                "message": err, "steps": steps, "iterations": iterations}
    steps.append("参考图加载成功")

    # 创建调试会话 (multiple, 每次清空)
    iter_dir = _debug_multiple_dir(r.id, body.node_id, action_node.get("id", ""), "ptz", body.inspection_id)
    output_dir = str(iter_dir)
    steps.append(f"── 开始云台校准 (最多{PTZ_MAX_ITERATIONS}次迭代, 阈值{PTZ_THRESHOLD_PX:.0f}px) ──")
    converged = False
    logger.info("[ptz_iter] 开始迭代 max_iter=%d threshold=%.0fpx target_zoom=%.2f",
                PTZ_MAX_ITERATIONS, PTZ_THRESHOLD_PX, target_zoom)

    for iteration in range(1, PTZ_MAX_ITERATIONS + 1):
        iter_t0 = time.time()
        steps.append(f"━━━ 第 {iteration} 轮 ━━━")
        iter_info: dict[str, Any] = {"iteration": iteration}
        logger.info("[ptz_iter] 第%d轮开始 累计耗时=%.2fs", iteration, time.time() - t0)

        result = _do_ptz_step(r, ref_img, target_zoom, steps, output_dir=str(iter_dir))

        if not result["ok"]:
            iter_info["error"] = result["message"]
            iter_info["debug_images"] = result.get("debug_images", [])
            iterations.append(iter_info)
            _save_iteration(iter_dir, iteration, steps[-15:], result.get("debug_images", []))
            logger.warning("[ptz_iter] 第%d轮ORB失败, 继续下一轮: %s 累计耗时=%.2fs",
                           iteration, result["message"], time.time() - t0)
            if iteration >= PTZ_MAX_ITERATIONS:
                return {"ok": False, "calibrated": False, "converged": False,
                        "message": f"全部{PTZ_MAX_ITERATIONS}轮ORB匹配失败, 最后一轮: {result['message']}",
                        "steps": steps, "iterations": iterations,
                        "debug_session": str(iter_dir)}
            continue

        iter_info.update({
            "x_offset_px": round(result["x_offset_px"], 4),
            "y_offset_px": round(result["y_offset_px"], 4),
            "total_offset_px": round(result["total_offset_px"], 4),
            "total_matches": result["total_matches"],
            "inlier_count": result["inlier_count"],
            "converged": result.get("converged", False),
            "debug_images": result.get("debug_images", []),
        })

        # 保存本轮过程图到子目录
        _save_iteration(iter_dir, iteration, steps[-10:], result.get("debug_images", []))

        if result.get("pan_delta") is not None:
            iter_info["pan_delta"] = round(result["pan_delta"], 4)
            iter_info["tilt_delta"] = round(result["tilt_delta"], 4)
            iter_info["ptz_from"] = {k: round(v, 4) for k, v in result.get("ptz_from", {}).items()}
            iter_info["ptz_to"] = {k: round(v, 4) for k, v in result.get("ptz_to", {}).items()}

        if result.get("converged"):
            iterations.append(iter_info)
            converged = True
            logger.info("[ptz_iter] 第%d轮已收敛 total_off=%.4fpx 本轮耗时=%.2fs 累计=%.2fs",
                        iteration, result["total_offset_px"], time.time() - iter_t0, time.time() - t0)
            break

        if iteration >= PTZ_MAX_ITERATIONS:
            steps.append(f"已达到最大迭代次数 {PTZ_MAX_ITERATIONS}, "
                         f"当前偏移 {result['total_offset_px']:.4f}px, 停止校准")

        logger.info("[ptz_iter] 第%d轮完成 total_off=%.4fpx pan_delta=%s 本轮耗时=%.2fs 累计=%.2fs",
                    iteration, result["total_offset_px"],
                    round(result.get("pan_delta", 0), 4) if result.get("pan_delta") is not None else "N/A",
                    time.time() - iter_t0, time.time() - t0)
        iterations.append(iter_info)

    logger.info("[ptz_iter] 出口 converged=%s iterations=%d 总耗时=%.2fs",
                converged, len(iterations), time.time() - t0)
    # 保存步骤日志和指标
    (iter_dir / "steps.txt").write_text("\n".join(steps), encoding="utf-8")
    import json as _json
    (iter_dir / "metrics.json").write_text(_json.dumps({
        "converged": converged, "iterations": len(iterations),
        "max_iterations": PTZ_MAX_ITERATIONS, "threshold_px": PTZ_THRESHOLD_PX,
        "iterations_detail": iterations,
    }, ensure_ascii=False, indent=2), encoding="utf-8")
    # 提取最终PTZ位姿，供C++行为树更新黑板值
    final_ptz = None
    if iterations:
        last = iterations[-1]
        if "ptz_to" in last:
            final_ptz = last["ptz_to"]
        elif "ptz_from" in last:
            final_ptz = last["ptz_from"]
    return {
        "ok": True,
        "calibrated": True,
        "converged": converged,
        "message": "云台校准成功" if converged else f"未收敛(已达{PTZ_MAX_ITERATIONS}次迭代上限)",
        "steps": steps,
        "iterations": iterations,
        "debug_session": str(iter_dir),
        "max_iterations": PTZ_MAX_ITERATIONS,
        "threshold_px": PTZ_THRESHOLD_PX,
        "ptz_pose": final_ptz,  # C++行为树用: {"pan":..., "tilt":..., "zoom":...}
    }
