import { Button, Select } from '@douyinfe/semi-ui'
import { IconLayers, IconRefresh } from '@douyinfe/semi-icons'
import type { Robot } from '../types'
import './robot-switcher.css'

type Props = {
  robots: Robot[]
  value: number | null
  loading: boolean
  error: boolean
  onChange: (id: number | null) => void
  onRefresh: () => void
}

function connection(robot: Robot) {
  if (!robot.enabled) return { label: '已停用', tone: 'disabled' }
  if (robot.online === undefined) return { label: '状态未知', tone: 'unknown' }
  return robot.online ? { label: '在线', tone: 'online' } : { label: '离线', tone: 'offline' }
}

export default function RobotSwitcher({ robots, value, loading, error, onChange, onRefresh }: Props) {
  const selected = robots.find(robot => robot.id === value)
  const options = robots.map(robot => {
    const status = connection(robot)
    const name = robot.name || `机器人 ${robot.id}`
    return {
      value: robot.id,
      searchText: `${name} ${robot.ip} ${robot.robot_id} ${robot.id}`.toLowerCase(),
      label: <div className="robot-switcher-option">
        <span className="robot-switcher-option-icon" aria-hidden="true"><IconLayers /></span>
        <span className="robot-switcher-identity"><span className="robot-switcher-name">{name}</span><span className="robot-switcher-address">{robot.ip} <span>· ID {robot.robot_id}</span></span></span>
        <span className={`robot-switcher-status is-${status.tone}`}><i aria-hidden="true" />{status.label}</span>
      </div>,
    }
  })
  return <Select
    aria-label="切换机器人"
    className="robot-switcher"
    dropdownClassName="robot-switcher-menu"
    value={value ?? undefined}
    placeholder="选择机器人"
    prefix={<span className="robot-switcher-prefix" aria-hidden="true"><IconLayers /></span>}
    optionList={options}
    renderSelectedItem={() => selected ? <span className="robot-switcher-selected" title={`${selected.name || `机器人 ${selected.id}`} · ${selected.ip}`}>
      <span className="robot-switcher-selected-name">{selected.name || `机器人 ${selected.id}`}</span>
      <span className="robot-switcher-selected-meta"><i className={`robot-switcher-dot is-${connection(selected).tone}`} aria-hidden="true" />{connection(selected).label}<span className="robot-switcher-selected-ip"> · {selected.ip}</span></span>
    </span> : <span>机器人 #{value}</span>}
    onChange={id => onChange(id != null ? Number(id) : null)}
    onDropdownVisibleChange={open => { if (open) onRefresh() }}
    filter={(text, option) => String(option.searchText || '').includes(text.trim().toLowerCase())}
    searchPosition="dropdown"
    searchPlaceholder="搜索名称、IP 或 ID"
    maxHeight={320}
    dropdownMatchSelectWidth={false}
    dropdownStyle={{ width: 380, maxWidth: 'calc(100vw - 24px)' }}
    loading={loading}
    outerTopSlot={<div className="robot-switcher-menu-heading"><strong>切换机器人</strong><span>{robots.length} 台设备</span><Button aria-label="刷新机器人列表" size="small" theme="borderless" icon={<IconRefresh />} loading={loading} onClick={onRefresh} /></div>}
    innerBottomSlot={error ? <div className="robot-switcher-error" role="alert">列表刷新失败，请重试{robots.length > 0 ? '；当前显示上次加载的数据' : ''}</div> : undefined}
    emptyContent={<div className="robot-switcher-empty">{loading ? '正在加载机器人…' : error ? '列表加载失败，请点击上方刷新' : robots.length ? '未找到匹配的机器人' : '暂无机器人，请先在机器人列表中添加'}</div>}
  />
}
