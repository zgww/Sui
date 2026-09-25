import React, { createContext, useContext, useState, useCallback, useEffect } from 'react'
import { login as apiLogin, fetchMe } from '../api/auth'

const TOKEN_KEY = 'fms_token'
const ROLE_KEY = 'fms_role'
const USER_KEY = 'fms_user'

interface UserState {
  token: string
  role: string
  username: string
}

interface UserContextValue extends UserState {
  isLogin: boolean
  isEngineer: boolean
  login: (username: string, password: string) => Promise<void>
  refreshMe: () => Promise<void>
  logout: () => void
}

const UserContext = createContext<UserContextValue>(null as any)

export function UserProvider({ children }: { children: React.ReactNode }) {
  const [state, setState] = useState<UserState>(() => ({
    token: localStorage.getItem(TOKEN_KEY) || '',
    role: localStorage.getItem(ROLE_KEY) || '',
    username: localStorage.getItem(USER_KEY) || '',
  }))

  const login = useCallback(async (username: string, password: string) => {
    const { data } = await apiLogin(username, password)
    const next = { token: data.access_token, role: data.role, username: data.username }
    setState(next)
    localStorage.setItem(TOKEN_KEY, next.token)
    localStorage.setItem(ROLE_KEY, next.role)
    localStorage.setItem(USER_KEY, next.username)
  }, [])

  const refreshMe = useCallback(async () => {
    try {
      const { data } = await fetchMe()
      setState((s) => {
        const next = { ...s, role: data.role, username: data.username }
        localStorage.setItem(ROLE_KEY, next.role)
        localStorage.setItem(USER_KEY, next.username)
        return next
      })
    } catch { /* ignore */ }
  }, [])

  const logout = useCallback(() => {
    setState({ token: '', role: '', username: '' })
    localStorage.removeItem(TOKEN_KEY)
    localStorage.removeItem(ROLE_KEY)
    localStorage.removeItem(USER_KEY)
  }, [])

  // 启动时若有 token 刷新一次用户信息
  useEffect(() => {
    if (state.token) refreshMe()
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [])

  const value: UserContextValue = {
    ...state,
    isLogin: !!state.token,
    isEngineer: state.role === 'engineer',
    login,
    refreshMe,
    logout,
  }

  return <UserContext.Provider value={value}>{children}</UserContext.Provider>
}

export function useUser() {
  return useContext(UserContext)
}
