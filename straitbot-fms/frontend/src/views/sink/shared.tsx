import React from 'react'

// ========== 下沉静态页面 — 共享展示小组件 ==========

/** 只读描述栅格（label + value 逐行） */
export function DescGrid({ items }: { items: { label: string; value: React.ReactNode }[] }) {
  return (
    <div style={{ display: 'grid', gridTemplateColumns: '1fr', border: '1px solid var(--semi-color-border)', borderRadius: 6, overflow: 'hidden', marginBottom: 12 }}>
      {items.map((it) => (
        <div key={it.label} style={{ display: 'flex', borderBottom: '1px solid var(--semi-color-border)', background: '#fff' }}>
          <div style={{ width: 120, flex: 'none', background: 'var(--semi-color-fill-0)', color: 'var(--semi-color-text-2)', padding: '7px 12px', fontSize: 13, borderRight: '1px solid var(--semi-color-border)' }}>
            {it.label}
          </div>
          <div style={{ padding: '7px 12px', fontSize: 13, flex: 1, minWidth: 0, wordBreak: 'break-all' }}>{it.value}</div>
        </div>
      ))}
    </div>
  )
}

/** 表单行（静态示意：label + 控件插槽） */
export function FormRow({ label, required, children, hint }: {
  label: string
  required?: boolean
  children: React.ReactNode
  hint?: string
}) {
  return (
    <div style={{ display: 'flex', alignItems: 'flex-start', marginBottom: 14 }}>
      <div style={{ width: 110, flex: 'none', textAlign: 'right', paddingRight: 12, color: 'var(--semi-color-text-2)', lineHeight: '30px', fontSize: 13 }}>
        {required && <span style={{ color: 'var(--semi-color-danger)', marginRight: 2 }}>*</span>}
        {label}
      </div>
      <div style={{ flex: 1, minWidth: 0 }}>
        {children}
        {hint && <div style={{ fontSize: 12, color: 'var(--semi-color-text-2)', marginTop: 4, lineHeight: 1.5 }}>{hint}</div>}
      </div>
    </div>
  )
}

/** 分区标题 */
export function SectionTitle({ children }: { children: React.ReactNode }) {
  return (
    <div style={{ fontSize: 13, fontWeight: 600, padding: '4px 0 10px', display: 'flex', alignItems: 'center', gap: 6 }}>
      <span style={{ width: 3, height: 12, borderRadius: 2, background: 'var(--semi-color-primary)', display: 'inline-block' }} />
      {children}
    </div>
  )
}
