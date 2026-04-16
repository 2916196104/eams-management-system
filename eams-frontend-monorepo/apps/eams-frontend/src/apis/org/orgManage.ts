import { useHttp } from "@/plugins/http";

/** 鏈烘瀯璇︽儏锛圙ET /org/institution/query-detail锛?*/
export interface OrgDetail {
	businessLicense?: string;
	contact?: string;
	email?: string;
	fax?: string;
	orgId?: number;
	orgName?: string;
	orgShortName?: string;
	/** 1-闆嗗洟 2-鍒嗘牎 3-閮ㄩ棬 */
	orgType?: number;
	orgTypeDesc?: string;
	parentOrgId?: number;
	parentOrgName?: string;
	phone?: string;
	region?: string;
	remark?: string;
	sortOrder?: number;
	/** 0-绂佺敤 1-鍚敤 */
	status?: number;
	statusDesc?: string;
}

/** 鏈烘瀯鍒楄〃琛岋紙GET /org/institution/query-list锛?*/
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
	/** 鏈烘瀯鍚嶇О妯＄硦鏌ヨ */
	orgName?: string;
	/** 1-闆嗗洟 2-鍒嗘牎 3-閮ㄩ棬 */
	orgType?: number;
	parentOrgId?: number;
	/** 0-绂佺敤 1-鍚敤 */
	status?: number;
}

/** 鏈烘瀯鏍戣妭鐐癸紙GET /org/institution/query-org-tree锛?*/
export interface OrgTreeNode {
	orgId: number;
	orgName: string;
	parentOrgId?: number;
	hasChildren?: boolean;
	children?: OrgTreeNode[];
}

/** 淇濆瓨鏈烘瀯锛圥OST /org/institution/save-org锛?*/
export interface OrgSavePayload {
	contact?: string;
	email?: string;
	fax?: string;
	/** 鏂板涓嶄紶锛屼慨鏀瑰繀浼?*/
	orgId?: number;
	orgName: string;
	orgShortName?: string;
	orgType: number;
	/** 椤剁骇鏈烘瀯浼?0 */
	parentOrgId: number;
	phone?: string;
	remark?: string;
	sortOrder?: number;
	status?: number;
}

/** 琛ㄦ牸鏍戣锛氬垪琛ㄥ瓧娈?+ 瀛愯妭鐐?*/
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
 * 灏嗘墎骞虫満鏋勫垪琛ㄦ寜 parentOrgId 缁勮涓烘爲锛坧arentOrgId 涓?0 鎴栦笉瀛樺湪鐖惰妭鐐规椂鎸傚埌鏍癸級
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
 * 鑾峰彇鏈烘瀯鍒楄〃锛堟墎骞筹級
 */
export async function queryOrgList(params?: OrgListQuery): Promise<OrgListItem[]> {
	const http = useHttp();
	const res = await http.get<OrgListItem[]>("/org/institution/query-list", params);
	const raw = res.data;
	return Array.isArray(raw) ? raw : [];
}

/**
 * 鑾峰彇鏈烘瀯璇︽儏
 */
export async function queryOrgDetail(orgId: number): Promise<OrgDetail | undefined> {
	const http = useHttp();
	const res = await http.get<OrgDetail>("/org/institution/query-detail", { orgId });
	return res.data;
}

/**
 * 鑾峰彇鏈烘瀯鏍戯紙鍚庣宸插祵濂?children 鏃朵娇鐢級
 */
export async function queryOrgTree(parentOrgId?: number | null): Promise<OrgTreeNode[]> {
	const http = useHttp();
	const params: Record<string, number> = {};
	if (parentOrgId != null) params.parentOrgId = parentOrgId;
	const res = await http.get<OrgTreeNode[]>("/org/institution/query-org-tree", params);
	const raw = res.data;
	return Array.isArray(raw) ? raw : [];
}

/**
 * 鏂板鎴栦慨鏀规満鏋? */
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
	await http.post<unknown>("/org/institution/save-org", body);
}

/**
 * 鍒犻櫎鏈烘瀯锛堟湁瀛愭満鏋勬椂鍚庣搴旀嫆缁濓級
 */
export async function removeOrg(orgId: number): Promise<void> {
	const http = useHttp();
	await http.delete<boolean>("/org/institution/remove-org", undefined, { params: { orgId } });
}

