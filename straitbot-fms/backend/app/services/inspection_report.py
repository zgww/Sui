"""巡检报表生成：按模板格式生成 Excel 巡检报告。

模板结构（来自 2026081801.xls）：
- 表头：大标题 + 任务名称/时间/状态 + 检测点汇总
- 内容按告警等级分块：预警 / 一般告警 / 严重告警 / 危急告警 / 异常点位 / 未参与 / 正常
- 每块九列：设备名称 | 点位名称 | 识别结果 | 告警等级 | 识别时间 | 可见光图片 | 红外图片 | 视频地址 | 采集数据
"""
import logging
from datetime import datetime
from pathlib import Path
from typing import Any, Optional

from openpyxl import Workbook
from openpyxl.styles import Alignment, Border, Font, PatternFill, Side
from openpyxl.utils import get_column_letter
from openpyxl.drawing.image import Image as XLImage
from sqlalchemy.orm import Session

from ..config import DATA_DIR
from ..models import InspectionRun, InspectionActionResult, InspectionPointResult

logger = logging.getLogger(__name__)

# 告警等级分块顺序
SECTIONS = [
    ("预警", "warning"),
    ("一般告警", "general"),
    ("严重告警", "severe"),
    ("危急告警", "critical"),
    ("异常点位", "abnormal"),
    ("未参与任务点位", "skipped"),
    ("正常点位", "normal"),
]

# 列宽（九列）
COL_WIDTHS = [16, 22, 14, 12, 20, 16, 16, 16, 18]

# 样式
THIN_BORDER = Border(
    left=Side(style='thin'),
    right=Side(style='thin'),
    top=Side(style='thin'),
    bottom=Side(style='thin'),
)
HEADER_FILL = PatternFill(start_color='D9E1F2', end_color='D9E1F2', fill_type='solid')
SECTION_FILL = PatternFill(start_color='F2F2F2', end_color='F2F2F2', fill_type='solid')
TITLE_FONT = Font(name='微软雅黑', size=14, bold=True)
HEADER_FONT = Font(name='微软雅黑', size=10, bold=True)
BODY_FONT = Font(name='微软雅黑', size=10)


def _fmt_time(v: Optional[str]) -> str:
    """ISO 时间 -> 本地字符串。"""
    if not v:
        return ''
    try:
        dt = datetime.fromisoformat(v.replace('Z', '+00:00'))
        return dt.strftime('%Y-%m-%d %H:%M:%S')
    except Exception:
        return str(v)


def _resolve_image_path(p: str) -> Optional[Path]:
    """把图片路径（相对/URL）转成本地文件路径。

    支持：
    - `/data/inspection/xxx.jpg` → `DATA_DIR/inspection/xxx.jpg`
    - 完整 URL（http/https）→ 不处理，返回 None
    - 绝对路径 → 直接用
    """
    if not p:
        return None
    # URL 不处理
    if p.startswith('http://') or p.startswith('https://'):
        return None
    # 静态服务路径转本地
    if p.startswith('/data/inspection/'):
        rel = p[len('/data/inspection/'):]
        path = DATA_DIR / 'inspection' / rel
        return path if path.exists() else None
    # 绝对路径
    path = Path(p)
    return path if path.exists() else None


def _insert_image(ws, cell: str, img_path: Path, max_w: int = 120, max_h: int = 90):
    """把图片插入到指定单元格，缩放到合适大小。"""
    try:
        img = XLImage(str(img_path))
        # 按比例缩放
        ratio = min(max_w / img.width, max_h / img.height)
        img.width = int(img.width * ratio)
        img.height = int(img.height * ratio)
        img.anchor = cell
        ws.add_image(img)
    except Exception as e:
        logger.warning('插入图片失败 %s: %s', img_path, e)


def _alert_level(act: InspectionActionResult, point: Optional[InspectionPointResult]) -> str:
    """判定告警等级：normal / warning / general / severe / critical / skipped."""
    # 跳过的动作
    if act.status == 'skipped':
        return 'skipped'
    # 失败的动作
    if act.status == 'failed':
        return 'abnormal'
    # 测点未通过
    if point and point.passed is False:
        # 根据 confidence / algorithm 细分等级（这里简化：统一一般告警）
        return 'general'
    return 'normal'


