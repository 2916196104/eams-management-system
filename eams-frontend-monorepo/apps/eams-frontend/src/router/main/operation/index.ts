const routes = [
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
