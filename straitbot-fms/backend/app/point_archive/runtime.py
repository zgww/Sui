"""Application singleton; tests inject independent stores into router dependencies."""
import logging
from ..config import ARCHIVE_DIR
from .schema import empty_snapshot
from .store import ArchiveStore

archive_store = ArchiveStore(ARCHIVE_DIR / "archive.json")


def startup_archive():
    archive_store.acquire_writer()
    try:
        if archive_store.path.exists():
            archive_store.load()
        else:
            archive_store.initialize(empty_snapshot())
    except Exception:
        archive_store.last_error = "测点档案加载失败，请检查文件或恢复备份"
        logging.exception("Point archive is unavailable; other FMS services remain running")


def get_archive_store():
    return archive_store
