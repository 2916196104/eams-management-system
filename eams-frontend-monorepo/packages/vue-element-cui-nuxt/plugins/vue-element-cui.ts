import VueElementCui from '@eams/vue-element-cui'
import ElementPlus from 'element-plus'
// Temporarily disabled to fix PostCSS stack overflow
// import 'element-plus/dist/index.css'
// import '@eams/vue-element-cui/styles'

export default defineNuxtPlugin((nuxtApp) => {
  nuxtApp.vueApp.use(ElementPlus)
  nuxtApp.vueApp.use(VueElementCui)
})
