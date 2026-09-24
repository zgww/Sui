import http from './http'

// ========== 航点获取 ==========
export const fetchInspection = (rid: number) => http.get(`/api/orb/${rid}/inspection`)
export const importInspection = (rid: number, data: any) => http.post(`/api/orb/${rid}/inspection/import`, { data })
export const getCached = (rid: number) => http.get(`/api/orb/${rid}/inspection/cached`)

// ========== 前往航点 ==========
export const gotoWaypoint = (rid: number, payload: any) => http.post(`/api/orb/${rid}/goto`, payload)

// ========== 拍照存档 ==========
export const captureCalibration = (rid: number, payload: any) => http.post(`/api/orb/${rid}/capture`, payload)

// ========== ORB 比对 ==========
export const orbCompare = (rid: number, payload: any) => http.post(`/api/orb/${rid}/compare`, payload)

// ========== 微挪循环 ==========
export const microMove = (rid: number, payload: any) => http.post(`/api/orb/${rid}/micro-move`, payload)

// ========== 结果图片 ==========
export const resultImageUrl = (path: string) => `/api/orb/1/result-image?path=${encodeURIComponent(path)}`

// ========== 上传定标图文件 ==========
export const uploadCalibrationFile = (rid: number, wpId: string, channel: string, file: File) => {
  const form = new FormData()
  form.append('wp_id', wpId)
  form.append('channel', channel)
  form.append('file', file)
  return http.post(`/api/orb/${rid}/capture/upload`, form)
}
