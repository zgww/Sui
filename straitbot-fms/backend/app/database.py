"""SQLAlchemy 会话与基类。SQLite + Native Date。"""
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, declarative_base
from .config import DB_URL, DB_PATH

DB_PATH.parent.mkdir(parents=True, exist_ok=True)

engine = create_engine(
    DB_URL(),
    connect_args={"check_same_thread": False, "timeout": 30},
    pool_pre_ping=True,
)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


def init_db():
    """建表(已存在则跳过) + 为已存在的表补缺失列(SQLite 无原生 ALTER 迁移机制)。"""
    from . import models  # noqa: F401  触发模型注册
    Base.metadata.create_all(bind=engine)
    _ensure_columns()


def _ensure_columns():
    """轻量列迁移: 对比 ORM 定义与实际表结构, 缺失列自动 ALTER ADD。
    SQLite ADD COLUMN 有限制(不能加 NOT NULL 无默认), 故新列都带 default/nullable。
    """
    from sqlalchemy import inspect, text
    insp = inspect(engine)
    for mapper in Base.registry.mappers:
        cls = mapper.class_
        table = cls.__tablename__
        if not insp.has_table(table):
            continue
        existing = {c["name"] for c in insp.get_columns(table)}
        for col in cls.__table__.columns:
            if col.name in existing:
                continue
            # 构造 ALTER 语句
            coltype = col.type.compile(engine.dialect)
            default_sql = ""
            if col.default is not None and col.default.arg is not None:
                val = col.default.arg
                if isinstance(val, str):
                    default_sql = f" DEFAULT '{val}'"
                elif isinstance(val, bool):
                    default_sql = f" DEFAULT {int(val)}"
                else:
                    default_sql = f" DEFAULT {val}"
            elif not col.nullable:
                # 必填列给个兜底默认, 避免 ADD COLUMN 失败
                default_sql = " DEFAULT ''" if "char" in coltype.lower() or "text" in coltype.lower() else " DEFAULT 0"
            ddl = f"ALTER TABLE {table} ADD COLUMN {col.name} {coltype}{default_sql}"
            try:
                with engine.begin() as conn:
                    conn.execute(text(ddl))
                print(f"[migrate] {table}.{col.name} ({coltype}) 已补列")
            except Exception as e:  # noqa: BLE001
                print(f"[migrate] 跳过 {table}.{col.name}: {e}")
