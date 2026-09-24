import http from './http'

// ========== 地图 ==========
export const listMaps = (rid: number) => http.get(`/api/waypoints/robots/${rid}/maps`)
export const createMap = (rid: number, data: any) => http.post(`/api/waypoints/robots/${rid}/maps`, data)
export const updateMap = (mid: number, data: any) => http.put(`/api/waypoints/maps/${mid}`, data)
export const deleteMap = (mid: number) => http.delete(`/api/waypoints/maps/${mid}`)

// ========== 航点 ==========
export const listWaypoints = (mid: number) => http.get(`/api/waypoints/maps/${mid}/list`)
export const createWaypoint = (mid: number, data: any) => http.post(`/api/waypoints/maps/${mid}`, data)
export const updateWaypoint = (wid: number, data: any) => http.put(`/api/waypoints/${wid}`, data)
export const deleteWaypoint = (wid: number) => http.delete(`/api/waypoints/${wid}`)

// ========== 动作 ==========
export const addAction = (wid: number, data: any) => http.post(`/api/waypoints/${wid}/actions`, data)
export const updateAction = (aid: number, data: any) => http.put(`/api/waypoints/actions/${aid}`, data)
export const deleteAction = (aid: number) => http.delete(`/api/waypoints/actions/${aid}`)

// ========== 定标图 ==========
export const uploadCalibration = (wid: number, channel: string, file: File) => {
  const form = new FormData()
  form.append('file', file)
  return http.post(`/api/waypoints/${wid}/calibration?channel=${channel}`, form)
}
export const saveCalibrationBase64 = (wid: number, channel: string, dataurl: string) =>
  http.post(`/api/waypoints/${wid}/calibration/base64`, { channel, dataurl })

// ========== 当前位姿(录点用) ==========
export const currentPose = (rid: number) => http.get(`/api/waypoints/robots/${rid}/current_pose`)

// ========== 导入/导出 ==========
export const exportRobot = (rid: number) => http.get(`/api/waypoints/robots/${rid}/export`)
export const importRobot = (rid: number, data: any, replace = false) =>
  http.post(`/api/waypoints/robots/${rid}/import`, { data, replace })
export const exportFileUrl = (rid: number) => `/api/waypoints/robots/${rid}/export/file`