def _collect_points(db: Session, run_id: int) -> list[dict]:
    """收集所有测点及其所属动作信息，展平成报表行。"""
    actions = db.query(InspectionActionResult).filter(
        InspectionActionResult.run_id == run_id
    ).order_by(InspectionActionResult.floor, InspectionActionResult.waypoint_index,
               InspectionActionResult.action_seq).all()

    points = db.query(InspectionPointResult).filter(
        InspectionPointResult.run_id == run_id
    ).all()

    # action_id -> action
    act_map = {a.id: a for a in actions}

    def _wp_name(act: InspectionActionResult) -> str:
        """从 raw_json 里取航点/设备名（同 inspection_log._waypoint_name）。"""
        raw = act.raw_json
        if isinstance(raw, dict):
            return str(raw.get('steer_point_name') or '')
        return ''

    def _action_type_name(act: InspectionActionResult) -> str:
        """动作类型中文名：拍照/测温/录像。"""
        return {1: '拍照', 2: '测温', 3: '录像'}.get(act.action_type, '')

    def _build_point_name(act: InspectionActionResult, box_seq: int = 0) -> str:
        """构建点位名称：航点名/动作点名称/检测框索引。"""
        wp = _wp_name(act) or f'航点{act.waypoint_index}'
        at = _action_type_name(act) or f'动作{act.action_seq}'
        return f'{wp}/{at}/{box_seq + 1}'

    rows = []
    for p in points:
        act = act_map.get(p.action_result_id)
        if not act:
            continue
        level = _alert_level(act, p)
        # 点位名称：优先用绑定测点名称，无绑定则构建为"航点名/动作点名称/检测框索引"
        point_name = p.label or _build_point_name(act, p.seq or 0)
        rows.append({
            'level': level,
            'device_name': _wp_name(act),
            'point_name': point_name,
            'result': p.algorithm or '',
            'alert_level': '异常' if p.passed is False else '正常',
            'time': _fmt_time(p.created_at),
            'picture': act.picture or '',
            'infrared': act.infrared or '',
            'video': act.media or '',
            'data': f'{p.value}{p.unit or ""}' if p.value is not None else '',
        })

    # 没有测点但有动作的，也加进去（比如拍照动作没有检测框）
    point_action_ids = {p.action_result_id for p in points}
    for act in actions:
        if act.id in point_action_ids:
            continue
        level = _alert_level(act, None)
        rows.append({
            'level': level,
            'device_name': _wp_name(act),
            'point_name': _build_point_name(act, act.action_seq),
            'result': '',
            'alert_level': '',
            'time': _fmt_time(act.finish_time),
            'picture': act.picture or '',
            'infrared': act.infrared or '',
            'video': act.media or '',
            'data': '',
        })

    return rows


