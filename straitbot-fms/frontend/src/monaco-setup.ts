/**
 * Monaco Editor 本地加载配置 (不依赖 CDN)。
 *
 * 使用 Vite ?url 导入获取 worker 文件路径,
 * 兼容 dev 和 production build。
 *
 * 注意: monaco-editor 的 exports 映射为 ./*.js → ./esm/vs/*.js,
 * 所以导入路径不包含 esm/vs/ 前缀。
 */
import * as monaco from 'monaco-editor'
import { loader } from '@monaco-editor/react'

// ?url 让 Vite 正确解析 node_modules 中的 worker 文件路径
import editorWorkerUrl from 'monaco-editor/editor/editor.worker.js?url'
import jsonWorkerUrl from 'monaco-editor/language/json/json.worker.js?url'

// 告诉 Monaco 如何创建 worker
self.MonacoEnvironment = {
  getWorker(_workerId: string, label: string) {
    if (label === 'json') {
      return new Worker(jsonWorkerUrl, { type: 'module' })
    }
    return new Worker(editorWorkerUrl, { type: 'module' })
  },
}

// 使用本地 monaco-editor, 而非 CDN
loader.config({ monaco })

export { monaco }
