"""航点树编排 API：基于 prefab 机制的纯数据航点树。

与规则 prefab（/api/prefab）的区别：
- 根目录固定为 data/prefabs/waypoint（可嵌套目录、多个 *.prefab.json）；
- 只做文件读写与 registry.build 校验，**不激活、不进规则 runtime**，航点树是编排数据；
- 节点类型仅暴露航点系（WaypointNodeBase 子类：分组/航点/动作点/测点…）；
- 支持把巡检任务 JSON 导入成航点树 spec。

目录/文件 CRUD 与树读写这一套（`/dirs` `/files` `/rename` `/move` `/trees`
`/tree` `/node-types`）由 `prefab_store.make_prefab_router` 生成——巡检计划编排
（`/api/plan-prefab`）用的是同一份实现，只是换了根目录与类型过滤。本模块只保留
**航点树独有**的东西：算法目录、地图背景图、云台抓拍图、巡检任务导入。
"""
import json
import re
import uuid
from typing import Any

from fastapi import APIRouter, Body, Depends, File, Form, HTTPException, UploadFile

from ..auth import engineer_only, get_current_user
from ..config import CALIB_DIR, DATA_DIR, WAYPOINT_PREFAB_DIR
from ..prefab import registry
from ..prefab.waypoint_import import inspection_to_spec
from .prefab_store import make_prefab_router

#: 检测框可绑定的算法类型目录（运维可改，所以放 data/ 而不是内置到代码里）
ALGORITHMS_FILE = DATA_DIR / "algorithms.json"

#: 单个算法示意图的 base64 上限（**字符数**）。
#: 示意图只是在算法卡片上"这个算法长什么样"的一张缩略图，前端已压到 320px /
#: JPEG 0.85（通常 20~60KB）。这里是被兜底那一层：algorithms.json 每次开页面
#: 都要**整体**拉一次，塞几 MB 原图进来会把算法列表拖慢；而且它是运维手改的文件，
#: 太大了也就没法再手改了。
ALGO_IMAGE_MAX_CHARS = 512 * 1024

#: 只认这几种浏览器 `canvas.toDataURL()` 能吐出来的图；`svg` 不要放进来——
#: 它是 XML，能带脚本，直接塞进 `<img src="data:image/svg+xml;base64,...">` 有 XSS 面。
_DATA_URL_RE = re.compile(
    r"^data:image/(png|jpeg|jpg|webp|gif|bmp);base64,[A-Za-z0-9+/]+={0,2}$")


def _group_root(name: str) -> dict[str, Any]:
    """新建航点树文件时的初始 spec：一个空的分组当根。"""
    return {
        "name": name,
        "description": "",
        "root": {
            "type": "GroupNode",
            "properties": {"name": name, "enabled": True, "description": ""},
            "children": [],
        },
    }


#: 通用部分（目录/文件 CRUD、树读写、node-types）——与巡检计划编排共用同一份实现
router: APIRouter = make_prefab_router(
    prefix="/api/waypoint-prefab",
    tag="waypoint-prefab",
    root_dir=WAYPOINT_PREFAB_DIR,
    base_filter="WaypointNodeBase",
    root_spec_factory=_group_root,
)


def _root():
    WAYPOINT_PREFAB_DIR.mkdir(parents=True, exist_ok=True)
    return WAYPOINT_PREFAB_DIR


def _safe_rel(rel: Any, *, must_file: bool = False) -> str:
    """抓拍图上传用的一小段路径校验（其余接口走 prefab_store 里那份）。"""
    if not isinstance(rel, str):
        raise HTTPException(status_code=422, detail="rel_path 必填")
    rel = rel.strip().strip("/\\").replace("\\", "/")
    if not rel:
        raise HTTPException(status_code=422, detail="rel_path 必填")
    if must_file and not rel.endswith(".prefab.json"):
        raise HTTPException(status_code=422, detail="prefab 文件必须以 .prefab.json 结尾")
    root = _root().resolve()
    p = (root / rel).resolve()
    if p != root and root not in p.parents:
        raise HTTPException(status_code=400, detail="路径越界")
    if must_file and not p.is_file():
        raise HTTPException(status_code=404, detail=f"文件不存在: {rel}")
    return rel