def generate_report(db: Session, run_id: int) -> Path:
    """生成巡检报表 Excel，返回文件路径。"""
    run = db.query(InspectionRun).filter(InspectionRun.id == run_id).first()
    if not run:
        raise ValueError('巡检记录不存在')

    rows = _collect_points(db, run_id)

    # 按等级分组
    by_level = {k: [] for _, k in SECTIONS}
    for r in rows:
        by_level.setdefault(r['level'], []).append(r)

    # 统计
    total = len(rows)
    normal = len(by_level.get('normal', []))
    abnormal = len(by_level.get('abnormal', [])) + len(by_level.get('general', []))
    skipped = len(by_level.get('skipped', []))

    wb = Workbook()
    ws = wb.active
    ws.title = '巡检报告'

    # 设置列宽
    for i, w in enumerate(COL_WIDTHS, 1):
        ws.column_dimensions[get_column_letter(i)].width = w

    row_idx = 1

    # 1. 大标题（合并单元格）
    ws.merge_cells(start_row=row_idx, start_column=1, end_row=row_idx, end_column=9)
    cell = ws.cell(row=row_idx, column=1, value='海峡智汇机器人智能巡检系统巡检报告')
    cell.font = TITLE_FONT
    cell.alignment = Alignment(horizontal='center', vertical='center')
    ws.row_dimensions[row_idx].height = 30
    row_idx += 1

    # 2. 任务信息
    info_lines = [
        ('任务名称', run.remark or '全站巡检'),
        ('任务时间', _fmt_time(run.start_time)),
        ('任务状态', {'done': '完成', 'failed': '失败', 'canceled': '取消'}.get(run.status, run.status)),
    ]
    for label, value in info_lines:
        ws.cell(row=row_idx, column=1, value=label).font = HEADER_FONT
        ws.merge_cells(start_row=row_idx, start_column=2, end_row=row_idx, end_column=9)
        ws.cell(row=row_idx, column=2, value=value).font = BODY_FONT
        row_idx += 1

    # 3. 检测点汇总
    summary = (f'本次任务共巡检点位{total}个,正常点位{normal}个,未参与任务{skipped}个,'
               f'识别异常点位{abnormal}个')
    ws.cell(row=row_idx, column=1, value='巡检检测点').font = HEADER_FONT
    ws.merge_cells(start_row=row_idx, start_column=2, end_row=row_idx, end_column=9)
    ws.cell(row=row_idx, column=2, value=summary).font = BODY_FONT
    ws.cell(row=row_idx, column=2).alignment = Alignment(wrap_text=True, vertical='top')
    ws.row_dimensions[row_idx].height = 45
    row_idx += 1

    row_idx += 1  # 空行

    # 4. 各告警等级分块
    HEADERS = ['设备名称', '点位名称', '识别结果', '告警等级', '识别时间',
               '可见光图片', '红外图片', '视频地址', '采集数据']

    for section_name, level_key in SECTIONS:
        items = by_level.get(level_key, [])

        # 分块标题
        ws.merge_cells(start_row=row_idx, start_column=1, end_row=row_idx, end_column=9)
        cell = ws.cell(row=row_idx, column=1, value=section_name)
        cell.font = HEADER_FONT
        cell.fill = SECTION_FILL
        row_idx += 1

        # 表头
        for col, h in enumerate(HEADERS, 1):
            cell = ws.cell(row=row_idx, column=col, value=h)
            cell.font = HEADER_FONT
            cell.fill = HEADER_FILL
            cell.border = THIN_BORDER
            cell.alignment = Alignment(horizontal='center', vertical='center')
        row_idx += 1

        # 数据行
        for item in items:
            values = [
                item['device_name'], item['point_name'], item['result'],
                item['alert_level'], item['time'],
                '', '', item['video'],  # 图片列先留空，后面插入图片
                item['data'],
            ]
            has_image = False
            for col, v in enumerate(values, 1):
                cell = ws.cell(row=row_idx, column=col, value=v)
                cell.font = BODY_FONT
                cell.border = THIN_BORDER
                cell.alignment = Alignment(vertical='center')

            # 插入可见光图片（第6列 F）
            pic_path = _resolve_image_path(item['picture'])
            if pic_path:
                cell_addr = f'F{row_idx}'
                _insert_image(ws, cell_addr, pic_path)
                has_image = True

            # 插入红外图片（第7列 G）
            ir_path = _resolve_image_path(item['infrared'])
            if ir_path:
                cell_addr = f'G{row_idx}'
                _insert_image(ws, cell_addr, ir_path)
                has_image = True

            # 有图片的行加高，否则默认行高
            ws.row_dimensions[row_idx].height = 75 if has_image else 20
            row_idx += 1

        row_idx += 1  # 空行

    # 保存到临时目录
    out_dir = DATA_DIR / "reports"
    out_dir.mkdir(parents=True, exist_ok=True)
    filename = f"inspection_report_{run_id}_{datetime.now().strftime('%Y%m%d_%H%M%S')}.xlsx"
    out_path = out_dir / filename
    wb.save(out_path)

    logger.info("生成巡检报表: %s (run_id=%d, %d 行)", out_path, run_id, len(rows))
    return out_path
