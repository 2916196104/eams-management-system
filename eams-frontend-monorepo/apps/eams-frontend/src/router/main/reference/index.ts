const placeholderView = () => import("@/views/common/MenuPlaceholder.vue");

const routes = [
	{
		path: "/course/manage",
		name: "CourseManage",
		meta: {
			label: "课程管理",
			description: "课程基础信息和课程资料维护后续可继续在这里补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/course/subject",
		name: "CourseSubject",
		meta: {
			label: "科目管理",
			description: "科目树、科目属性和启用状态后续可继续扩展。",
		},
		component: placeholderView,
	},
	{
		path: "/ops/order-management",
		name: "OperationsOrderManagement",
		meta: {
			label: "订单管理",
			description: "订单列表、支付状态和订单详情后续可继续接入。",
		},
		component: placeholderView,
	},
	{
		path: "/ops/homework",
		name: "OperationsHomework",
		meta: {
			label: "课后作业",
			description: "课后作业列表、批改与统计后续可继续接入。",
		},
		component: placeholderView,
	},
	{
		path: "/material/manage",
		name: "MaterialManage",
		meta: {
			label: "物料管理",
			description: "物料目录、领用记录和库存能力后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/material/inventory",
		name: "MaterialInventory",
		meta: {
			label: "库存记录",
			description: "库存流水、预警和盘点能力后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/interaction/teacher-review",
		name: "InteractionTeacherReview",
		meta: {
			label: "学评教",
			description: "评价任务、评分结果和汇总分析后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/interaction/message-center",
		name: "InteractionMessageCenter",
		meta: {
			label: "站内消息",
			description: "消息中心、模板通知和已读未读状态后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/org/staff-management",
		name: "OrganizationStaffManagement",
		meta: {
			label: "员工管理",
			description: "员工档案、岗位信息和权限关系后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/org/branch-management",
		name: "OrganizationBranchManagement",
		meta: {
			label: "机构管理",
			description: "机构树、校区配置和组织关系后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/system/system-parameter",
		name: "SystemParameter",
		meta: {
			label: "系统参数",
			description: "系统级参数配置页面后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/system/role-permission",
		name: "SystemRolePermission",
		meta: {
			label: "角色与权限",
			description: "角色、菜单权限和数据权限后续可继续补齐。",
		},
		component: placeholderView,
	},
	{
		path: "/system/wechat-menu",
		name: "SystemWechatMenu",
		meta: {
			label: "公众号菜单",
			description: "公众号菜单配置和发布能力后续可继续补齐。",
		},
		component: placeholderView,
	},
];

export default routes;
