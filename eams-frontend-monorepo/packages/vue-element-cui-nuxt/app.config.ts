export default defineAppConfig({
  docus: {
    title: 'Vue Element CUI',
    description: 'Vue Element CUI 组件库文档',
    url: 'https://eams-docs.example.com',

    header: {
      logo: true,
      title: 'Vue Element CUI',
      navigation: [
        {
          title: '指南',
          to: '/getting-started'
        },
        {
          title: '组件',
          to: '/components'
        }
      ]
    },

    aside: {
      level: 0,
      collapsed: false
    },

    footer: {
      credits: {
        text: 'EAMS Frontend Team',
        href: ''
      }
    },

    search: {
      enabled: true
    }
  }
})
