export default defineNuxtConfig({
  extends: ['@nuxt-themes/docus'],

  modules: ['@nuxt/content'],

  vite: {
    optimizeDeps: {
      include: ['@eams/vue-element-cui']
    },
    css: {
      preprocessorMaxWorkers: true,
      postcss: {
        plugins: []
      }
    },
    build: {
      cssCodeSplit: true
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
