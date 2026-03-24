export interface OrgNode {
	id: string;
	name: string;
	children?: OrgNode[];
}

export interface EmployeeItem {
	id: string;
	name: string;
	account: string;
	orgId: string;
	orgName: string;
	gender: "男" | "女" | "未知";
	position: string;
	roleName: string;
	personType: "内部" | "外部";
	hireDate: string;
	status: "在职" | "离职";
}

export interface EmployeeQuery {
	orgId?: string;
	keyword?: string;
	status?: "在职" | "离职" | "";
	page: number;
	pageSize: number;
}

export interface EmployeeCreatePayload {
	name: string;
	account: string;
	orgId: string;
	position: string;
	gender: "男" | "女" | "未知";
	education?: string;
	birthday?: string;
	graduateSchool?: string;
	hireDate?: string;
	intro?: string;
	isInternal: boolean;
	isManager: boolean;
	photoUrl?: string;
}

export interface StudentCandidate {
	id: string;
	name: string;
	position: string;
}

export interface EmployeeUpdatePayload extends EmployeeCreatePayload {
	id: string;
}

const orgTree: OrgNode[] = [
	{
		id: "org-root-lf",
		name: "四川职业技术学院龙凤校区",
		children: [
			{ id: "org-hn", name: "HN校区" },
			{ id: "org-zxx", name: "ZXX校区" },
			{ id: "org-jsj", name: "JSJ校区" },
			{
				id: "org-zhs",
				name: "ZHS校区",
				children: [{ id: "org-art", name: "美术学院" }, { id: "org-301", name: "301" }, { id: "org-km", name: "昆明经管校区" }],
			},
		],
	},
	{
		id: "org-zico",
		name: "Zico Eplus少儿国际素养中心",
		children: [{ id: "org-admin", name: "行政部" }, { id: "org-teach", name: "教学部" }, { id: "org-sale", name: "销售部" }],
	},
	{ id: "org-jswx", name: "江苏无锡校区-清北信奥" },
	{ id: "org-jsnj", name: "江苏南京校区-清北信奥" },
];

const orgNameMap = new Map<string, string>();
function walk(nodes: OrgNode[]) {
	nodes.forEach((node) => {
		orgNameMap.set(node.id, node.name);
		if (node.children?.length) walk(node.children);
	});
}
walk(orgTree);

const seedEmployees: EmployeeItem[] = Array.from({ length: 56 }).map((_, i) => {
	const orgIds = [...orgNameMap.keys()];
	const orgId = orgIds[i % orgIds.length];
	return {
		id: `emp-${i + 1}`,
		name: `员工${i + 1}`,
		account: `13${String(100000000 + i * 97).slice(0, 9)}`,
		orgId,
		orgName: orgNameMap.get(orgId) || "",
		gender: i % 3 === 0 ? "男" : i % 3 === 1 ? "女" : "未知",
		position: i % 5 === 0 ? "校长-清北信奥" : i % 5 === 1 ? "教务-清北信奥" : i % 5 === 2 ? "运营-清北信奥" : i % 5 === 3 ? "测试工程师" : "部长",
		roleName: i % 4 === 0 ? "超级管理员" : i % 4 === 1 ? "教务-qb" : i % 4 === 2 ? "运营-qb" : "史志雨",
		personType: i % 6 === 0 ? "外部" : "内部",
		hireDate: `2026-0${(i % 8) + 1}-${String((i % 27) + 1).padStart(2, "0")}`,
		status: i % 11 === 0 ? "离职" : "在职",
	};
});

const db: EmployeeItem[] = [...seedEmployees];
const roleOptions = ["超级管理员", "测试角色", "校长", "管理员", "test1", "学员", "admin111"];

function wait<T>(data: T, ms = 300) {
	return new Promise<T>((resolve) => setTimeout(() => resolve(data), ms));
}

export async function queryOrgTree(): Promise<OrgNode[]> {
	return wait(orgTree, 260);
}