# ------------------------------------------------------------ 算法类型目录

def read_algorithms() -> dict[str, Any]:
    """读一次 `data/algorithms.json`（**不做进程内缓存**）。

    算法目录是运维数据，改文件刷新页面就该生效，缓存会让"改了 json 却要
    重启后端"这种最容易被当成 bug 的行为成立。

    文件缺失或写坏时不抛异常（那会让整个检视器打不开），而是返回空列表 +
    `warning`，前端照常能用，只是算法下拉没选项。

    ⚠️ 检测流程编排（`/api/detect-prefab`）用的是**同一份**：算法目录是全局的，
    两棵树各读一遍可以，各存一份就会漂。
    """
    if not ALGORITHMS_FILE.is_file():
        return {"ok": False, "algorithms": [], "warning": f"缺少 {ALGORITHMS_FILE}"}
    try:
        raw = json.loads(ALGORITHMS_FILE.read_text(encoding="utf-8"))
    except Exception as exc:  # noqa: BLE001 - json 损坏不该让接口 500
        return {"ok": False, "algorithms": [], "warning": f"解析失败: {exc}"}

    items = raw.get("algorithms") if isinstance(raw, dict) else raw
    out = []
    for a in items or []:
        if not isinstance(a, dict):
            continue
        aid = str(a.get("id") or "").strip()
        if not aid:
            continue  # 没有 id 的条目写进节点也没法反查，直接丢掉
        out.append({
            "id": aid,
            "name": str(a.get("name") or aid),
            "category": str(a.get("category") or "未分类"),
            "color": str(a.get("color") or ""),
            "description": str(a.get("description") or ""),
            # 示意图（data:image/...;base64,...），没上传过就是空串
            "image": str(a.get("image") or ""),
        })
    return {"ok": True, "algorithms": out}


@router.get("/algorithms", dependencies=[Depends(get_current_user)])
def get_algorithms():
    """检测框可绑定的算法类型（见 `read_algorithms`）。"""
    return read_algorithms()


def _write_json_atomic(path, doc: Any) -> None:
    """写 JSON：先写同目录临时文件再 `os.replace`。

    直接 `write_text` 的话，写到一半进程挂了会留一个半截文件，下次连读都读不出来——
    这文件是**运维手改**的数据，损坏的代价很高，所以走原子替换。
    """
    import os
    import tempfile
    tmp = tempfile.NamedTemporaryFile("w", encoding="utf-8", delete=False,
                                      dir=str(path.parent), suffix=".tmp")
    name = tmp.name
    try:
        with tmp as f:
            json.dump(doc, f, ensure_ascii=False, indent=2)
        os.replace(name, path)
    except Exception:
        try:
            os.unlink(name)
        except OSError:
            pass
        raise


