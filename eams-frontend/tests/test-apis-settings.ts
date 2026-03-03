import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import { createPinia } from 'pinia'
import http from '@/plugins/http'

export function withSetup(composable?: () => any) {
  let result
  const app = createApp({
    setup() {
      if (composable) result = composable()
      return () => {}
    }
  })
  // 创建一个空路由
  const router = createRouter({
    history: createWebHistory(import.meta.env.BASE_URL),
    routes: []
  })
  app.use(router)
  // 使用pinia
  app.use(createPinia())
  // 安装http插件
  app.use(http, { router })
  // 挂载
  app.mount(document.createElement('div'))
  // 返回结果与应用实例，用来测试供给和组件卸载
  return [result, app]
}
