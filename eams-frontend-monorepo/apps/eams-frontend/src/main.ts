import { createApp } from 'vue'
import { createPinia } from 'pinia'
import App from './App.vue'
import router from './router'
import 'element-plus/es/components/message/style/css'
import 'element-plus/es/components/message-box/style/css'
import zhCn from 'element-plus/es/locale/lang/zh-cn'
import './assets/main.css'

// 使用ElementPlus和FcDesigner
import FcDesigner from '@form-create/designer'
import ElementPlus from 'element-plus'

const app = createApp(App)

app.use(createPinia())
app.use(router)

// 使用ElementPlus和FcDesigner
app.use(ElementPlus, { locale: zhCn })
app.use(FcDesigner)

app.mount('#app')

// 安装http插件
import http from './plugins/http'
app.use(http, { router })

// 安装ElIcon
import icon from './plugins/icon'
app.use(icon)
