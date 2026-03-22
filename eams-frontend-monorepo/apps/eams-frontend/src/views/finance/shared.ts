import type { MyTableColumn, MyTableOperationsBtn } from '@/components/mytable/type'
import { createMyTableOperationsColumn } from '@/components/mytable/type'

export interface FinanceFilterOption {
	label: string
	value: string
}

export interface FinanceFilterField {
	prop: string
	label: string
	type: 'input' | 'select' | 'date'
	placeholder: string
	options?: FinanceFilterOption[]
}

export interface FinanceActionButton {
	key: string
	label: string
	type?: 'primary' | 'success' | 'warning' | 'danger' | 'info'
}

export interface FinanceListConfig<T extends Record<string, any>> {
	title: string
	description?: string
	filters: FinanceFilterField[]
	initialFilters: Record<string, string>
	batchActions?: FinanceActionButton[]
	columns: MyTableColumn[]
	rows: T[]
	operationButtons?: MyTableOperationsBtn[]
}

const paymentStatusOptions: FinanceFilterOption[] = [
	{ label: '待认款', value: '待认款' },
	{ label: '已认款', value: '已认款' },
	{ label: '已驳回', value: '已驳回' }
]

const requestStatusOptions: FinanceFilterOption[] = [
	{ label: '待审核', value: '待审核' },
	{ label: '已通过', value: '已通过' },
	{ label: '已驳回', value: '已驳回' }
]

export const paymentManagementConfig: FinanceListConfig<Record<string, any>> = {
	title: '款项管理',
	filters: [
		{ prop: 'title', label: '标题', type: 'input', placeholder: '请输入标题' },
		{ prop: 'handler', label: '经手人', type: 'select', placeholder: '请选择经手人', options: [
			{ label: '张老师', value: '张老师' },
			{ label: '李老师', value: '李老师' },
			{ label: '周老师', value: '周老师' }
		] },
		{ prop: 'payer', label: '付款人', type: 'input', placeholder: '请输入付款人' },
		{ prop: 'status', label: '认款状态', type: 'select', placeholder: '请选择认款状态', options: paymentStatusOptions }
	],
	initialFilters: {
		title: '',
		handler: '',
		payer: '',
		status: ''
	},
	batchActions: [
		{ key: 'confirm', label: '批量认款', type: 'primary' },
		{ key: 'reject', label: '批量拒绝', type: 'danger' }
	],
	columns: [
		{ prop: 'paymentType', label: '款项类型', 'min-width': 140 },
		{ prop: 'title', label: '标题', 'min-width': 180 },
		{ prop: 'amount', label: '金额', width: '120px' },
		{ prop: 'student', label: '学员', 'min-width': 120 },
		{ prop: 'handler', label: '经手人', 'min-width': 120 },
		{ prop: 'remark', label: '备注说明', 'min-width': 220, 'show-overflow-tooltip': true },
		{ prop: 'submitTime', label: '提交时间', 'min-width': 180 },
		{ prop: 'status', label: '认款状态', 'min-width': 120 },
		{ prop: 'statusInfo', label: '认款信息', 'min-width': 220, 'show-overflow-tooltip': true }
	],
	rows: [
		{ paymentType: '学费', title: '2026 春季续费', amount: 9800, student: '王晓彤', handler: '张老师', payer: '王女士', remark: '报名钢琴提升班', submitTime: '2026-03-01 09:12', status: '待认款', statusInfo: '等待财务确认' },
		{ paymentType: '教材费', title: '教材补缴', amount: 560, student: '陈奕辰', handler: '李老师', payer: '陈先生', remark: '补领教材与讲义', submitTime: '2026-03-03 14:25', status: '已认款', statusInfo: '财务已确认到账' },
		{ paymentType: '活动费', title: '比赛报名', amount: 1200, student: '林语晨', handler: '周老师', payer: '林女士', remark: '参加省赛报名', submitTime: '2026-03-05 17:40', status: '待认款', statusInfo: '需核对转账截图' },
		{ paymentType: '学费', title: '一对一课包', amount: 6800, student: '赵一鸣', handler: '张老师', payer: '赵先生', remark: '40 节私教课', submitTime: '2026-03-08 10:16', status: '已认款', statusInfo: '已同步学员台账' },
		{ paymentType: '学费', title: '寒假班补费', amount: 2200, student: '苏可欣', handler: '李老师', payer: '苏女士', remark: '寒假精品小班', submitTime: '2026-03-10 16:08', status: '已驳回', statusInfo: '支付凭证金额不符' },
		{ paymentType: '材料费', title: '美术耗材补费', amount: 380, student: '何雨泽', handler: '周老师', payer: '何先生', remark: '补齐画材费用', submitTime: '2026-03-14 11:52', status: '待认款', statusInfo: '待核实线下收款' }
	]
}

