/**
 * 枚举配置（第四棵 prefab 树）的回归测试。
 *
 * 锁三件事：
 * 1. **纯函数**（`utils/enumSpec.ts`）——选项提取的过滤规则、键的回落、树上
 *    标签/摘要、结构操作。这些错了不报错，只会"看错"或"下拉框里少一项"，
 *    必须能算。
 * 2. **前后端口径一致**——`enumSpec.ts` 的三条过滤（停用跳过 / 空键跳过 /
 *    label 回落 name）与后端 `enum_catalog.py` 必须逐条对齐，否则树上配好的
 *    项在下拉框里点不到。源码级断言盯着两边的关键字。
 * 3. **接线**——枚举树挂进路由、告警中心的类型下拉真的去取枚举。删掉这些
 *    不会有任何类型错误，只能在这里锁。
 *
 * **不手抄源码**：用 tsc 把真实 .ts 编到临时目录再 import。
 * 运行：node scripts/verify-enum-spec.mjs
 */
import { execFileSync } from 'node:child_process'
import { mkdtempSync, rmSync, existsSync, writeFileSync, readFileSync, readdirSync } from 'node:fs'
import { tmpdir } from 'node:os'
import { join, dirname, resolve } from 'node:path'
import { pathToFileURL, fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const root = resolve(here, '..')
const out = mkdtempSync(join(tmpdir(), 'enumspec-'))

const tscEntry = join(root, 'node_modules', 'typescript', 'bin', 'tsc')
if (!existsSync(tscEntry)) {
  console.error('找不到本地 typescript，请先在 frontend/ 下 npm install')
  process.exit(1)
}
try {
  execFileSync(process.execPath,
    [tscEntry, 'src/utils/enumSpec.ts', '--outDir', out,
      '--target', 'es2020', '--module', 'es2020', '--skipLibCheck',
      '--moduleResolution', 'bundler'],
    { cwd: root, stdio: 'pipe' })
} catch (e) {
  console.error('编译失败：\n', e.stdout?.toString() || '', e.stderr?.toString() || '', e.message)
  process.exit(1)
}
writeFileSync(join(out, 'package.json'), JSON.stringify({ type: 'module' }))

/** tsc 不给相对导入补 `.js`，Node 原生 ESM 必须要，产物里补一遍 */
const fixExt = (dir) => {
  for (const name of readdirSync(dir, { withFileTypes: true })) {
    const p = join(dir, name.name)
    if (name.isDirectory()) { fixExt(p); continue }
    if (!name.name.endsWith('.js')) continue
    const src = readFileSync(p, 'utf8')
    const next = src.replace(/(from\s+['"])(\.[^'"]*?)(['"])/g,
      (m, a, spec, c) => (spec.endsWith('.js') ? m : `${a}${spec}.js${c}`))
    if (next !== src) writeFileSync(p, next)
  }
}
fixExt(out)

const modPath = ['utils/enumSpec.js', 'enumSpec.js']
  .map((p) => join(out, p)).find((p) => existsSync(p))
if (!modPath) {
  console.error('编译产物里找不到 enumSpec.js：', out)
  process.exit(1)
}
const E = await import(pathToFileURL(modPath).href)
const {
  ENUM_NODE_TYPE, ENUM_ITEM_TYPE, ENUM_TYPE_LABEL, ENUM_TYPE_COLOR,
  enumTypeLabel, enumOptionsOf, enumKeyOf, walkEnumTree, findEnumOptions,
  toOptionList, enumNodeLabel, enumNodeSummary,
  appendChildNode, insertSiblingNode, defaultsFrom,
} = E

let pass = 0
const fails = []
const check = (n, c, extra = '') => { c ? pass++ : fails.push(`${n} ${extra}`) }
const eq = (n, got, want) => check(n, got === want, `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)
const deep = (n, got, want) => check(n, JSON.stringify(got) === JSON.stringify(want),
  `got=${JSON.stringify(got)} want=${JSON.stringify(want)}`)

/* ============================================================ 1. 类型名与配色 */

eq('1.1 枚举类型名', enumTypeLabel(ENUM_NODE_TYPE), '枚举')
eq('1.2 枚举项类型名', enumTypeLabel(ENUM_ITEM_TYPE), '枚举项')
eq('1.3 未知类型回落到类型名本身（不显示"undefined"）', enumTypeLabel('Foo'), 'Foo')
check('1.4 两个类型都有中文名', !!ENUM_TYPE_LABEL[ENUM_NODE_TYPE] && !!ENUM_TYPE_LABEL[ENUM_ITEM_TYPE])
check('1.5 两个类型都有配色', !!ENUM_TYPE_COLOR[ENUM_NODE_TYPE] && !!ENUM_TYPE_COLOR[ENUM_ITEM_TYPE])

/* ============================================================ 2. 选项提取（与后端同口径） */

const item = (name, label = '', desc = '', enabled = true) => ({
  type: ENUM_ITEM_TYPE,
  properties: { name, label, description: desc, enabled },
  children: [],
})
const enumNode = (name, children) => ({
  type: ENUM_NODE_TYPE,
  properties: { name, label: name, enabled: true, description: '' },
  children,
})

deep('2.1 选项 = {value:name, label, description}',
  enumOptionsOf(enumNode('k', [item('a', '甲', '说明A')])),
  [{ value: 'a', label: '甲', description: '说明A' }])

deep('2.2 停用的项不进下拉框（暂时停用 ≠ 停用但仍显示）',
  enumOptionsOf(enumNode('k', [item('a', '甲'), item('b', '乙', '', false)])).map((o) => o.value),
  ['a'])

deep('2.3 没填键的项不进下拉框（筛不出东西，只会多一条空行）',
  enumOptionsOf(enumNode('k', [item('', '空键'), item('a', '甲')])).map((o) => o.value),
  ['a'])

eq('2.4 label 为空时回落 name（前端拿到的显示文本一定非空）',
  enumOptionsOf(enumNode('k', [item('a', '')]))[0].label, 'a')

deep('2.5 只收直接子级的枚举项（孙级不混进来）',
  enumOptionsOf(enumNode('k', [item('a', '甲'), { ...item('b', '乙'), children: [item('c', '丙')] }]))
    .map((o) => o.value),
  ['a', 'b'])

deep('2.6 非枚举项子节点忽略', enumOptionsOf(enumNode('k', [{ type: 'Sequence', properties: {} }])), [])

/* ============================================================ 3. 键与查找 */

eq('3.1 键取 EnumNode.name', enumKeyOf(enumNode('告警类型', [])), '告警类型')
eq('3.2 没填 name 时回落文件名', enumKeyOf(enumNode('', []), '告警类型'), '告警类型')
eq('3.3 空 key 不命中', findEnumOptions({ root: enumNode('告警类型', [item('a')]) }, '').found, false)

{
  const spec = { root: enumNode('告警类型', [item('a', '甲')]) }
  const r = findEnumOptions(spec, '告警类型')
  check('3.4 按 key 命中', r.found === true)
  deep('3.5 命中的选项', r.options.map((o) => o.value), ['a'])
}
{
  // 配了但一项没填：found=true 而 options=[] —— 与"没配过"是两件事
  const r = findEnumOptions({ root: enumNode('告警类型', []) }, '告警类型')
  check('3.6 空枚举也算子 found', r.found === true && r.options.length === 0)
}
{
  const r = findEnumOptions({ root: enumNode('别的', [item('a')]) }, '告警类型')
  check('3.7 key 不匹配时 found=false', r.found === false && r.options.length === 0)
}
{
  // 同 key 多份（嵌套）：按值去重、保首次出现顺序，否则下拉框会有两行一样的值
  const spec = { root: { type: ENUM_NODE_TYPE, properties: { name: '告警类型', enabled: true }, children: [
    item('x', 'X'),
    enumNode('告警类型', [item('x', '重复'), item('y', 'Y')]),
  ] } }
  const r = findEnumOptions(spec, '告警类型')
  deep('3.8 同 key 多份去重', r.options.map((o) => o.value), ['x', 'y'])
  eq('3.9 去重时首次出现者胜', r.options[0].label, 'X')
}
eq('3.10 walkEnumTree 含根自己', walkEnumTree(enumNode('k', [item('a')])).length, 2)

deep('3.11 选项 -> Select optionList', toOptionList([{ value: 'a', label: '甲', description: '' }]),
  [{ value: 'a', label: '甲' }])

/* ============================================================ 4. 展示 */

eq('4.1 树上标签取显示名', enumNodeLabel(item('a', '甲')), '甲')
eq('4.2 没显示名时取键', enumNodeLabel(item('a', '')), 'a')
eq('4.3 都没有时取类型中文名', enumNodeLabel({ type: ENUM_NODE_TYPE, properties: {} }), '枚举')
eq('4.4 枚举节点摘要 = 项数', enumNodeSummary(enumNode('k', [item('a'), item('b')])), '2 项')
eq('4.5 空枚举不显示摘要（"0 项"是噪声）', enumNodeSummary(enumNode('k', [])), '')
eq('4.6 显示名就是键时不再重复一遍', enumNodeSummary(item('a', 'a')), '')
eq('4.7 显示名与键不同时补一句键', enumNodeSummary(item('a', '甲')), 'a')

/* ============================================================ 5. 结构操作 */

{
  const spec = { root: enumNode('k', []) }
  check('5.1 追加子节点', appendChildNode(spec, 'root', item('a', '甲')) === true)
  eq('5.2 追加后路径', spec.root.children.length, 1)
  check('5.3 父级不存在时失败（不静默假装成功）',
    appendChildNode(spec, 'root/children/9', item('b')) === false)
}
{
  const spec = { root: enumNode('k', [item('a'), item('c')]) }
  check('5.4 在前插入同级', insertSiblingNode(spec, 'root/children/1', item('b'), 'before') === true)
  deep('5.5 插入后的顺序', spec.root.children.map((c) => c.properties.name), ['a', 'b', 'c'])
  check('5.6 在后插入同级', insertSiblingNode(spec, 'root/children/0', item('z'), 'after') === true)
  eq('5.7 后插落在目标之后', spec.root.children[1].properties.name, 'z')
  check('5.8 根节点没有同级，插入必然失败',
    insertSiblingNode(spec, 'root', item('x'), 'before') === false)
}
deep('5.9 defaultsFrom 跳过 type / children',
  Object.keys(defaultsFrom({ properties: { type: { default: '' }, children: { default: [] }, name: { default: 'x' } } })),
  ['name'])

/* ============================================================ 6. 后端口径一致 */

const pyNodes = readFileSync(resolve(root, '../backend/app/prefab/nodes/enum.py'), 'utf8')
check('6.1 后端有 EnumNodeBase（中间基类）', pyNodes.includes('class EnumNodeBase(NodeBase)'))
check('6.2 中间基类不注册（__type_name__ = None）',
  /class EnumNodeBase[\s\S]{0,200}__type_name__: ClassVar\[str \| None\] = None/.test(pyNodes))
check('6.3 EnumNode 三个字段齐全',
  /class EnumNode\(EnumNodeBase\)[\s\S]{0,900}name: str[\s\S]{0,400}label: str[\s\S]{0,400}description: str/.test(pyNodes))
check('6.4 EnumItemNode 三个字段齐全',
  /class EnumItemNode\(EnumNodeBase\)[\s\S]{0,900}name: str[\s\S]{0,400}label: str[\s\S]{0,400}description: str/.test(pyNodes))

const pyCatalog = readFileSync(resolve(root, '../backend/app/prefab/enum_catalog.py'), 'utf8')
check('6.5 后端跳过停用的项', pyCatalog.includes('enabled') && pyCatalog.includes('continue'))
check('6.6 后端跳过空键的项', pyCatalog.includes('if not name'))
check('6.7 后端 label 回落 name', pyCatalog.includes('.strip() or name'))
check('6.8 后端 found 与 options 非空分开表达', pyCatalog.includes('"found"'))
check('6.9 坏文件不抛异常（下拉框不该让页面 500）', pyCatalog.includes('except Exception'))

const pyRouter = readFileSync(resolve(root, '../backend/app/routers/enum_prefab.py'), 'utf8')
check('6.10 走通用 prefab 工厂（与另外三棵树同一套 CRUD）',
  pyRouter.includes('make_prefab_router'))
check('6.11 类型目录按 EnumNodeBase 过滤（不串门）',
  pyRouter.includes('base_filter="EnumNodeBase"'))
check('6.12 有 /options 取选项的接口', pyRouter.includes('@router.get("/options"'))

const pyConfig = readFileSync(resolve(root, '../backend/app/config.py'), 'utf8')
check('6.13 枚举目录独立配置', pyConfig.includes('ENUM_PREFAB_DIR'))
check('6.14 启动时建目录', pyConfig.includes('ENUM_PREFAB_DIR,\n           BOOT_PREFAB_DIR')
  || /DETECT_PREFAB_DIR, ENUM_PREFAB_DIR/.test(pyConfig))

const pyMain = readFileSync(resolve(root, '../backend/app/main.py'), 'utf8')
check('6.15 路由挂进 app', pyMain.includes('enum_prefab.router'))
check('6.16 模块已 import', pyMain.includes('enum_prefab'))

/* ============================================================ 7. 前端接线 */

const alarms = readFileSync(resolve(root, 'src/views/Alarms.tsx'), 'utf8')
check('7.1 告警中心类型下拉取枚举配置', alarms.includes('getEnumOptions'))
check('7.2 引用的键是「告警类型」', alarms.includes("ALARM_TYPE_ENUM_KEY = '告警类型'"))
check('7.3 取不到时回落到库里实际出现过的值（不会只剩"全部类型"）',
  /enumTypes\.length[\s\S]{0,120}meta\.types/.test(alarms))
check('7.4 取数失败不报错（下拉框是装饰性控件）', alarms.includes('.catch(() => {})'))

const page = readFileSync(resolve(root, 'src/views/EnumPrefab.tsx'), 'utf8')
check('7.5 页面拉本棵树的 node-types', page.includes('getEnumNodeTypes'))
check('7.6 拖拽复用 specTree 的落点判定（不自己判 dropPosition）',
  page.includes('resolveDropKind') && page.includes('moveNodeInSpec'))
check('7.7 结构操作走纯函数模块', page.includes('appendChildNode') && page.includes('insertSiblingNode'))
check('7.8 右键菜单放过菜单内部点击（否则菜单项点了没反应）',
  page.includes('className="en-ctx"') && page.includes('e.stopPropagation()'))

const router = readFileSync(resolve(root, 'src/router/index.tsx'), 'utf8')
check('7.9 路由已注册', router.includes("path: 'enum-prefab'"))
check('7.10 侧栏菜单已注册', router.includes("path: '/enum-prefab'"))

/* ============================================================ 8. 默认数据 */

const seed = resolve(root, '../backend/data/prefabs/枚举/告警类型.prefab.json')
if (existsSync(seed)) {
  const spec = JSON.parse(readFileSync(seed, 'utf8'))
  eq('8.1 默认枚举的根是 EnumNode', spec.root.type, 'EnumNode')
  eq('8.2 默认枚举的键对得上告警中心', spec.root.properties.name, '告警类型')
  check('8.3 默认枚举有选项', (spec.root.children || []).length > 0)
}

/* ============================================================ 汇总 */

rmSync(out, { recursive: true, force: true })
if (fails.length) {
  console.error(`\n枚举配置回归：${pass} 项通过，${fails.length} 项失败`)
  for (const f of fails) console.error('  ✗ ' + f)
  process.exit(1)
}
console.log(`枚举配置回归：${pass} 项通过，0 项失败`)
