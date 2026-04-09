const routes = [
	{
		path: '/finance/paymentManagement',
		alias: '/finance/payment-management',
		name: 'FinancePaymentManagement',
		meta: {
			label: '款项管理'
		},
		component: () => import('@/views/finance/PaymentManagement.vue')
	},
	{
		path: '/finance/financeRecord',
		alias: '/finance/monthly-class-fee',
		name: 'FinanceMonthlyClassFee',
		meta: {
			label: '月课时费'
		},
		component: () => import('@/views/finance/MonthlyClassFee.vue')
	},
	{
		path: '/finance/courseReward',
		alias: '/finance/course-reward',
		name: 'FinanceCourseReward',
		meta: {
			label: '消课课酬'
		},
		component: () => import('@/views/finance/CourseReward.vue')
	},
	{
		path: '/finance/requestManagement',
		alias: '/finance/request-management',
		name: 'FinanceRequestManagement',
		meta: {
			label: '请款管理'
		},
		component: () => import('@/views/finance/RequestManagement.vue')
	}
]

export default routes
