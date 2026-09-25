import http from './http'

// 视频流配置 + 状态(后端代理 ZLMediaKit)
export const getVideoConfig = (rid: number) => http.get(`/api/video/${rid}/config`)
export const listStreams = (rid: number) => http.get(`/api/video/${rid}/streams`)
export const streamStatus = (rid: number, channel = 'visible') =>
  http.get(`/api/video/${rid}/status`, { params: { channel } })

// WebRTC 信令接口地址
export const webrtcSignalUrl = (rid: number, channel = 'visible', ch: number | null = null, ssm: number | null = null) => {
  const params = new URLSearchParams({ channel })
  if (ch != null) params.set('ch', String(ch))
  if (ssm != null) params.set('ssm', String(ssm))
  return `/api/video/${rid}/webrtc?${params.toString()}`
}

// 带鉴权 header 的信令请求
export async function postWebrtcSignal(url: string, sdp: string, token: string | null) {
  const resp = await fetch(url, {
    method: 'POST',
    headers: { 'Content-Type': 'text/plain;charset=utf-8', ...(token ? { Authorization: `Bearer ${token}` } : {}) },
    body: sdp,
  })
  if (!resp.ok) {
    let detail = ''
    try { detail = (await resp.json()).detail || '' } catch { /* */ }
    throw new Error(`信令失败 ${resp.status} ${detail}`)
  }
  return await resp.text()
}
