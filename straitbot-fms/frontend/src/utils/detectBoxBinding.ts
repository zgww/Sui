/**
 * 检测框相关的纯函数（不碰 React / DOM）。
 *
 * 抽出来是为了让下面这几条"容易写错又看不出来"的规则能被回归脚本单独测：
 *
 * - `nextBox`：批量给一批检测框挨个绑测点 / 指定流程时，"设置并切下一个框"
 *   到底跳到谁、走到末尾怎么回绕。
 * - `collectPointUsage`：整棵树的测点占用表（一个测点只能绑一处 + 绑在哪要看得见）。
 *
 * 注：早期"在检测框下挂一个 AlgorithmConfigNode 选单个算法"的模型已下线——检测框
 * 现在直接在 `DetectBoxNode.detect_flow` 上引用一整条**检测算法流程**
 * （`data/prefabs/检测算法`，= 算法 + 参数的检测管线），不再有绑定/解绑子节点
 * 这回事，故这里不再保留 bind/unbind 之类的函数。
 */

/**
 * 「绑定并切下一个检测框」的下一个是谁。
 *
 * 顺序就是**列表顺序**（= 动作点下 children 的顺序）。走到最后一个再点会
 * **回到第一个**（`wrapped: true`）——给一批框挨个绑测点 / 指定流程时，
 * 手不用从屏幕底下挪回顶上；调用方拿到 wrapped 给一句提示，让人知道一轮走完了。
 *
 * 只有一个框时"下一个"就是它自己（wrapped = true），别返回 null 把流程卡死。
 *
 * @param boxes 只需 `{ path }`，与 DetectBoxItem 兼容（不想让这里依赖组件类型）
 */
export function nextBox(
  boxes: { path: string }[],
  curPath: string | null,
): { path: string; index: number; wrapped: boolean } | null {
  if (!boxes.length) return null
  const at = curPath ? boxes.findIndex((b) => b.path === curPath) : -1
  if (at < 0) return { path: boxes[0].path, index: 0, wrapped: false }
  const next = (at + 1) % boxes.length
  return { path: boxes[next].path, index: next, wrapped: boxes.length === 1 || next === 0 }
}

/**
 * 测点 id -> 它在树里被绑的位置（"1 号柜 / 拍照 · AO-RC-057 / 检测框 #2"）。
 *
 * 这张表用来干两件事：
 *
 * 1. **一个测点只能绑一处**。被占了的测点在窗口里不给「绑定」按钮（按钮该先灰掉，
 *    而不是让人点下去再弹个错），真绕过去了（右键菜单、老数据）由工具层再兜一次。
 * 2. **绑在哪要看得见**。只写「已绑定」等于没说——用户真正要的是"绑在哪个航点的
 *    哪个动作点上"，想挪一下才知道去哪找。
 *
 * 扫的是**整棵树**，不只当前动作点：被别的航点 / 别的动作点绑走一样算占用。
 * 测温点（`MeasurePointNode`）也算：它和检测框抢的是同一份测点档案，
 * 同一个测点既当测温点又当检测框的测点，下发下去两份数据会互相打架。
 *
 * 路径里写的是**用户在树上看到的名字**（`properties.name`），没名字才退回 id /
 * 类型 + 序号，免得整行显示成 "undefined / undefined"。
 */
export type PointUsage = Record<string, string>

const ACTION_TEXT: Record<number, string> = { 1: '拍照', 2: '测温', 3: '录像' }

/** 与列表同一个门槛：少于 3 点围不成区域，不成框，也不占测点 */
const boxUsable = (box: any): boolean =>
  Array.isArray(box?.properties?.points) && box.properties.points.length >= 3

/** 先写进去的赢：同一个测点被绑两处本来就是脏数据，别让后扫到的覆盖掉提示 */
const putUsage = (out: PointUsage, id: string, parts: string[]) => {
  if (!id || out[id] !== undefined) return
  out[id] = parts.filter((p) => p && p.trim()).join(' / ')
}

/**
 * @param root 整棵 spec（只读，不修改）
 */
export function collectPointUsage(root: any): PointUsage {
  const out: PointUsage = {}
  const seq = { wp: 0 }

  const walk = (node: any, wp: string, act: string) => {
    if (!node || typeof node !== 'object') return
    const props = node.properties || {}
    const kids: any[] = Array.isArray(node.children) ? node.children : []
    let myWp = wp
    let myAct = act

    if (node.type === 'WaypointNode') {
      myWp = String(props.name || props.wp_id || '').trim() || `航点 #${++seq.wp}`
    }
    if (node.type === 'ActionPointNode') {
      const base = String(props.name || props.steer_point_name || '').trim() || '动作点'
      const t = ACTION_TEXT[Number(props.action_type)]
      myAct = t ? `${base} · ${t}` : base
      // 序号按各自类型单独数，**不看成不成框 / 有没有绑测点**：
      // 列表里第 2 个框就是 #2，不能因为 #1 没绑测点就把它叫 #1。
      let boxNo = 0
      let mpNo = 0
      for (const c of kids) {
        if (c?.type === 'DetectBoxNode') {
          if (!boxUsable(c)) continue
          boxNo += 1
          putUsage(out, String(c?.properties?.point_id || ''),
            [myWp, myAct, `检测框 #${boxNo}`])
        } else if (c?.type === 'MeasurePointNode') {
          mpNo += 1
          putUsage(out, String(c?.properties?.point_id || ''),
            [myWp, myAct, `测温点 #${mpNo}`])
        }
      }
    }
    for (const k of kids) walk(k, myWp, myAct)
  }

  walk(root, '', '')
  return out
}
