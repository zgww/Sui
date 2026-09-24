/**
 * 检测流程编排的**图标**（与纯逻辑分开，见下面的理由）。
 *
 * 这些图标原本和 `detectSelect.ts` 里的纯函数挤在一个文件里。问题是：
 * 图标要从 `@douyinfe/semi-icons` 引，而这个包的 es/cjs 产物都只能在打包器里
 * 加载（ES 产物是无扩展名的裸相对导入、CJS 产物 require 了 .css），
 * Node 原生 ESM 一个都 import 不了——于是 `verify-detect-prefab.mjs` 想测那几个
 * 纯函数时，会被图标一起带崩（TS17004 / ERR_MODULE_NOT_FOUND / CSS 语法错）。
 *
 * 拆开之后：纯逻辑留在 `detectSelect.ts`（可被 tsc 编译 + node 直接 import），
 * 依赖 React 与组件库的部分放这里（只由页面/画布 import）。
 * **新增图标一律加在本文件**，别再加回 detectSelect.ts。
 */
import type { ReactNode } from 'react'
import {
  IconAlertTriangle, IconCamera, IconCheckList, IconChevronRight,
  IconClock, IconCrop, IconFilter, IconForward, IconHourglass, IconImage,
  IconMail, IconPulse, IconSearch, IconShield, IconStop,
} from '@douyinfe/semi-icons'

/** 检测流程节点类型 -> 图标（画布/树上统一用） */
export const NODE_ICONS: Record<string, ReactNode> = {
  DetectPipelineNode: <IconShield />,
  FrameSourceNode: <IconCamera />,
  FrameSkipNode: <IconHourglass />,
  RoiFilterNode: <IconCrop />,
  TimeWindowNode: <IconClock />,
  ResultFilterNode: <IconFilter />,
  EvidenceNode: <IconImage />,
  AlarmNode: <IconAlertTriangle />,
  NumericAlarmNode: <IconPulse />,
  RangeAlarmNode: <IconPulse />,
  ForwardNode: <IconForward />,
  SmsNotifyNode: <IconMail />,
  EmailNotifyNode: <IconMail />,
}

/** 画布上"加子节点"按钮等地方要直接用的图标 */
export { IconChevronRight, IconCheckList, IconStop, IconSearch }