export const monthlyClassFeeConfig: FinanceListConfig<Record<string, any>> = {
	title: '月课时费',
	description: '按授课次数统计已结课的课时费，支持导出。',
	filters: [
		{ prop: 'employee', label: '选择员工', type: 'select', placeholder: '请选择员工', options: [
			{ label: '张老师', value: '张老师' },
			{ label: '李老师', value: '李老师' },
			{ label: '周老师', value: '周老师' }
		] },
		{ prop: 'startDate', label: '开始日期', type: 'date', placeholder: '请选择开始日期' },
		{ prop: 'endDate', label: '结束日期', type: 'date', placeholder: '请选择结束日期' }
	],
	initialFilters: {
		employee: '',
		startDate: '',
		endDate: ''
	},
	columns: [
		{ prop: 'name', label: '姓名', 'min-width': 120 },
		{ prop: 'month', label: '月份', 'min-width': 100 },
		{ prop: 'unitClassFee', label: '单节上课费', 'min-width': 130 },
		{ prop: 'classCount', label: '上课课次数', 'min-width': 120 },
		{ prop: 'classSubtotal', label: '上课费小计', 'min-width': 140 },
		{ prop: 'unitTutorFee', label: '单节助教费', 'min-width': 130 },
		{ prop: 'tutorCount', label: '助教课次数', 'min-width': 120 },
		{ prop: 'tutorSubtotal', label: '助教费小计', 'min-width': 140 }
	],
	rows: [
		{ name: '张老师', employee: '张老师', month: '2026-03', unitClassFee: 260, classCount: 42, classSubtotal: 10920, unitTutorFee: 80, tutorCount: 6, tutorSubtotal: 480, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ name: '李老师', employee: '李老师', month: '2026-03', unitClassFee: 220, classCount: 38, classSubtotal: 8360, unitTutorFee: 70, tutorCount: 4, tutorSubtotal: 280, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ name: '周老师', employee: '周老师', month: '2026-03', unitClassFee: 300, classCount: 31, classSubtotal: 9300, unitTutorFee: 90, tutorCount: 8, tutorSubtotal: 720, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ name: '张老师', employee: '张老师', month: '2026-02', unitClassFee: 260, classCount: 37, classSubtotal: 9620, unitTutorFee: 80, tutorCount: 5, tutorSubtotal: 400, startDate: '2026-02-01', endDate: '2026-02-28' },
		{ name: '李老师', employee: '李老师', month: '2026-02', unitClassFee: 220, classCount: 35, classSubtotal: 7700, unitTutorFee: 70, tutorCount: 3, tutorSubtotal: 210, startDate: '2026-02-01', endDate: '2026-02-28' }
	]
}

export const courseRewardConfig: FinanceListConfig<Record<string, any>> = {
	title: '消课课酬',
	description: '按消课次数统计老师的课酬，支持导出。',
	filters: [
		{ prop: 'employee', label: '选择员工', type: 'select', placeholder: '请选择员工', options: [
			{ label: '张老师', value: '张老师' },
			{ label: '李老师', value: '李老师' },
			{ label: '周老师', value: '周老师' }
		] },
		{ prop: 'startDate', label: '开始日期', type: 'date', placeholder: '请选择开始日期' },
		{ prop: 'endDate', label: '结束日期', type: 'date', placeholder: '请选择结束日期' }
	],
	initialFilters: {
		employee: '',
		startDate: '',
		endDate: ''
	},
	columns: [
		{ prop: 'teacherName', label: '老师名', 'min-width': 120 },
		{ prop: 'month', label: '月份', 'min-width': 100 },
		{ prop: 'studentName', label: '学生名', 'min-width': 120 },
		{ prop: 'courseName', label: '课程名', 'min-width': 160 },
		{ prop: 'courseCount', label: '消课数', 'min-width': 100 },
		{ prop: 'unitReward', label: '单节课酬', 'min-width': 120 },
		{ prop: 'rewardSubtotal', label: '消课课酬小计', 'min-width': 150 }
	],
	rows: [
		{ teacherName: '张老师', employee: '张老师', month: '2026-03', studentName: '王晓彤', courseName: '钢琴一对一', courseCount: 8, unitReward: 260, rewardSubtotal: 2080, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ teacherName: '张老师', employee: '张老师', month: '2026-03', studentName: '陈奕辰', courseName: '视唱练耳', courseCount: 6, unitReward: 180, rewardSubtotal: 1080, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ teacherName: '李老师', employee: '李老师', month: '2026-03', studentName: '苏可欣', courseName: '少儿美术', courseCount: 10, unitReward: 220, rewardSubtotal: 2200, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ teacherName: '周老师', employee: '周老师', month: '2026-03', studentName: '赵一鸣', courseName: '奥数提升', courseCount: 7, unitReward: 300, rewardSubtotal: 2100, startDate: '2026-03-01', endDate: '2026-03-31' },
		{ teacherName: '李老师', employee: '李老师', month: '2026-02', studentName: '林语晨', courseName: '油画基础', courseCount: 5, unitReward: 220, rewardSubtotal: 1100, startDate: '2026-02-01', endDate: '2026-02-28' }
	]
}

