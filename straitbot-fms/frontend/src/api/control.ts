import http from './http'

// 运动
export const motionMove = (rid: number, command: number, instantSpeed = 0) =>
  http.post(`/api/control/${rid}/motion/move`, { command, instant_speed: instantSpeed })
export const motionSetPose = (rid: number, data: any) => http.post(`/api/control/${rid}/motion/pose`, data)
export const motionGetPose = (rid: number) => http.get(`/api/control/${rid}/motion/pose`)
export const motionHome = (rid: number, goHome = true) => http.post(`/api/control/${rid}/motion/home`, { go_home: goHome })
export const motionEStop = (rid: number, action = true) => http.post(`/api/control/${rid}/motion/estop`, null, { params: { action } })

// 云台
export const ptzGetPose = (rid: number) => http.get(`/api/control/${rid}/ptz/pose`)
export const ptzSetPose = (rid: number, data: any) => http.post(`/api/control/${rid}/ptz/pose`, data)
export const ptzAction = (rid: number, data: any) => http.post(`/api/control/${rid}/ptz/action`, data)

// 拍照
export const cameraCapture = (rid: number, command: number, duration = 0) =>
  http.post(`/api/control/${rid}/camera/capture`, { command, duration })

// 升降杆
export const liftStatus = (rid: number) => http.get(`/api/control/${rid}/lift/status`)

/** 取消当前正在进行的巡检 */
export const cancelInspection = (rid: number) => http.post(`/api/control/${rid}/inspection/cancel`)
export const liftControl = (rid: number, command: number, height = 0) =>
  http.post(`/api/control/${rid}/lift/control`, { command, height })

// 音频
export const audioPlay = (rid: number, command: number, file = '') =>
  http.post(`/api/control/${rid}/audio/play`, { command, file })

// 局放
export const pddDetect = (rid: number, command: number) =>
  http.post(`/api/control/${rid}/pdd/detect`, null, { params: { command } })

// 巡检
export const inspectionTasks = (robotPk: number) => http.get('/api/inspection/tasks', { params: { robot_pk: robotPk } })
export const inspectionCreate = (data: any) => http.post('/api/inspection/tasks', data)
export const inspectionControl = (taskId: number, action: number, targetWp = 0) =>
  http.post(`/api/inspection/tasks/${taskId}/control`, null, { params: { action, target_waypoint: targetWp } })
export const inspectionResults = (robotPk: number) => http.get('/api/inspection/results', { params: { robot_pk: robotPk } })

// 巡检日志 (cmd=103~106 上报查询)
export const inspectionRuns = (robotPk?: number) =>
  http.get('/api/inspection/runs', { params: robotPk ? { robot_pk: robotPk } : {} })
export const inspectionRunDetail = (runId: number) =>
  http.get(`/api/inspection/runs/${runId}`)
export const getCalibImageUrl = (rid: number, inspectionId: string, path: string) =>
  `/api/inspection/calib-images/${rid}/${inspectionId}/${path}`

// 物模型
export const getThingModel = () => http.get('/api/thing-model')
export const saveThingModel = (data: any) => http.put('/api/thing-model', data)
