import http from './http'
import type { ApiResponse } from '../types'

export interface LoginResult {
  access_token: string
  role: string
  username: string
}

export const login = (username: string, password: string) =>
  http.post<LoginResult>('/api/auth/login', { username, password })

export const fetchMe = () => http.get<{ role: string; username: string }>('/api/auth/me')
