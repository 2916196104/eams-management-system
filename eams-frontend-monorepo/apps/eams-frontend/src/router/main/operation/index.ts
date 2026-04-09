const routes = [
	// 订单管理
	{
		path: "/ops/order-management",
		name: "OperationsOrderManagement",
		component: () => import("@/views/operation/order-management/index.vue"),
	},
	// 订单退款
	{
		path: "/ops/refund-management",
		name: "OperationsRefundManagement",
		component: () => import("@/views/operation/refund-management/index.vue"),
	},
	// 订单评价
	{
		path: "/ops/evaluation-management",
		name: "OperationsEvaluationManagement",
		component: () => import("@/views/operation/evaluation-management/index.vue"),
	},
	// 体验卡管理
	{
		path: "/ops/trialCardManagement",
		name: "TrialCardManage",
		component: () => import("@/views/operation/trialCardManagement/TrialCardManagement.vue"),
	},
	// 积分礼品
	{
		path: "/ops/pointsGift",
		name: "PointsGift",
		component: () => import("@/views/operation/pointsGift/PointsGift.vue"),
	},
	// 积分兑换
	{
		path: "/ops/pointsRedemption",
		name: "PointsRedemption",
		component: () => import("@/views/operation/pointsRedemption/PointsRedemption.vue"),
	},
	// 积分记录
	{
		path: "/ops/pointsRecord",
		name: "PointsRecord",
		component: () => import("@/views/operation/pointsRecord/PointsRecord.vue"),
	},
];
export default routes;