@router.post("/algorithms/image", dependencies=[Depends(engineer_only)])
def save_algorithm_image(body: dict[str, Any]):
    """给某个算法存 / 删示意图（base64 data URL 写回 `data/algorithms.json`）。

    body: `{"id": "meter_pointer", "image": "data:image/jpeg;base64,..."}`；
    `image` 传**空串 = 删掉**示意图。

    只改命中那一条的 `image` 字段，**其它字段原样保留**：文件是运维手改的，
    别为了存张图把整份文件 `json.dumps` 重写一遍（那会丢掉手写的换行和排版）。
    """
    if not isinstance(body, dict):
        raise HTTPException(status_code=422, detail="body 必须是对象")
    aid = str(body.get("id") or "").strip()
    image = body.get("image")
    if not aid:
        raise HTTPException(status_code=422, detail="id 必填")
    if not isinstance(image, str):
        raise HTTPException(status_code=422,
                            detail="image 必须是字符串（data:image/...;base64,...），传空串表示删除")
    image = image.strip()
    if image:
        if len(image) > ALGO_IMAGE_MAX_CHARS:
            raise HTTPException(
                status_code=413,
                detail=f"示意图太大：{len(image)} 字符，上限 {ALGO_IMAGE_MAX_CHARS}。请压到 320px 再传")
        if not _DATA_URL_RE.match(image):
            raise HTTPException(status_code=422, detail="示意图必须是 data:image/xxx;base64,... 格式")

    if not ALGORITHMS_FILE.is_file():
        raise HTTPException(status_code=404, detail=f"缺少 {ALGORITHMS_FILE}")
    try:
        doc = json.loads(ALGORITHMS_FILE.read_text(encoding="utf-8"))
    except Exception as exc:  # noqa: BLE001
        raise HTTPException(status_code=400, detail=f"algorithms.json 解析失败: {exc}") from exc

    items = doc.get("algorithms") if isinstance(doc, dict) else doc
    if not isinstance(items, list):
        raise HTTPException(status_code=400, detail="algorithms.json 里没有 algorithms 数组")
    hit = None
    for a in items:
        if isinstance(a, dict) and str(a.get("id") or "").strip() == aid:
            hit = a
            break
    if hit is None:
        raise HTTPException(status_code=404, detail=f"算法目录里没有 id={aid}")

    if image:
        hit["image"] = image
    else:
        hit.pop("image", None)
    _write_json_atomic(ALGORITHMS_FILE, doc)
    return {"ok": True, "id": aid, "has_image": bool(image)}


# ------------------------------------------------------------ 地图背景图上传

# 放在 data/calibration/background 下：main.py 已把整个 CALIB_DIR 挂到
# /data/calibration，子目录随建随取，不用再挂一次静态目录。
BG_DIR = CALIB_DIR / "background"
BG_EXT_OK = ("jpg", "jpeg", "png", "bmp", "webp")


@router.post("/background", dependencies=[Depends(engineer_only)])
async def upload_background(file: UploadFile = File(...)):
    """上传地图背景图，返回可访问的相对路径与图片原始尺寸。

    顺带返回宽高：前端要拿它算"铺满当前轨道大概需要多大的 scale"，
    否则一张 4000px 的图按 scale=1 铺下去会把轨道挤成一小段。
    """
    ext = (file.filename or ".png").rsplit(".", 1)[-1].lower()
    if ext not in BG_EXT_OK:
        raise HTTPException(status_code=415, detail=f"不支持的图片格式: {ext}")
    BG_DIR.mkdir(parents=True, exist_ok=True)
    fname = f"bg_{uuid.uuid4().hex[:8]}.{ext}"
    raw = await file.read()
    (BG_DIR / fname).write_bytes(raw)

    width = height = 0
    try:
        from PIL import Image
        with Image.open(BG_DIR / fname) as im:
            width, height = im.size
    except Exception:  # 读不出尺寸不影响上传，只是前端没法自动估算缩放
        pass
    return {
        "ok": True,
        "path": f"/data/calibration/background/{fname}",
        "width": width,
        "height": height,
    }


# ------------------------------------------------------------ 云台抓拍图上传

CAPTURE_EXT_OK = ("jpg", "jpeg", "png", "bmp", "webp")
CAPTURE_SUBDIR = "images"
#: main.py 把整个 WAYPOINT_PREFAB_DIR 挂到了这里，抓拍图才能被 <img> 直接取到
STATIC_PREFIX = "/data/prefabs/waypoint"


