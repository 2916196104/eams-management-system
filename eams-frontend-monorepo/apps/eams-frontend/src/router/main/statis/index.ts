const routes = [
	{
		path: '/statis/saleStatis',
		alias: '/statis/sale-stats',
		name: 'SaleStats',
		meta: {
			label: '销售统计'
		},
		component: () => import('@/views/statis/SaleStats.vue')
	}
]

export default routes
