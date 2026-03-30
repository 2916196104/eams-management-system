import { useHttp } from "@/plugins/http";

/** 机构详情（GET /org/query-detail） */
export interface OrgDetail {
	businessLicense?: string;
	contact?: string;
	email?: string;
	fax?: string;
	orgId?: number;
	orgName?: string;
	orgShortName?: string;
	/** 1-集团 2-分校 3-部门 */
	orgType?: number;
	orgTypeDesc?: string;
	parentOrgId?: number;
	parentOrgName?: string;
	phone?: string;
	region?: string;
	remark?: string;
	sortOrder?: number;
	/** 0-禁用 1-启用 */
	status?: number;
	statusDesc?: string;
}

/** 机构列表行（GET /org/query-list） */
export interface OrgListItem {
	contact?: string;
	orgFullName?: string;
	orgId?: number;
	orgName?: string;
	orgType?: number;
	orgTypeDesc?: string;
	parentOrgId?: number;
	phone?: string;
}

export interface OrgListQuery {
	/** 机构名称模糊查询 */
	orgName?: string;
	/** 1-集团 2-分校 3-部门 */
	orgType?: number;
	parentOrgId?: number;
	/** 0-禁用 1-启用 */
	status?: number;
}

/** 机构树节点（GET /org/query-org-tree） */
export interface OrgTreeNode {
	orgId: number;
	orgName: string;
	parentOrgId?: number;
	hasChildren?: boolean;
	children?: OrgTreeNode[];
}

/** 保存机构（POST /org/save-org） */
export interface OrgSavePayload {
	contact?: string;
	email?: string;
	fax?: string;
	/** 新增不传，修改必传 */
	orgId?: number;
	orgName: string;
	orgShortName?: string;
	orgType: number;
	/** 顶级机构传 0 */
	parentOrgId: number;
	phone?: string;
	remark?: string;
	sortOrder?: number;
	status?: number;
}

/** 表格树行：列表字段 + 子节点 */
export interface OrgTreeRow extends OrgListItem {
	children?: OrgTreeRow[];
}

function normalizeTreeRows(nodes: OrgTreeRow[]) {
	nodes.forEach((n) => {
		if (n.children?.length) normalizeTreeRows(n.children);
		else delete n.children;
	});
}

/**
 * 将扁平机构列表按 parentOrgId 组装为树（parentOrgId 为 0 或不存在父节点时挂到根）
 */
export function buildOrgTreeFromList(rows: OrgListItem[]): OrgTreeRow[] {
	const map = new Map<number, OrgTreeRow>();
	for (const r of rows) {
		if (r.orgId == null) continue;
		map.set(r.orgId, {
			...r,
			children: [],
		});
	}
	const roots: OrgTreeRow[] = [];
	map.forEach((node) => {
		const pid = node.parentOrgId;
		if (pid != null && pid !== 0 && map.has(pid)) {
			const parent = map.get(pid)!;
			parent.children = parent.children || [];
			parent.children.push(node);
		} else {
			roots.push(node);
		}
	});
	normalizeTreeRows(roots);
	return roots;
}

/**
 * 获取机构列表（扁平）
 */
export async function queryOrgList(params?: OrgListQuery): Promise<OrgListItem[]> {
	const http = useHttp();
	const res = await http.get<OrgListItem[]>("/org/query-list", params);
	const raw = res.data;
	return Array.isArray(raw) ? raw : [];
}

/**
 * 获取机构详情
 */
export async function queryOrgDetail(orgId: number): Promise<OrgDetail | undefined> {
	const http = useHttp();
	const res = await http.get<OrgDetail>("/org/query-detail", { orgId });
	return res.data;
}

/**
 * 获取机构树（后端已嵌套 children 时使用）
 */
export async function queryOrgTree(parentOrgId?: number | null): Promise<OrgTreeNode[]> {
	const http = useHttp();
	const params: Record<string, number> = {};
	if (parentOrgId != null) params.parentOrgId = parentOrgId;
	const res = await http.get<OrgTreeNode[]>("/org/query-org-tree", params);
	const raw = res.data;
	return Array.isArray(raw) ? raw : [];
}

/**
 * 新增或修改机构
 */
export async function saveOrg(payload: OrgSavePayload): Promise<void> {
	const http = useHttp();
	const body: Record<string, unknown> = {
		orgName: payload.orgName,
		orgType: payload.orgType,
		parentOrgId: payload.parentOrgId,
	};
	if (payload.orgId != null) body.orgId = payload.orgId;
	if (payload.contact != null) body.contact = payload.contact;
	if (payload.email != null) body.email = payload.email;
	if (payload.fax != null) body.fax = payload.fax;
	if (payload.orgShortName != null) body.orgShortName = payload.orgShortName;
	if (payload.phone != null && payload.phone !== "") body.phone = payload.phone;
	if (payload.remark != null) body.remark = payload.remark;
	if (payload.sortOrder != null) body.sortOrder = payload.sortOrder;
	if (payload.status != null) body.status = payload.status;
	await http.post<unknown>("/org/save-org", body);
}

/**
 * 删除机构（有子机构时后端应拒绝）
 */
export async function removeOrg(orgId: number): Promise<void> {
	const http = useHttp();
	await http.delete<boolean>("/org/remove-org", undefined, { params: { orgId } });
}
