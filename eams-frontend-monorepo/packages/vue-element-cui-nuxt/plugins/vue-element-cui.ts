import VueElementCui from '@eams/vue-element-cui'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import '@eams/vue-element-cui/styles'

export default defineNuxtPlugin((nuxtApp) => {
  nuxtApp.vueApp.use(ElementPlus)
  nuxtApp.vueApp.use(VueElementCui)
})
