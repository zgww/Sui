/**
 * Semi 触发元素（Dropdown / Popover / Tooltip）的嵌套规则检查。
 *
 * 背景（真实踩过的坑）：地图工具栏的"显示开关"下拉框曾经**点不开**。
 * 原因是这样写的：
 *
 *     <Dropdown ...>
 *       <Tooltip content="...">
 *         <Button>显示</Button>
 *       </Tooltip>
 *     </Dropdown>
 *
 * Semi 的 Dropdown 底层就是 Tooltip，它把触发用的 onClick 通过
 * cloneElement 合并到**直接子元素**的 props 上；而 Semi 的 Tooltip
 * **不透传**自己收到的未知 props（它只把 children 自己的 props 往外合），
 * 于是这个 onClick 被吃掉，下拉框永远打不开。
 *
 * 规则：Dropdown / Popover / Tooltip 的直接子元素必须是**真实 DOM 节点**
 * （小写标签）或会把 props 透传到 DOM 的组件（Button 等），
 * 绝不能是另一个 Tooltip / Popover / Dropdown。
 *
 * 要同时挂 hover 提示 + 点击菜单，就在中间垫一层普通标签（本项目里是
 * `<span className="wp3-map-trigger">`，见 styles.css）。
 *
 * 用 TypeScript 的真实 AST 来找直接子元素，不靠正则猜（JSX 属性里
 * 还嵌着别的 JSX，正则根本分不清哪个才是 children）。
 *
 * 运行：node scripts/verify-semi-trigger.mjs
 */
import { readdirSync, readFileSync, statSync } from 'node:fs'
import { join, dirname, resolve, relative } from 'node:path'
import { fileURLToPath } from 'node:url'
import { createRequire } from 'node:module'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const srcDir = join(root, 'src')

// typescript 是 CJS：Windows 上直接 import() 一个盘符绝对路径会解析失败，
// 走 createRequire 最稳。
const require = createRequire(import.meta.url)
let ts
try {
  ts = require(join(root, 'node_modules', 'typescript', 'lib', 'typescript.js'))
} catch {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}

/** 会把触发事件挂到直接子元素上的组件 */
const TRIGGERS = new Set(['Dropdown', 'Popover', 'Tooltip'])
/** 会"吃掉"这些事件的组件：收到 props 但不透传给 DOM */
const SWALLOWERS = new Set(['Dropdown', 'Popover', 'Tooltip'])
/** 已知会把 props 透传到真实 DOM 的 Semi 组件（放行） */
const PASSTHROUGH = new Set(['Button', 'IconButton', 'Tag', 'Input', 'Select', 'Switch', 'Checkbox'])

function walkTsx(dir, out = []) {
  for (const name of readdirSync(dir)) {
    const p = join(dir, name)
    const st = statSync(p)
    if (st.isDirectory()) walkTsx(p, out)
    else if (/\.tsx$/.test(name)) out.push(p)
  }
  return out
}

const files = walkTsx(srcDir)
let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }

check('src 下有 tsx 文件可供检查', files.length > 0, `找到 ${files.length} 个`)

for (const file of files) {
  const text = readFileSync(file, 'utf8')
  const sf = ts.createSourceFile(file, text, ts.ScriptTarget.Latest, true, ts.ScriptKind.TSX)

  const visit = (node) => {
    const tag = ts.isJsxOpeningElement(node) || ts.isJsxSelfClosingElement(node)
      ? node.tagName.getText(sf)
      : null
    if (tag && TRIGGERS.has(tag)) {
      // 自闭合（<Tooltip ... />）没有 children，跳过
      if (ts.isJsxOpeningElement(node)) {
        const parent = node.parent // JsxElement（setParentNodes: true）
        if (parent && ts.isJsxElement(parent)) {
          // 第一个"元素型"子节点（跳过纯文本 / 表达式里的注释）
          const first = parent.children.find(
            (c) => ts.isJsxElement(c) || ts.isJsxSelfClosingElement(c),
          )
          if (first) {
            const childTag = (ts.isJsxElement(first) ? first.openingElement : first).tagName.getText(sf)
            const { line } = sf.getLineAndCharacterOfPosition(first.getStart(sf))
            const where = `${relative(root, file)}:${line + 1}`
            const isDom = /^[a-z]/.test(childTag)
            check(`${where} <${tag}> 的直接子元素 <${childTag}> 不该吃掉触发事件`,
              isDom || PASSTHROUGH.has(childTag) || !SWALLOWERS.has(childTag),
              '请中间垫一层普通 DOM 标签（如 <span>）')
          }
        }
      }
    }
    ts.forEachChild(node, visit)
  }
  visit(sf)
}

console.log(`\nSemi 触发元素嵌套检查：${pass} 项通过，${fails.length} 项失败`)
if (fails.length) {
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