export async function queryEmployeeList(params: EmployeeQuery): Promise<{ list: EmployeeItem[]; total: number }> {
	const keyword = (params.keyword || "").trim().toLowerCase();
	let filtered = db.filter((item) => (params.orgId ? item.orgId === params.orgId : true));
	if (params.status) filtered = filtered.filter((item) => item.status === params.status);
	if (keyword) {
		filtered = filtered.filter((item) => item.name.toLowerCase().includes(keyword) || item.account.toLowerCase().includes(keyword));
	}

	const total = filtered.length;
	const start = (params.page - 1) * params.pageSize;
	const end = start + params.pageSize;
	return wait({ list: filtered.slice(start, end), total }, 360);
}

export async function createEmployee(payload: EmployeeCreatePayload): Promise<EmployeeItem> {
	const item: EmployeeItem = {
		id: `emp-${Date.now()}`,
		name: payload.name,
		account: payload.account,
		orgId: payload.orgId,
		orgName: orgNameMap.get(payload.orgId) || "",
		gender: payload.gender,
		position: payload.position,
		roleName: payload.isManager ? "管理员" : "普通员工",
		personType: payload.isInternal ? "内部" : "外部",
		hireDate: payload.hireDate || new Date().toISOString().slice(0, 10),
		status: "在职",
	};
	db.unshift(item);
	return wait(item, 260);
}

export async function updateEmployee(payload: EmployeeUpdatePayload): Promise<void> {
	const idx = db.findIndex((item) => item.id === payload.id);
	if (idx === -1) return wait(undefined, 200);
	db[idx] = {
		...db[idx],
		name: payload.name,
		account: payload.account,
		orgId: payload.orgId,
		orgName: orgNameMap.get(payload.orgId) || db[idx].orgName,
		gender: payload.gender,
		position: payload.position,
		personType: payload.isInternal ? "内部" : "外部",
		roleName: payload.isManager ? "管理员" : db[idx].roleName,
		hireDate: payload.hireDate || db[idx].hireDate,
	};
	return wait(undefined, 260);
}

export async function resetEmployeePassword(id: string, newPassword: string): Promise<void> {
	void id;
	void newPassword;
	return wait(undefined, 220);
}

export async function queryRoleOptions(): Promise<string[]> {
	return wait(roleOptions, 160);
}

export async function setEmployeeRole(ids: string[], roleName: string): Promise<void> {
	db.forEach((item) => {
		if (ids.includes(item.id)) item.roleName = roleName;
	});
	return wait(undefined, 220);
}

export async function deleteEmployees(ids: string[]): Promise<void> {
	for (let i = db.length - 1; i >= 0; i--) {
		if (ids.includes(db[i].id)) db.splice(i, 1);
	}
	return wait(undefined, 260);
}

export async function transferEmployeeOrg(ids: string[], targetOrgId: string): Promise<void> {
	const orgName = orgNameMap.get(targetOrgId) || "";
	db.forEach((item) => {
		if (ids.includes(item.id)) {
			item.orgId = targetOrgId;
			item.orgName = orgName;
		}
	});
	return wait(undefined, 260);
}

export async function changeEmployeeStatus(ids: string[], status: "在职" | "离职"): Promise<void> {
	db.forEach((item) => {
		if (ids.includes(item.id)) item.status = status;
	});
	return wait(undefined, 240);
}

export async function queryStudentCandidates(keyword = ""): Promise<StudentCandidate[]> {
	const k = keyword.trim().toLowerCase();
	const source = db
		.filter((i) => i.status === "在职")
		.map((i) => ({ id: i.id, name: i.name, position: i.position }))
		.filter((i) => (k ? i.name.toLowerCase().includes(k) : true))
		.slice(0, 100);
	return wait(source, 220);
}

export async function transferToStudent(employeeIds: string[], studentId: string): Promise<void> {
	// mock：保留员工，仅模拟关联成功
	void employeeIds;
	void studentId;
	return wait(undefined, 260);
}