export const requestManagementConfig: FinanceListConfig<Record<string, any>> = {
	title: '请款管理',
	filters: [
		{ prop: 'project', label: '请款项目', type: 'input', placeholder: '请输入请款项目' },
		{ prop: 'paymentType', label: '请款类型', type: 'select', placeholder: '请选择请款类型', options: [
			{ label: '市场投放', value: '市场投放' },
			{ label: '办公采购', value: '办公采购' },
			{ label: '教学物料', value: '教学物料' }
		] },
		{ prop: 'applicant', label: '申请人', type: 'select', placeholder: '请选择申请人', options: [
			{ label: '张老师', value: '张老师' },
			{ label: '李老师', value: '李老师' },
			{ label: '周老师', value: '周老师' }
		] },
		{ prop: 'payee', label: '收款人', type: 'input', placeholder: '请输入收款人' }
	],
	initialFilters: {
		project: '',
		paymentType: '',
		applicant: '',
		payee: ''
	},
	batchActions: [
		{ key: 'approve', label: '批量通过', type: 'primary' },
		{ key: 'return', label: '批量驳回', type: 'danger' }
	],
	columns: [
		createMyTableOperationsColumn({ label: '操作', 'min-width': 160, align: 'center' }),
		{ prop: 'project', label: '请款项目', 'min-width': 180 },
		{ prop: 'paymentType', label: '款项类型', 'min-width': 120 },
		{ prop: 'applicant', label: '申请人', 'min-width': 120 },
		{ prop: 'payee', label: '收款人', 'min-width': 120 },
		{ prop: 'amount', label: '请款金额', 'min-width': 120 },
		{ prop: 'applyTime', label: '申请时间', 'min-width': 180 },
		{ prop: 'account', label: '收款账号', 'min-width': 180 },
		{ prop: 'description', label: '请款说明', 'min-width': 220, 'show-overflow-tooltip': true },
		{ prop: 'auditStatus', label: '审核状态', 'min-width': 120 },
		{ prop: 'auditInfo', label: '审核信息', 'min-width': 220, 'show-overflow-tooltip': true }
	],
	operationButtons: [
		{ evtname: 'detail', text: '详情', attr: { type: 'primary', link: true } },
		{ evtname: 'approve', text: '通过', attr: { type: 'success', link: true } },
		{ evtname: 'reject', text: '驳回', attr: { type: 'danger', link: true } }
	],
	rows: [
		{ project: '春招地推物料', paymentType: '市场投放', applicant: '张老师', payee: '上海星河广告', amount: 5600, applyTime: '2026-03-02 10:20', account: '6222 8899 1200 3344', description: '地推展架、海报、易拉宝印制', auditStatus: '待审核', auditInfo: '等待财务负责人处理' },
		{ project: '教室白板采购', paymentType: '办公采购', applicant: '李老师', payee: '杭州智学设备', amount: 3800, applyTime: '2026-03-06 13:18', account: '6217 5600 8800 1256', description: '新校区白板和支架采购', auditStatus: '已通过', auditInfo: '已通过，等待打款' },
		{ project: '美术颜料补货', paymentType: '教学物料', applicant: '周老师', payee: '苏州艺材仓', amount: 1260, applyTime: '2026-03-09 15:47', account: '6225 1260 7788 9911', description: '丙烯颜料与调色盘补货', auditStatus: '已驳回', auditInfo: '预算超标，请补充审批单' },
		{ project: '家长会茶歇', paymentType: '办公采购', applicant: '张老师', payee: '南京会务服务部', amount: 980, applyTime: '2026-03-12 09:10', account: '6228 1000 6600 4412', description: '季度家长会茶歇采购', auditStatus: '待审核', auditInfo: '待行政复核发票' }
	]
}

export const saleTrendXAxis = ['03-01', '03-05', '03-09', '03-13', '03-17', '03-21', '03-25', '03-29']

export const saleTrendSeries = [
	{
		name: '报名人数',
		data: [6, 9, 11, 8, 15, 13, 18, 16],
		color: '#3b82f6'
	},
	{
		name: '成交人数',
		data: [4, 6, 8, 5, 11, 10, 14, 12],
		color: '#10b981'
	}
]

export const courseSalesXAxis = ['钢琴一对一', '少儿美术', '奥数提升', '舞蹈启蒙', '口才表达']

export const courseSalesSeries = [
	{
		name: '历史报名量',
		data: [128, 104, 96, 86, 72],
		color: '#f59e0b'
	}
]
