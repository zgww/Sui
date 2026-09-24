"""鉴权: 密码哈希 + JWT + RBAC。单管理员/操作员模型。"""
from datetime import datetime, timedelta
from typing import Optional
from fastapi import Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer
from jose import jwt, JWTError
from passlib.context import CryptContext
from sqlalchemy.orm import Session

from .config import settings
from .database import get_db
from .models import User

pwd_ctx = CryptContext(schemes=["bcrypt"], deprecated="auto")
oauth2 = OAuth2PasswordBearer(tokenUrl="/api/auth/login")


def hash_pwd(p: str) -> str:
    return pwd_ctx.hash(p)


def verify_pwd(p: str, h: str) -> bool:
    try:
        return pwd_ctx.verify(p, h)
    except Exception:
        return False


def make_token(user: User) -> str:
    exp = datetime.utcnow() + timedelta(minutes=settings.token_expire_minutes)
    payload = {"sub": user.username, "role": user.role, "uid": user.id, "exp": exp}
    return jwt.encode(payload, settings.jwt_secret, algorithm=settings.jwt_algo)


def decode_token(token: str) -> dict:
    return jwt.decode(token, settings.jwt_secret, algorithms=[settings.jwt_algo])


def get_current_user(token: str = Depends(oauth2), db: Session = Depends(get_db)) -> User:
    cred_exc = HTTPException(status_code=status.HTTP_401_UNAUTHORIZED,
                             detail="凭证无效或已过期", headers={"WWW-Authenticate": "Bearer"})
    try:
        payload = decode_token(token)
        username = payload.get("sub")
        if not username:
            raise cred_exc
    except JWTError:
        raise cred_exc
    user = db.query(User).filter(User.username == username).first()
    if not user or not user.enabled:
        raise cred_exc
    return user


def require_role(*roles: str):
    """角色守卫装饰器依赖: require_role('engineer')"""
    def dep(user: User = Depends(get_current_user)) -> User:
        if user.role not in roles:
            raise HTTPException(status_code=status.HTTP_403_FORBIDDEN, detail="权限不足")
        return user
    return dep


# engineer 才能用的快捷依赖
engineer_only = require_role("engineer")
