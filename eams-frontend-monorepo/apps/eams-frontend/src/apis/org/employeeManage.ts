import { useHttp } from "@/plugins/http";

export interface OrgNode {
	id: string;
	name: string;
	children?: OrgNode[];
}

export interface EmployeeItem {
	id: string;
	name: string;
	account: string;
	mobile: string;
	orgId: string;
	orgName: string;
	gender: "男" | "女" | "未知";
	position: string;
	roleName: string;
	personType: "内部" | "外部";
	hireDate: string;
	status: "在职" | "离职";
	isManager?: number;
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
	positionId?: number | string;
	position?: string;
	gender: "男" | "女" | "未知";
	education?: string;
	degree?: number;
	birthday?: string;
	graduateSchool?: string;
	school?: string;
	hireDate?: string;
	intro?: string;
	remark?: string;
	assistantFee?: number;
	classFee?: number;
	isInternal: boolean;
	isManager: boolean;
	password?: string;
	photoUrl?: string;
	headImg?: string;
}

export interface EmployeeUpdatePayload extends EmployeeCreatePayload {
	id: string;
}

export interface StudentCandidate {
	id: string;
	name: string;
	position: string;
}

const roleOptions = ["超级管理员", "校长", "管理员", "教师", "助教", "招生"];

function wait<T>(data: T, ms = 250) {
	return new Promise<T>((resolve) => setTimeout(() => resolve(data), ms));
}

function toGender(value: unknown): "男" | "女" | "未知" {
	if (value === "MALE" || value === 1 || value === "1" || value === "男") return "男";
	if (value === "FEMALE" || value === 2 || value === "2" || value === "女") return "女";
	return "未知";
}

function toStatus(value: unknown): "在职" | "离职" {
	if (value === "ON_JOB" || value === 1 || value === "1" || value === "在职") return "在职";
	return "离职";
}

function toPersonType(value: unknown): "内部" | "外部" {
	return value === true || value === 1 || value === "1" || value === "内部" ? "内部" : "外部";
}

function mapStaffRowToEmployeeItem(row: Record<string, unknown>): EmployeeItem {
	const orgId = String(row.orgId ?? "");
	const mobile = String(row.mobile ?? row.account ?? "");
	return {
		id: String(row.id ?? ""),
		name: String(row.name ?? ""),
		account: mobile,
		mobile,
		orgId,
		orgName: String(row.orgNamePath ?? row.orgName ?? ""),
		gender: toGender(row.gender),
		position: String(row.positionName ?? row.position ?? ""),
		roleName: String(row.roleName ?? (row.isManager ? "管理员" : "")),
		personType: toPersonType(row.isInner),
		hireDate: String(row.hireDate ?? ""),
		status: toStatus(row.state ?? row.statue ?? row.status),
		isManager: Number(row.isManager ?? 0),
	};
}

function mapPayloadToSaveBody(payload: EmployeeCreatePayload | EmployeeUpdatePayload) {
	const orgIdNum = Number(payload.orgId);
	const positionIdNum = Number(payload.positionId ?? payload.position);
	const body: Record<string, unknown> = {
		name: payload.name,
		mobile: payload.account,
		orgId: Number.isFinite(orgIdNum) ? orgIdNum : payload.orgId,
		positionId: Number.isFinite(positionIdNum) ? positionIdNum : payload.positionId,
		gender: payload.gender === "男" ? 1 : payload.gender === "女" ? 2 : 0,
		isInner: payload.isInternal ? 1 : 0,
		isManager: payload.isManager ? 1 : 0,
		assistantFee: payload.assistantFee ?? undefined,
		classFee: payload.classFee ?? undefined,
		degree: typeof payload.degree === "number" ? payload.degree : undefined,
		birthday: payload.birthday || undefined,
		hireDate: payload.hireDate || undefined,
		school: payload.school || payload.graduateSchool || undefined,
		remark: payload.remark || payload.intro || undefined,
		headImg: payload.headImg || payload.photoUrl || undefined,
	};
	if (payload.password) body.password = payload.password;
	if ("id" in payload && payload.id) body.id = Number(payload.id);
	return body;
}

export async function queryOrgTree(): Promise<OrgNode[]> {
	const http = useHttp();
	const res = await http.get<unknown>("/org/institution/query-list");
	const raw = res.data;
	if (!Array.isArray(raw)) return [];

	const rows = raw
		.map((item) => {
			if (!item || typeof item !== "object") return null;
			const o = item as Record<string, unknown>;
			const id = String(o.orgId ?? "");
			const name = String(o.orgName ?? "");
			if (!id || !name) return null;
			return {
				id,
				name,
				parentId: String(o.parentOrgId ?? ""),
			};
		})
		.filter((i): i is { id: string; name: string; parentId: string } => Boolean(i));

	const nodeMap = new Map<string, OrgNode>();
	rows.forEach((r) => nodeMap.set(r.id, { id: r.id, name: r.name, children: [] }));
	const roots: OrgNode[] = [];

	rows.forEach((r) => {
		const current = nodeMap.get(r.id);
		if (!current) return;
		const parent = nodeMap.get(r.parentId);
		if (parent && r.parentId !== "0") {
			parent.children = parent.children || [];
			parent.children.push(current);
			return;
		}
		roots.push(current);
	});

	const normalize = (nodes: OrgNode[]) => {
		nodes.forEach((n) => {
			if (n.children?.length) normalize(n.children);
			else delete n.children;
		});
	};
	normalize(roots);
	return roots;
}

