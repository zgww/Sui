import http from './http'

export interface ExecResult {
  ok: boolean
  stdout: string
  stderr: string
  rc: number
  elapsed_ms: number
  msg: string
}

export function execCmd(rid: number, cmd: string, timeout = 30) {
  return http.post<ExecResult>(`/api/terminal/${rid}/exec`, { cmd, timeout })
}
