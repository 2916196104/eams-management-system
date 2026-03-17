enum TableType {
	selection = 'selection',
	index = 'index',
	custom = 'custom',
	normal = 'normal',
	handler = 'handler'
}
interface headerBtn<T = void> {
	title: string
	iconPath: string
	handler?: (data?: T) => void
}

interface tableList {
	type: string
	prop?: string
	label: string
	width?: string
	slotName?: string
	// 允许任意其他属性，值为 any 类型
	[key: string]: any
}
interface TableConfig {
	pageName?: string // 网络接口
	headerBtn?: headerBtn[] // 左上角的按钮数组
	tableProperties?: object
	tableList: tableList[]
}
export const F1TableConfig: TableConfig = {
	tableProperties: {
		stripe: true,
		border: true
	},
	tableList: [
		{
			type: TableType.selection,
			width: '50px',
			label: '选择',
			fixed: true
		},
		{
			type: TableType.index,
			width: '60px',
			label: '序号',
			fixed: true
		},
		{
			type: TableType.normal,
			label: '用户名',
			prop: 'name'
		},
		{
			type: TableType.normal,
			label: '真实名',
			prop: 'realname'
		},
		{
			type: TableType.normal,
			label: '手机号码',
			prop: 'cellphone'
		},
		{
			type: TableType.custom,
			label: '状态',
			prop: 'enable',
			width: '80px',
			slotName: 'status'
		},
		{
			type: TableType.handler,
			label: '操作',
			width: '130px'
		}
	]
}