@router.post("/capture", dependencies=[Depends(engineer_only)])
async def upload_capture(file: UploadFile = File(...), rel_path: str = Form(...)):
    """把云台抓拍图存到**该 prefab 文件所在目录**下的 `images/` 里。

    与背景图（`/background`）刻意分开：抓拍图记的是"这棵树的这个动作点拍到了
    什么"，跟着 prefab 走（整棵目录搬走/改名不断链）；背景图是全局素材，
    放 calibration 下给所有地图共用。

    返回两个东西，前端各用一处：
    - `rel`：相对 prefab 文件的路径，写进 `ActionPointNode.imageUrl`；
    - `url`：可直接塞进 `<img src>` 的地址（`<img>` 带不了鉴权头，所以只能
      走静态挂载，这里只是把 rel 拼到挂载点后面）。
    """
    rel = _safe_rel(rel_path, must_file=True)
    ext = (file.filename or ".jpg").rsplit(".", 1)[-1].lower()
    if ext not in CAPTURE_EXT_OK:
        raise HTTPException(status_code=415, detail=f"不支持的图片格式: {ext}")
    out_dir = (_root() / rel).parent / CAPTURE_SUBDIR
    out_dir.mkdir(parents=True, exist_ok=True)
    fname = f"cap_{uuid.uuid4().hex[:8]}.{ext}"
    (out_dir / fname).write_bytes(await file.read())

    filedir = posix_dirname(rel)
    store_rel = f"{CAPTURE_SUBDIR}/{fname}"
    url = f"{STATIC_PREFIX}/{filedir}/{store_rel}" if filedir else f"{STATIC_PREFIX}/{store_rel}"
    return {"ok": True, "rel": store_rel, "url": url, "file": fname}


@router.get("/ptz-pose", dependencies=[Depends(engineer_only)])
def read_ptz_pose():
    """根据 robot.prefab.json 配置的云台信息，**实时读取当前云台位姿**。

    不查数据库、不经过机器人上报：直接用 prefab 里 HkPtzConfig 的连接参数，
    走 HTTP ISAPI（digest 鉴权，无需加载 HCNetSDK）GET PTZ status，现取现用。
    给航点树动作点检视器的「使用当前云台位姿」工具回填 pan/tilt/zoom。
    """
    from pathlib import Path

    from ..config import PREFAB_DIR
    from ..rail.HkPtz import HkPtz

    path = Path(PREFAB_DIR) / "robot.prefab.json"
    if not path.is_file():
        raise HTTPException(404, "robot.prefab.json 不存在，无法读取云台配置")
    try:
        cam = HkPtz.from_prefab(path)
        st = cam.ptz_status()
    except Exception as exc:  # noqa: BLE001 - 读失败要把原因回给页面
        raise HTTPException(502, f"读取云台位姿失败: {exc}")
    return {
        "ok": True,
        "pan": st.get("pan"),
        "tilt": st.get("tilt"),
        "zoom": st.get("zoom"),
    }


def posix_dirname(rel: str) -> str:
    """`a/b/c.prefab.json` -> `a/b`（根目录返回空串，便于拼 URL 时不留双斜杠）。"""
    i = rel.rfind("/")
    return rel[:i] if i > 0 else ""


# ------------------------------------------------------------ 巡检任务导入

@router.post("/import-inspection", dependencies=[Depends(engineer_only)])
def import_inspection(body: Any = Body(...)):
    """把巡检任务 JSON（楼层对象或数组）转换成航点树 spec（不落盘，前端载入后保存）。"""
    try:
        spec = inspection_to_spec(body)
        registry.build(spec["root"])  # 转换结果必须能 build
    except registry.UnknownNodeType as exc:
        raise HTTPException(status_code=400, detail=str(exc))
    except Exception as exc:
        raise HTTPException(status_code=400, detail=f"导入失败: {exc}")

    def _count(node: dict[str, Any]) -> dict[str, int]:
        counts = {"GroupNode": 0, "WaypointNode": 0, "ActionPointNode": 0,
                  "MeasurePointNode": 0}
        def walk(n: dict[str, Any]) -> None:
            counts[n["type"]] = counts.get(n["type"], 0) + 1
            for c in n.get("children") or []:
                walk(c)
        walk(node)
        return counts

    return {"ok": True, "spec": spec, "counts": _count(spec["root"])}
