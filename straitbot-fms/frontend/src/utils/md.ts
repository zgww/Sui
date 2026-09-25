/**
 * 极简 Markdown -> HTML 渲染器。
 * 不引入大依赖(markdown-it/marked 体积大)。覆盖 AI 输出常用语法:
 * 标题/粗斜体/列表/代码块/行内代码/段落/分隔线。转义 HTML 防 XSS。
 */
function esc(s: string): string {
  return s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;')
}

function inline(s: string): string {
  // 行内代码(先处理, 避免被后续替换)
  s = s.replace(/`([^`]+)`/g, '<code>$1</code>')
  // 粗体
  s = s.replace(/\*\*([^*]+)\*\*/g, '<strong>$1</strong>')
  s = s.replace(/__([^_]+)__/g, '<strong>$1</strong>')
  // 斜体
  s = s.replace(/\*([^*]+)\*/g, '<em>$1</em>')
  return s
}

export function renderMd(md: string): string {
  if (!md) return ''
  const lines = esc(md).split('\n')
  const out: string[] = []
  let inCode = false
  let codeBuf: string[] = []
  let inUl = false
  let inOl = false

  const closeLists = () => {
    if (inUl) { out.push('</ul>'); inUl = false }
    if (inOl) { out.push('</ol>'); inOl = false }
  }

  for (const line of lines) {
    // 代码块
    if (line.trim().startsWith('```')) {
      if (inCode) {
        out.push('<pre><code>' + codeBuf.join('\n') + '</code></pre>')
        codeBuf = []
        inCode = false
      } else {
        closeLists()
        inCode = true
      }
      continue
    }
    if (inCode) { codeBuf.push(line); continue }

    let m: RegExpMatchArray | null
    // 标题
    if ((m = line.match(/^######\s+(.*)/))) { closeLists(); out.push('<h6>' + inline(m[1]) + '</h6>'); continue }
    if ((m = line.match(/^#####\s+(.*)/)))  { closeLists(); out.push('<h5>' + inline(m[1]) + '</h5>'); continue }
    if ((m = line.match(/^####\s+(.*)/)))   { closeLists(); out.push('<h4>' + inline(m[1]) + '</h4>'); continue }
    if ((m = line.match(/^###\s+(.*)/)))    { closeLists(); out.push('<h3>' + inline(m[1]) + '</h3>'); continue }
    if ((m = line.match(/^##\s+(.*)/)))     { closeLists(); out.push('<h2>' + inline(m[1]) + '</h2>'); continue }
    if ((m = line.match(/^#\s+(.*)/)))      { closeLists(); out.push('<h1>' + inline(m[1]) + '</h1>'); continue }

    // 分隔线
    if (/^---+\s*$/.test(line)) { closeLists(); out.push('<hr/>'); continue }

    // 无序列表
    if ((m = line.match(/^\s*[-*]\s+(.*)/))) {
      if (!inUl) { closeLists(); out.push('<ul>'); inUl = true }
      out.push('<li>' + inline(m[1]) + '</li>')
      continue
    }
    // 有序列表
    if ((m = line.match(/^\s*\d+\.\s+(.*)/))) {
      if (!inOl) { closeLists(); out.push('<ol>'); inOl = true }
      out.push('<li>' + inline(m[1]) + '</li>')
      continue
    }
    // 空行
    if (line.trim() === '') { closeLists(); out.push(''); continue }

    // 普通段落
    closeLists()
    out.push('<p>' + inline(line) + '</p>')
  }
  if (inCode) out.push('<pre><code>' + codeBuf.join('\n') + '</code></pre>')
  closeLists()
  return out.join('\n')
}
