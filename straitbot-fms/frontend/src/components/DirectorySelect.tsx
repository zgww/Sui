import { useMemo } from 'react'
import { TreeSelect } from '@douyinfe/semi-ui'
import type { TreeNodeData } from '@douyinfe/semi-ui/lib/es/tree/interface'
import type { Directory } from '../api/pointArchive'

type Node = { key: string; value: string; label: string; path: string; searchText: string; children: Node[] }
type Props = { directories: Directory[]; value?: string | null; onChange: (id: string | null) => void; excludeId?: string; disabled?: boolean; rootLabel?: string; label?: string }
export default function DirectorySelect({ directories, value, onChange, excludeId, disabled, rootLabel = '根目录', label = '所属目录' }: Props) {
  const tree = useMemo(() => {
    const byId = new Map(directories.map(d => [d.id, d]))
    const children = new Map<string | null, string[]>()
    directories.forEach(d => children.set(d.parent_id, [...(children.get(d.parent_id) || []), d.id]))
    const blocked = new Set<string>(), pending = excludeId ? [excludeId] : []
    while (pending.length) { const id = pending.pop()!; if (blocked.has(id)) continue; blocked.add(id); pending.push(...children.get(id) || []) }
    const root: Node = { key: 'root', value: '', label: rootLabel, path: rootLabel, searchText: rootLabel, children: [] }
    const nodes = new Map<string, Node>()
    directories.filter(d => !blocked.has(d.id)).forEach(d => {
      const names = [d.name], seen = new Set([d.id]); let parent = d.parent_id ? byId.get(d.parent_id) : undefined
      while (parent && !seen.has(parent.id)) { seen.add(parent.id); names.unshift(parent.name); parent = parent.parent_id ? byId.get(parent.parent_id) : undefined }
      const path = names.join(' / ')
      nodes.set(d.id, { key: `directory:${d.id}`, value: d.id, label: d.name, path, searchText: `${path} ${d.code || ''} ${d.id}`, children: [] })
    })
    directories.forEach(d => { const node = nodes.get(d.id); if (node) (d.parent_id ? nodes.get(d.parent_id) || root : root).children.push(node) })
    return [root]
  }, [directories, excludeId, rootLabel])
  return <TreeSelect aria-label={label} style={{ width: '100%' }} disabled={disabled} value={value || ''}
    treeData={tree} defaultExpandedKeys={['root']} autoExpandParent treeNodeFilterProp="searchText"
    filterTreeNode={(input, text) => text.toLocaleLowerCase().includes(input.trim().toLocaleLowerCase())}
    showFilteredOnly showSearchClear searchPlaceholder="搜索目录名称、编码或路径" emptyContent="没有匹配的目录"
    dropdownStyle={{ maxHeight: 360, overflow: 'auto' }}
    renderSelectedItem={(node: TreeNodeData) => <span title={String(node.path)}>{String(node.path)}</span>}
    onChange={v => onChange(v === '' ? null : String(v))} />
}
