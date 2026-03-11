export default defineNuxtConfig({
  extends: ['@nuxt/ui-pro'],

  modules: ['@nuxt/content', '@nuxt/ui'],

  vite: {
    optimizeDeps: {
      include: ['@eams/vue-element-cui']
    }
  },

  content: {
    highlight: {
      theme: {
        default: 'github-light',
        dark: 'github-dark'
      },
      preload: ['vue', 'typescript', 'javascript', 'bash']
    }
  },

  components: [
    {
      path: '~/components',
      pathPrefix: false
    }
  ],

  compatibilityDate: '2024-11-01',

  devtools: { enabled: true }
})
