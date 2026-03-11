export default defineNuxtConfig({
  modules: ['@nuxt/content', '@nuxtjs/tailwindcss'],

  content: {
    highlight: {
      theme: 'github-dark',
      preload: ['vue', 'typescript', 'javascript', 'bash']
    }
  },

  compatibilityDate: '2024-11-01',

  devtools: { enabled: true }
})
