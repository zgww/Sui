import { useState, useEffect, forwardRef, useImperativeHandle } from 'react'
import { Select } from '@douyinfe/semi-ui'
import { listRobots } from '../api/robots'
import type { Robot } from '../types'

export interface RobotSelectRef {
  reload: () => Promise<void>
  list: Robot[]
}

interface Props {
  value?: number | string | null
  placeholder?: string
  onChange?: (v: number) => void
  onLoaded?: (list: Robot[]) => void
}

const RobotSelect = forwardRef<RobotSelectRef, Props>(({ value, placeholder = '选择机器人', onChange, onLoaded }, ref) => {
  const [inner, setInner] = useState<number | string | undefined>(value ?? undefined)
  const [list, setList] = useState<Robot[]>([])

  const load = async () => {
    const { data } = await listRobots()
    setList(data)
    onLoaded?.(data)
  }

  useEffect(() => { load() }, [])
  useEffect(() => { setInner(value ?? undefined) }, [value])

  useImperativeHandle(ref, () => ({ reload: load, list }))

  return (
    <Select
      style={{ width: '100%' }}
      value={inner}
      placeholder={placeholder}
      filter
      onChange={(v: any) => { setInner(v); onChange?.(v as number) }}
      optionList={list.map((r) => ({
        value: r.id,
        label: `${r.name} (${r.ip})${r.last_version ? ' v' + r.last_version : ''}`,
      }))}
    />
  )
})

export default RobotSelect
