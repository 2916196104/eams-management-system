const routes = [
  {
    path: '/sample',
    name: 'Sample',
    redirect: { path: '/sample/file' },
    component: () => import('@/views/sample/SampleView.vue'),
    children: [
      {
        name: 'sfile',
        path: '/sample/file',
        component: () => import('@/views/sample/file/FileUpload.vue')
      },
      {
        name: 'sexcel',
        path: '/sample/excel',
        component: () => import('@/views/sample/excel/Excel.vue')
      },
      {
        name: 'sprint',
        path: '/sample/print',
        component: () => import('@/views/sample/print/Print.vue')
      },
      {
        name: 'seditor',
        path: '/sample/editor',
        component: () => import('@/views/sample/editor/Editor.vue')
      },
      {
        name: 'spdf',
        path: '/sample/pdfobject',
        component: () => import('@/views/sample/pdfobject/PdfObject.vue')
      },
      {
        name: 'secharts',
        path: '/sample/echarts',
        component: () => import('@/views/sample/echarts/Echarts.vue')
      },
      {
        name: 'sformcreate',
        path: '/sample/formcreate',
        component: () => import('@/views/sample/formcreate/FormCreate.vue')
      },
      {
        name: 'sflow',
        path: '/sample/flow',
        component: () => import('@/views/sample/flow/Flow.vue')
      },
      {
        name: 'sflowm',
        path: '/sample/flowm',
        component: () => import('@/views/sample/flow/FlowManage.vue')
      },
      {
        name: 'smytable',
        path: '/sample/mytable',
        component: () => import('@/views/sample/mytable/Index.vue')
      },
      {
        name: 'smyform',
        path: '/sample/myform',
        component: () => import('@/views/sample/myform/Index.vue')
      },
      {
        name: 'smysearch',
        path: '/sample/mysearch',
        component: () => import('@/views/sample/mysearch/Index.vue')
      },
      {
        name: 'smydialog',
        path: '/sample/mydialog',
        component: () => import('@/views/sample/mydialog/Index.vue')
      },
      {
        name: 'f1table',
        path: '/sample/f1table',
        component: () => import('@/views/sample/f1table/index.vue')
      }
    ]
  }
]

export default routes
