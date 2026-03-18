export interface MockData {
	id: number;
	name: string;
	realname: string;
	cellphone: string;
	enable: number;
	role: string;
	department: string;
	createTime: string;
}

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

export function getMockData(page: number, pageSize: number): { list: MockData[]; total: number } {
	const start = (page - 1) * pageSize;
	const end = start + pageSize;
	const list = mockData.slice(start, end);
	return {
		list,
		total: mockData.length,
	};
}

export function getAllMockData(): MockData[] {
	return mockData;
}
