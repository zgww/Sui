"""ORB 配准调试模块。

功能:
  1. 从工控机拉取 inspection.json 或手动导入
  2. 前往航点(到位+PTZ+升降杆)
  3. 拍照保存定标图 + 位姿映射
  4. ORB 特征匹配(参考定标图 vs 当前拍照)
  5. 微挪循环(不匹配时自动微动+重试)

定标图存 calibration/{wp_id}_visible.jpg
过程图存 calibration/orb/{wp_id}/{timestamp}/
"""
import json
import base64
import time
import uuid
from datetime import datetime
from io import BytesIO
from pathlib import Path
from typing import Optional, List
from fastapi import APIRouter, Depends, HTTPException, UploadFile, File
from fastapi.responses import StreamingResponse
from pydantic import BaseModel
from sqlalchemy.orm import Session

from ..database import get_db
from ..models import Robot
from ..auth import engineer_only, get_current_user
from ..config import CALIB_DIR, ORB_DIR
from ..services import robot_api, ssh_client

router = APIRouter(prefix="/api/orb", tags=["orb_calibration"])


def _robot(rid: int, db: Session) -> Robot:
    r = db.query(Robot).filter(Robot.id == rid).first()
    if not r:
        raise HTTPException(404, "机器人不存在")
    return r


