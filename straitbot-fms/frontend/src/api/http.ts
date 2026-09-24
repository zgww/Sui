import axios from 'axios'
import { Toast } from '@douyinfe/semi-ui'

const http = axios.create({ baseURL: '', timeout: 60000 })

http.interceptors.request.use((cfg) => {
  const tok = localStorage.getItem('fms_token')
  if (tok) cfg.headers.Authorization = 'Bearer ' + tok
  return cfg
})

http.interceptors.response.use(
  (resp) => resp,
  (err) => {
    const status = err.response?.status
    const msg = err.response?.data?.detail || err.message || '请求失败'
    if (status === 401) {
      localStorage.removeItem('fms_token')
      localStorage.removeItem('fms_role')
      localStorage.removeItem('fms_user')
      if (window.location.pathname !== '/login') {
        window.location.href = '/login'
      }
    } else {
      Toast.error(typeof msg === 'string' ? msg : JSON.stringify(msg))
    }
    return Promise.reject(err)
  }
)

export default http
