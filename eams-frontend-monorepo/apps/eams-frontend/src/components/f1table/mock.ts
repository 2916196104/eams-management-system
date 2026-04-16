/**
 * ============================================
 * F1Table 表格组件 - Mock 数据文件
 * ============================================
 * 提供用于测试和演示的模拟数据
 */

/**
 * ============================================
 * 模拟数据接口
 * ============================================
 * 定义 Mock 数据的类型结构
 */
export interface MockData {
	/** 数据唯一标识 ID */
	id: number;

	/** 用户登录名（英文） */
	name: string;

	/** 用户真实姓名（中文） */
	realname: string;

	/** 手机号码 */
	cellphone: string;

	/**
	 * 启用状态
	 * - 1: 启用
	 * - 0: 禁用
	 */
	enable: number;

	/** 用户角色 */
	role: string;

	/** 所属部门 */
	department: string;

	/** 创建时间（格式：YYYY-MM-DD HH:mm:ss） */
	createTime: string;
}

/**
 * ============================================
 * Mock 数据数组
 * ============================================
 * 包含 11 条模拟用户数据，用于表格组件的测试和演示
 *
 * 数据涵盖：
 * - 3 种角色：超级管理员、管理员、普通用户、访客
 * - 6 个部门：技术部、运营部、市场部、财务部、行政部、运维部、产品部、设计部
 * - 两种状态：启用(1)、禁用(0)
 */
const mockData: MockData[] = [
	{
		id: 1,
		name: "admin",
		realname: "管理员",
		cellphone: "13800138000",
		enable: 1,
		role: "超级管理员",
		department: "技术部",
		createTime: "2024-01-15 10:30:00",
	},
	{
		id: 2,
		name: "user01",
		realname: "张三",
		cellphone: "13800138001",
		enable: 1,
		role: "普通用户",
		department: "运营部",
		createTime: "2024-02-20 14:20:00",
	},
	{
		id: 3,
		name: "user02",
		realname: "李四",
		cellphone: "13800138002",
		enable: 0,
		role: "普通用户",
		department: "市场部",
		createTime: "2024-03-10 09:15:00",
	},
	{
		id: 4,
		name: "user03",
		realname: "王五",
		cellphone: "13800138003",
		enable: 1,
		role: "管理员",
		department: "技术部",
		createTime: "2024-03-25 16:45:00",
	},
	{
		id: 5,
		name: "user04",
		realname: "赵六",
		cellphone: "13800138004",
		enable: 1,
		role: "普通用户",
		department: "财务部",
		createTime: "2024-04-05 11:00:00",
	},
	{
		id: 6,
		name: "user05",
		realname: "孙七",
		cellphone: "13800138005",
		enable: 0,
		role: "访客",
		department: "行政部",
		createTime: "2024-04-18 13:30:00",
	},
	{
		id: 7,
		name: "user06",
		realname: "周八",
		cellphone: "13800138006",
		enable: 1,
		role: "普通用户",
		department: "技术部",
		createTime: "2024-05-01 08:45:00",
	},
	{
		id: 8,
		name: "user07",
		realname: "吴九",
		cellphone: "13800138007",
		enable: 1,
		role: "管理员",
		department: "运维部",
		createTime: "2024-05-12 15:20:00",
	},
	{
		id: 9,
		name: "user08",
		realname: "郑十",
		cellphone: "13800138008",
		enable: 0,
		role: "普通用户",
		department: "产品部",
		createTime: "2024-05-25 10:00:00",
	},
	{
		id: 10,
		name: "user09",
		realname: "钱一",
		cellphone: "13800138009",
		enable: 1,
		role: "普通用户",
		department: "设计部",
		createTime: "2024-06-08 14:10:00",
	},
	{
		id: 11,
		name: "user10",
		realname: "陈二",
		cellphone: "13800138010",
		enable: 1,
		role: "访客",
		department: "市场部",
		createTime: "2024-06-20 16:30:00",
	},
];

/**
 * ============================================
 * 分页获取 Mock 数据
 * ============================================
 * 根据页码和每页条数，返回对应的数据切片
 *
 * @param page - 页码，从 1 开始
 * @param pageSize - 每页显示的数据条数
 * @returns 包含当前页数据列表和总数据条数的对象
 *
 * @example
 * // 获取第 1 页，每页 10 条数据
 * const result = getMockData(1, 10);
 * console.log(result.list);   // 前 10 条数据
 * console.log(result.total);  // 总共 11 条数据
 */
export function getMockData(page: number, pageSize: number): { list: MockData[]; total: number } {
	// 计算分页起始位置
	const start = (page - 1) * pageSize;
	// 计算分页结束位置
	const end = start + pageSize;
	// 截取当前页的数据
	const list = mockData.slice(start, end);

	return {
		list,
		total: mockData.length,
	};
}

/**
 * ============================================
 * 获取所有 Mock 数据
 * ============================================
 * 返回完整的 Mock 数据数组
 *
 * @returns 包含所有 11 条数据的数组
 *
 * @example
 * const allData = getAllMockData();
 * console.log(allData.length); // 11
 */
export function getAllMockData(): MockData[] {
	return mockData;
}