# ========== 航点获取 ==========
@router.get("/{rid}/inspection")
def get_inspection(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """从工控机 SFTP 拉取 /home/nav/robot/robot/inspection.json。"""
    r = _robot(rid, db)
    try:
        cli = ssh_client._connect(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)
        sftp = cli.open_sftp()
        try:
            remote_path = "/home/nav/robot/robot/inspection.json"
            with sftp.file(remote_path, "r") as f:
                data = json.loads(f.read().decode("utf-8"))
        finally:
            sftp.close()
            cli.close()
        return {"ok": True, "data": data, "source": "sftp"}
    except Exception as e:  # noqa: BLE001
        return {"ok": False, "data": None, "msg": f"拉取失败: {e}。可手动导入 JSON"}


class ImportIn(BaseModel):
    data: dict


@router.post("/{rid}/inspection/import")
def import_inspection(rid: int, body: ImportIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """手动导入 inspection.json(存本地缓存, 下次优先用)。"""
    r = _robot(rid, db)
    cache_path = CALIB_DIR / f"inspection_{rid}.json"
    cache_path.write_text(json.dumps(body.data, ensure_ascii=False, indent=2), encoding="utf-8")
    return {"ok": True, "msg": "已导入并缓存", "data": body.data}


@router.get("/{rid}/inspection/cached")
def get_cached_inspection(rid: int, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """优先读缓存, 没有则尝试 SFTP。"""
    r = _robot(rid, db)
    cache_path = CALIB_DIR / f"inspection_{rid}.json"
    if cache_path.exists():
        return {"ok": True, "data": json.loads(cache_path.read_text("utf-8")), "source": "cache"}
    return get_inspection(rid, db)


# ========== 前往航点 ==========
class GotoIn(BaseModel):
    x: float
    y: float
    theta: float = 0
    lift_height: float = 0
    ptz_pan: float = 0
    ptz_tilt: float = 0
    ptz_zoom: float = 0
    wait_arrive: bool = True
    arrive_timeout: float = 30.0


def _is_arrived(r: Robot, target_x: float, target_y: float, target_theta: float,
                dist_tol: float = 0.1, angle_tol: float = 3.0) -> bool:
    """到位判断: 读取当前位姿, 比较与目标的距离和角度差。"""
    try:
        code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 30, timeout=4.0)
        if code != 0 or not d:
            return False
        cur_x = d.get("x", 0) or (d.get("point", {}) or {}).get("x", 0)
        cur_y = d.get("y", 0) or (d.get("point", {}) or {}).get("y", 0)
        cur_theta = d.get("theta", 0)
        dist = ((cur_x - target_x) ** 2 + (cur_y - target_y) ** 2) ** 0.5
        angle_diff = abs(cur_theta - target_theta) % 360
        if angle_diff > 180:
            angle_diff = 360 - angle_diff
        return dist <= dist_tol and angle_diff <= angle_tol
    except Exception:
        return False


@router.post("/{rid}/goto")
def goto_waypoint(rid: int, body: GotoIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """前往航点: 移动到位(cmd=31) → 升降杆(cmd=41) → 云台(cmd=36)。可等待到位。"""
    r = _robot(rid, db)
    steps = []

    # 1. 移动到目标位姿
    payload = {
        "point": {"x": body.x, "y": body.y},
        "theta": body.theta,
        "safety_check": False,
    }
    code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 31, payload)
    steps.append(f"移动到位姿 (cmd=31): code={code} {msg}")

    # 2. 升降杆
    if body.lift_height > 0:
        code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 41, {"command": 3, "height": body.lift_height})
        steps.append(f"升降杆→{body.lift_height}m (cmd=41): code={code} {msg}")

    # 3. 云台
    code, msg, _ = robot_api.call(r.ip, r.api_port, r.robot_id, 36,
                                   {"pan": body.ptz_pan, "tilt": body.ptz_tilt, "zoom": body.ptz_zoom})
    steps.append(f"云台→({body.ptz_pan},{body.ptz_tilt},{body.ptz_zoom}) (cmd=36): code={code} {msg}")

    # 4. 等待到位
    arrived = False
    if body.wait_arrive:
        start = time.time()
        while time.time() - start < body.arrive_timeout:
            if _is_arrived(r, body.x, body.y, body.theta):
                arrived = True
                break
            time.sleep(1.5)
        steps.append(f"到位等待: {'✅ 已到位' if arrived else '⚠ 超时'} ({time.time()-start:.0f}s)")

    return {"ok": True, "arrived": arrived, "steps": steps}


# ========== 拍照保存定标图 ==========
class CaptureIn(BaseModel):
    wp_id: str = ""
    note: str = ""


@router.post("/{rid}/capture")
def capture_calibration(rid: int, body: CaptureIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """拍照(cmd=38可见光+红外) + 读当前位姿, 保存定标图 + 映射 JSON。"""
    r = _robot(rid, db)
    wp_id = body.wp_id or f"wp_{uuid.uuid4().hex[:6]}"
    result = {"wp_id": wp_id, "images": {}, "mapping": {}}

    # 1. 可见光拍照
    code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 38, {"command": 1})
    if code == 0 and d:
        fname = f"{wp_id}_visible.jpg"
        _save_capture_file(r, d, fname)
        result["images"]["visible"] = f"/data/calibration/{fname}"

    # 2. 红外拍照
    code, msg, d = robot_api.call(r.ip, r.api_port, r.robot_id, 38, {"command": 2})
    if code == 0 and d:
        fname = f"{wp_id}_thermal.jpg"
        _save_capture_file(r, d, fname)
        result["images"]["thermal"] = f"/data/calibration/{fname}"

    # 3. 读当前位姿
    pose_data = {}
    try:
        code, _, d = robot_api.call(r.ip, r.api_port, r.robot_id, 30)
        if code == 0:
            pose_data["pose"] = {"x": d.get("x") or (d.get("point", {}) or {}).get("x"),
                                 "y": d.get("y") or (d.get("point", {}) or {}).get("y"),
                                 "theta": d.get("theta")}
    except Exception:
        pass
    try:
        code, _, d = robot_api.call(r.ip, r.api_port, r.robot_id, 35)
        if code == 0:
            pose_data["ptz"] = {"pan": d.get("pan"), "tilt": d.get("tilt"), "zoom": d.get("zoom")}
    except Exception:
        pass
    try:
        code, _, d = robot_api.call(r.ip, r.api_port, r.robot_id, 40)
        if code == 0:
            pose_data["lift"] = {"height": d.get("height")}
    except Exception:
        pass

    result["mapping"] = pose_data
    result["mapping"]["note"] = body.note

    # 保存映射
    mapping_path = CALIB_DIR / f"{wp_id}_mapping.json"
    mapping_path.write_text(json.dumps(pose_data, ensure_ascii=False, indent=2), encoding="utf-8")

    result["ok"] = True
    return result


def _save_capture_file(r: Robot, data: dict, fname: str):
    """从 cmd=38 返回的 data 中提取图片保存。若返回 file 路径则 SFTP 拉取; 若返回 base64 则直接存。"""
    if not data:
        return
    # 尝试 base64
    img_b64 = data.get("image") or data.get("base64") or data.get("data")
    if img_b64:
        raw = base64.b64decode(img_b64)
        (CALIB_DIR / fname).write_bytes(raw)
        return
    # 尝试机器人本地文件路径 → SFTP 拉取
    file_path = data.get("file") or data.get("path") or ""
    if file_path:
        try:
            cli = ssh_client._connect(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)
            sftp = cli.open_sftp()
            try:
                sftp.get(file_path, str(CALIB_DIR / fname))
            finally:
                sftp.close()
                cli.close()
        except Exception:
            pass


# ========== ORB 比对核心 ==========
class OrbCompareIn(BaseModel):
    wp_id: str
    channel: str = "visible"   # visible | thermal
    mask_top_ratio: float = 0.0      # 顶部掩膜比例(0~1)
    mask_bottom_ratio: float = 0.0   # 底部掩膜比例(0~1)
    cur_image_base64: str = ""       # 当前拍照 base64(如空则自动 cmd=38 拍照)
    n_features: int = 1000


@router.post("/{rid}/compare")
def orb_compare(rid: int, body: OrbCompareIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """ORB 特征比对: 定标图 vs 当前拍照。"""
    import cv2
    import numpy as np

    r = _robot(rid, db)
    wp_id = body.wp_id
    channel = body.channel

    # 1. 读取定标图
    ref_ext = "thermal" if channel == "thermal" else "visible"
    ref_path = CALIB_DIR / f"{wp_id}_{ref_ext}.jpg"
    if not ref_path.exists():
        raise HTTPException(400, f"定标图不存在: {ref_path}")
    ref_img = cv2.imread(str(ref_path))
    if ref_img is None:
        raise HTTPException(400, "定标图读取失败")

    # 2. 获取当前拍照
    if body.cur_image_base64:
        cur_img = _base64_to_cv2(body.cur_image_base64)
    else:
        cmd = 2 if channel == "thermal" else 1
        code, _, d = robot_api.call(r.ip, r.api_port, r.robot_id, 38, {"command": cmd})
        if code != 0:
            raise HTTPException(400, f"拍照失败 cmd=38 code={code}")
        cur_img = _get_image_from_data(r, d)
        if cur_img is None:
            raise HTTPException(400, "未能从拍照结果中获取图片")
    if cur_img is None:
        raise HTTPException(400, "当前拍照为空")

    # 3. 统一尺寸
    h = max(ref_img.shape[0], cur_img.shape[0])
    w = max(ref_img.shape[1], cur_img.shape[1])
    ref_img = cv2.resize(ref_img, (w, h))
    cur_img = cv2.resize(cur_img, (w, h))

    # 4. 创建输出目录
    ts = datetime.utcnow().strftime("%Y%m%d_%H%M%S")
    out_dir = ORB_DIR / wp_id / ts
    out_dir.mkdir(parents=True, exist_ok=True)

    # 5. pHash 相似度
    import imagehash
    from PIL import Image
    ref_pil = Image.fromarray(cv2.cvtColor(ref_img, cv2.COLOR_BGR2RGB))
    cur_pil = Image.fromarray(cv2.cvtColor(cur_img, cv2.COLOR_BGR2RGB))
    phash_distance = imagehash.phash(ref_pil) - imagehash.phash(cur_pil)

    # 6. 掩膜
    ref_mask = _create_mask(ref_img.shape, body.mask_top_ratio, body.mask_bottom_ratio)
    cur_mask = _create_mask(cur_img.shape, body.mask_top_ratio, body.mask_bottom_ratio)

    # 7. ORB 特征提取
    orb = cv2.ORB_create(nfeatures=body.n_features)
    ref_kp, ref_des = orb.detectAndCompute(ref_img, ref_mask)
    cur_kp, cur_des = orb.detectAndCompute(cur_img, cur_mask)

    result = {"phash_distance": phash_distance, "ref_keypoints": len(ref_kp) if ref_kp else 0,
              "cur_keypoints": len(cur_kp) if cur_kp else 0}

    if ref_des is None or cur_des is None or len(ref_kp) < 10 or len(cur_kp) < 10:
        result["error"] = "特征点不足"
        result["same_scene"] = False
        return result

    # 8. BFMatcher + Lowe's ratio test
    bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=False)
    raw_matches = bf.knnMatch(ref_des, cur_des, k=2)
    good_matches = []
    for m_n in raw_matches:
        if len(m_n) == 2:
            m, n = m_n
            if m.distance < 0.75 * n.distance:
                good_matches.append(m)
    result["total_matches"] = len(good_matches)

    if len(good_matches) < 10:
        result["error"] = "有效匹配点不足(需≥10)"
        result["same_scene"] = False
        return result

    # 9. RANSAC 单应性矩阵
    src_pts = np.float32([ref_kp[m.queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
    dst_pts = np.float32([cur_kp[m.trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)
    H, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)
    inlier_count = int(mask.sum()) if mask is not None else 0

    # 10. 评估指标
    h_ref, w_ref = ref_img.shape[:2]
    corners = np.float32([[0, 0], [w_ref, 0], [w_ref, h_ref], [0, h_ref]]).reshape(-1, 1, 2)
    transformed_corners = cv2.perspectiveTransform(corners, H) if H is not None else corners

    # 覆盖网格
    grid_size = 5
    coverage_count = _coverage_grid(H, (w_ref, h_ref), cur_img.shape[1], cur_img.shape[0], grid_size)

    # 面积比
    area_ref = w_ref * h_ref
    area_warped = cv2.contourArea(transformed_corners.reshape(-1, 2)) if H is not None else 0
    area_ratio = area_warped / area_ref if area_ref > 0 else 0

    # 角点判定
    cur_w, cur_h = cur_img.shape[1], cur_img.shape[0]
    corners_in = sum(1 for c in transformed_corners.reshape(-1, 2)
                     if 0 <= c[0] <= cur_w and 0 <= c[1] <= cur_h)

    assessment = {
        "inlier_count": inlier_count,
        "inlier_ratio": round(inlier_count / len(good_matches), 3) if good_matches else 0,
        "coverage_count": coverage_count,
        "area_ratio": round(area_ratio, 3),
        "corners_in_bounds": corners_in,
        "same_scene": inlier_count >= 15 and area_ratio > 0.3,
    }

    # 11. 保存过程图
    _save_debug_images(ref_img, cur_img, ref_kp, cur_kp, good_matches, H,
                       ref_mask, cur_mask, transformed_corners, out_dir)

    # 12. 保存评估 JSON
    save_path = out_dir / "transformed_boxes.json"
    boxes = _serialize_boxes(transformed_corners)
    save_path.write_text(json.dumps({
        "homography": H.tolist() if H is not None else None,
        "transformed_boxes": boxes,
        "total_matches": len(good_matches),
        "assessment": assessment,
    }, ensure_ascii=False, indent=2), encoding="utf-8")

    # 返回结果
    result.update(assessment)
    result["images"] = {
        "ref_mask": f"/data/calibration/orb/{wp_id}/{ts}/00_ref_mask.jpg",
        "cur_mask": f"/data/calibration/orb/{wp_id}/{ts}/00_cur_mask.jpg",
        "ref_keypoints": f"/data/calibration/orb/{wp_id}/{ts}/01_ref_keypoints.jpg",
        "cur_keypoints": f"/data/calibration/orb/{wp_id}/{ts}/01_cur_keypoints.jpg",
        "matches": f"/data/calibration/orb/{wp_id}/{ts}/02_matches.jpg",
        "reference_outline": f"/data/calibration/orb/{wp_id}/{ts}/03_reference_outline.jpg",
        "warped_reference": f"/data/calibration/orb/{wp_id}/{ts}/04_warped_reference.jpg",
        "blended": f"/data/calibration/orb/{wp_id}/{ts}/05_blended.jpg",
        "transformed_boxes": f"/data/calibration/orb/{wp_id}/{ts}/06_transformed_boxes.jpg",
    }
    return result


# ========== 微挪循环 ==========
class MicroMoveIn(BaseModel):
    wp_id: str
    channel: str = "visible"
    step_speed: float = 0.3       # 微挪速度
    step_count: int = 3            # 每方向步数
    directions: List[int] = None   # 默认 [0,1,2,3,4] = 停/前/后/左/右
    lift_adjust: float = 0         # 升降微调(0则不调)
    mask_top_ratio: float = 0.0
    mask_bottom_ratio: float = 0.0


@router.post("/{rid}/micro-move")
def micro_move(rid: int, body: MicroMoveIn, db: Session = Depends(get_db), _=Depends(engineer_only)):
    """微挪循环: 向各方向微动 + 拍照 + ORB 比对, 找最佳匹配。"""
    r = _robot(rid, db)
    directions = body.directions or [1, 2, 3, 4]  # 前/后/左/右
    best = None
    all_results = []

    for d in directions:
        for step in range(body.step_count):
            # 微挪
            robot_api.call(r.ip, r.api_port, r.robot_id, 32, {"command": d, "instant_speed": body.step_speed, "safety_check": False})
            time.sleep(0.5)
            robot_api.call(r.ip, r.api_port, r.robot_id, 32, {"command": 0})  # 停
            time.sleep(0.3)

            # 调升降
            if body.lift_adjust:
                robot_api.call(r.ip, r.api_port, r.robot_id, 41,
                               {"command": 3, "height": body.lift_adjust})
                time.sleep(1)

            # 拍照
            cmd_num = 2 if body.channel == "thermal" else 1
            code, _, d = robot_api.call(r.ip, r.api_port, r.robot_id, 38, {"command": cmd_num})
            if code != 0:
                continue
            cur_b64 = _extract_base64_from_data(r, d)
            if not cur_b64:
                continue

            # ORB 比对
            try:
                orb_in = OrbCompareIn(wp_id=body.wp_id, channel=body.channel,
                                      mask_top_ratio=body.mask_top_ratio,
                                      mask_bottom_ratio=body.mask_bottom_ratio,
                                      cur_image_base64=cur_b64)
                res = orb_compare(rid, orb_in, db, _=get_current_user)
                all_results.append({"direction": d, "step": step, "result": res})
                score = res.get("inlier_count", 0)
                if best is None or score > best.get("inlier_count", 0):
                    best = {"direction": d, "step": step, "inlier_count": score, "result": res}
                if res.get("same_scene"):
                    return {"ok": True, "matched": True, "best": best, "all": all_results}
            except HTTPException:
                pass

    return {"ok": True, "matched": best is not None and best.get("inlier_count", 0) >= 15,
            "best": best, "all": all_results}


# ========== ORB 结果图片获取 ==========
@router.get("/{rid}/result-image")
def get_result_image(rid: int, path: str, db: Session = Depends(get_db), _=Depends(get_current_user)):
    """获取 ORB 过程图。path 为相对路径如 /data/calibration/orb/wp_001/20260101/02_matches.jpg"""
    full = Path(path.lstrip("/"))
    if not str(full).startswith(str(CALIB_DIR)):
        full = CALIB_DIR.parent / path.lstrip("/")
    if not full.exists():
        raise HTTPException(404, "图片不存在")
    return StreamingResponse(BytesIO(full.read_bytes()), media_type="image/jpeg")


# ========== 辅助函数 ==========
def _base64_to_cv2(b64: str):
    """base64 dataurl → cv2 image。"""
    import cv2, numpy as np
    if "," in b64:
        b64 = b64.split(",", 1)[1]
    raw = base64.b64decode(b64)
    arr = np.frombuffer(raw, np.uint8)
    return cv2.imdecode(arr, cv2.IMREAD_COLOR)


def _get_image_from_data(r: Robot, data: dict):
    """从 cmd=38 返回数据中提取 cv2 图片。"""
    import cv2, numpy as np
    b64 = _extract_base64_from_data(r, data)
    if not b64:
        return None
    return _base64_to_cv2(b64)


def _extract_base64_from_data(r: Robot, data: dict) -> Optional[str]:
    """从 cmd=38 返回中提取 base64 图片。"""
    if not data:
        return None
    img_b64 = data.get("image") or data.get("base64") or data.get("data")
    if img_b64:
        return img_b64 if "," not in str(img_b64) else str(img_b64)
    # 尝试从 file 路径 SFTP 拉取
    fp = data.get("file") or data.get("path") or ""
    if fp:
        try:
            cli = ssh_client._connect(r.ip, r.ssh_port, r.ssh_user, r.ssh_pass)
            sftp = cli.open_sftp()
            try:
                with sftp.file(fp, "rb") as f:
                    raw = f.read()
                return base64.b64encode(raw).decode("ascii")
            finally:
                sftp.close()
                cli.close()
        except Exception:
            pass
    return None


def _create_mask(shape, top_ratio: float, bottom_ratio: float):
    """创建掩膜: 顶部和底部按比例置零。"""
    import numpy as np
    h, w = shape[:2]
    mask = np.ones((h, w), dtype=np.uint8) * 255
    if top_ratio > 0:
        mask[:int(h * top_ratio), :] = 0
    if bottom_ratio > 0:
        mask[int(h * (1 - bottom_ratio)):, :] = 0
    return mask


def _coverage_grid(H, ref_size, cur_w, cur_h, grid=5):
    """计算参考图在目标图中的覆盖网格数。"""
    import numpy as np
    if H is None:
        return 0
    w_ref, h_ref = ref_size
    count = 0
    for i in range(grid):
        for j in range(grid):
            px = w_ref * (j + 0.5) / grid
            py = h_ref * (i + 0.5) / grid
            pt = np.float32([[[px, py]]])
            try:
                tp = cv2.perspectiveTransform(pt, H)
                tx, ty = tp[0][0]
                if 0 <= tx <= cur_w and 0 <= ty <= cur_h:
                    count += 1
            except Exception:
                pass
    return count


def _save_debug_images(ref_img, cur_img, ref_kp, cur_kp, good_matches, H,
                       ref_mask, cur_mask, transformed_corners, out_dir: Path):
    """保存 7 张 ORB 过程图。"""
    import cv2, numpy as np

    # 00 掩膜图
    ref_mask_overlay = cv2.bitwise_and(ref_img, ref_img, mask=ref_mask)
    cur_mask_overlay = cv2.bitwise_and(cur_img, cur_img, mask=cur_mask)
    cv2.imwrite(str(out_dir / "00_ref_mask.jpg"), ref_mask_overlay)
    cv2.imwrite(str(out_dir / "00_cur_mask.jpg"), cur_mask_overlay)

    # 01 特征点图
    ref_kp_img = cv2.drawKeypoints(ref_img, ref_kp, None, color=(0, 255, 0))
    cur_kp_img = cv2.drawKeypoints(cur_img, cur_kp, None, color=(0, 255, 0))
    cv2.imwrite(str(out_dir / "01_ref_keypoints.jpg"), ref_kp_img)
    cv2.imwrite(str(out_dir / "01_cur_keypoints.jpg"), cur_kp_img)

    # 02 匹配连线图
    match_img = cv2.drawMatches(ref_img, ref_kp, cur_img, cur_kp, good_matches[:200], None,
                                 matchColor=(0, 255, 0), singlePointColor=(255, 0, 0))
    cv2.imwrite(str(out_dir / "02_matches.jpg"), match_img)

    # 03 参考轮廓投影
    cur_h, cur_w = cur_img.shape[:2]
    outline_img = cur_img.copy()
    if transformed_corners is not None:
        pts = transformed_corners.reshape(-1, 2).astype(np.int32)
        cv2.polylines(outline_img, [pts], True, (0, 255, 0), 3)
    cv2.imwrite(str(out_dir / "03_reference_outline.jpg"), outline_img)

    # 04 透视变换后的参考图
    if H is not None:
        warped = cv2.warpPerspective(ref_img, H, (cur_w, cur_h))
        cv2.imwrite(str(out_dir / "04_warped_reference.jpg"), warped)
    else:
        cv2.imwrite(str(out_dir / "04_warped_reference.jpg"), cur_img)

    # 05 混合图
    if H is not None:
        warped = cv2.warpPerspective(ref_img, H, (cur_w, cur_h))
        blended = cv2.addWeighted(cur_img, 0.5, warped, 0.5, 0)
        cv2.imwrite(str(out_dir / "05_blended.jpg"), blended)
    else:
        cv2.imwrite(str(out_dir / "05_blended.jpg"), cur_img)

    # 06 变换后的检测框
    boxes_img = cur_img.copy()
    if transformed_corners is not None:
        pts = transformed_corners.reshape(-1, 2).astype(np.int32)
        cv2.polylines(boxes_img, [pts], True, (0, 255, 0), 2)
        for p in pts:
            cv2.circle(boxes_img, tuple(p), 5, (255, 0, 0), -1)
    cv2.imwrite(str(out_dir / "06_transformed_boxes.jpg"), boxes_img)


def _serialize_boxes(corners) -> list:
    """序列化检测框坐标。"""
    import numpy as np
    if corners is None:
        return []
    pts = corners.reshape(-1, 2)
    return [{"x": float(p[0]), "y": float(p[1])} for p in pts]
