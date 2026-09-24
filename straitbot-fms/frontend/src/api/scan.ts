import http from './http'

export const scanNetwork = (cidr: string, apiPort = 6002, timeout = 1.0) =>
  http.post('/api/scan', { cidr, api_port: apiPort, timeout }, { timeout: 300000 })

export const getKnownRobots = () => http.get('/api/scan/known')

export const addBatch = (robots: any[]) => http.post('/api/scan/add', { robots })

export const getLocalNetworks = () => http.get<{ networks: any[]; default: string }>('/api/scan/local_networks')
