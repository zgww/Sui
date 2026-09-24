/** 仿真页后端状态查询 */
export interface SimStatus {
  tcp_connected: boolean
  ws_connected: boolean
  tcp_host: string
  tcp_port: number
  started: boolean
}

export async function fetchSimStatus(): Promise<SimStatus> {
  const r = await fetch('/api/simulation/status')
  if (!r.ok) throw new Error(`status ${r.status}`)
  return r.json() as Promise<SimStatus>
}

/** 场景配置(多套: 轨道 + 障碍物 + RFID) */
export interface ScenarioMeta {
  name: string
  savedAt: string
  obstacleCount: number
  rfidCount: number
  trackKind: 'rect' | 'poly'
}

export interface ScenarioData {
  name: string
  savedAt: string
  track: Record<string, unknown>
  obstacles: Array<{ id: number; s: number; width: number; enabled: boolean }>
  rfids: Array<{ id: number; s: number; tagId: string }>
}

async function j<T>(r: Response): Promise<T> {
  if (!r.ok) {
    const t = await r.text().catch(() => '')
    throw new Error(`${r.status} ${t}`)
  }
  return r.json() as Promise<T>
}

export async function listScenarios(): Promise<ScenarioMeta[]> {
  const r = await fetch('/api/simulation/scenarios')
  return (await j<{ scenarios: ScenarioMeta[] }>(r)).scenarios
}

export async function getScenario(name: string): Promise<ScenarioData> {
  return j<ScenarioData>(await fetch(`/api/simulation/scenarios/${encodeURIComponent(name)}`))
}

export async function saveScenario(name: string, data: { track: Record<string, unknown>; obstacles: unknown[]; rfids: unknown[] }): Promise<void> {
  await j(await fetch(`/api/simulation/scenarios/${encodeURIComponent(name)}`, {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(data),
  }))
}

export async function deleteScenario(name: string): Promise<void> {
  await j(await fetch(`/api/simulation/scenarios/${encodeURIComponent(name)}`, { method: 'DELETE' }))
}