export async function queryEmployeeList(params: EmployeeQuery): Promise<{ list: EmployeeItem[]; total: number }> {
	const http = useHttp();
	const res = await http.get<unknown>("/org/staff/getpage", {
		orgId: params.orgId ? Number(params.orgId) : undefined,
		account: params.keyword || undefined,
		name: params.keyword || undefined,
		id: undefined,
		pageIndex: params.page,
		pageSize: params.pageSize,
		statue: params.status ? (params.status === "在职" ? 1 : 0) : undefined,
	});

	const raw = res.data;
	if (!(raw && typeof raw === "object")) return { list: [], total: 0 };
	const pageObj = raw as Record<string, unknown>;
	const rows = Array.isArray(pageObj.rows) ? pageObj.rows : [];
	const list = rows
		.map((item) => (item && typeof item === "object" ? mapStaffRowToEmployeeItem(item as Record<string, unknown>) : null))
		.filter((item): item is EmployeeItem => Boolean(item));
	const total = Number(pageObj.total ?? 0);
	return { list, total: Number.isFinite(total) ? total : list.length };
}

export async function queryEmployeeDetail(params: { id?: string; account?: string; name?: string }): Promise<EmployeeItem | null> {
	const http = useHttp();
	const res = await http.get<unknown>("/org/staff/get", {
		id: params.id ? Number(params.id) : undefined,
		account: params.account || undefined,
		name: params.name || undefined,
	});
	const raw = res.data;
	if (!raw || typeof raw !== "object") return null;
	return mapStaffRowToEmployeeItem(raw as Record<string, unknown>);
}

export async function createEmployee(payload: EmployeeCreatePayload): Promise<void> {
	const http = useHttp();
	await http.post("/org/staff/save", mapPayloadToSaveBody(payload));
}

export async function updateEmployee(payload: EmployeeUpdatePayload): Promise<void> {
	const http = useHttp();
	await http.post("/org/staff/save", mapPayloadToSaveBody(payload));
}

export async function resetEmployeePassword(id: string, newPassword: string): Promise<void> {
	const http = useHttp();
	await http.put("/org/staff/reset-password", {
		staffId: Number(id),
		newPassword,
	});
}

export async function updateEmployeeAvatar(id: string, avatar: string): Promise<void> {
	const http = useHttp();
	await http.put("/org/staff/avatar/url", {
		staffId: Number(id),
		avatarUrl: avatar,
	});
}

export async function queryRoleOptions(): Promise<string[]> {
	return wait(roleOptions, 120);
}

export async function setEmployeeRole(ids: string[], roleName: string): Promise<void> {
	const http = useHttp();
	await http.post("/org/staff/set", {
		staffIds: ids.map((id) => Number(id)),
		roleId: Number(roleName) || undefined,
	});
}

export async function deleteEmployees(ids: string[]): Promise<void> {
	const http = useHttp();
	await http.delete("/org/staff/delete", ids.map((id) => Number(id)));
}

export async function transferEmployeeOrg(ids: string[], targetOrgId: string): Promise<void> {
	const http = useHttp();
	await http.post("/org/staff/transfer", {
		staffIds: ids.map((id) => Number(id)),
		targetOrgId: Number(targetOrgId),
	});
}

export async function changeEmployeeStatus(ids: string[], status: "在职" | "离职", date?: string): Promise<void> {
	const http = useHttp();
	await http.post("/org/staff/update", ids.map((id) => Number(id)), {
		params: {
			status: status === "在职" ? 1 : 0,
			date: date || new Date().toISOString().slice(0, 10),
		},
	});
}

export async function exportEmployees(params: EmployeeQuery): Promise<void> {
	const http = useHttp();
	await http.getFile("/org/staff/export", {
		account: params.keyword || undefined,
		name: params.keyword || undefined,
		pageIndex: params.page,
		pageSize: params.pageSize,
		statue: params.status ? (params.status === "在职" ? 1 : 0) : undefined,
		orgId: params.orgId ? Number(params.orgId) : undefined,
	});
}

export async function queryClassRecord(params: { page: number; pageSize: number; staffId: string }) {
	const http = useHttp();
	return http.get("/org/staff/class", {
		pageIndex: params.page,
		pageSize: params.pageSize,
		staffId: Number(params.staffId),
	});
}

export async function queryTeachRecord(params: { page: number; pageSize: number; staffId: string; startDate?: string; endDate?: string }) {
	const http = useHttp();
	return http.get("/org/staff/lesson", {
		pageIndex: params.page,
		pageSize: params.pageSize,
		staffId: Number(params.staffId),
		startDate: params.startDate || undefined,
		endDate: params.endDate || undefined,
	});
}

export async function queryStudentCandidates(keyword = ""): Promise<StudentCandidate[]> {
	const { list } = await queryEmployeeList({
		keyword,
		page: 1,
		pageSize: 100,
		status: "在职",
	});
	return list.map((item) => ({ id: item.id, name: item.name, position: item.position }));
}

export async function transferToStudent(employeeIds: string[], studentId: string): Promise<void> {
	void employeeIds;
	void studentId;
	return wait(undefined, 200);
}
