import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import path from 'path'

// 临时验证用：与 vite.config.ts 相同，但代理指向 :8010 的临时后端，端口 5199
export default defineConfig({
  plugins: [react()],
  resolve: { alias: { '@': path.resolve(__dirname, 'src') } },
  server: {
    host: '127.0.0.1',
    port: 5199,
    proxy: {
      '/api': { target: 'http://127.0.0.1:8010', changeOrigin: true },
      '/data': { target: 'http://127.0.0.1:8010', changeOrigin: true },
      '/ws': { target: 'ws://127.0.0.1:8010', changeOrigin: true, ws: true },
    },
  },
})
