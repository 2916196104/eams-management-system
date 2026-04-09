import { useHttp } from "@/plugins/http";

export interface PositionRow {
	id: string;
	name: string;
}

export interface PageResult<T> {
	pageIndex: number;
	pageSize: number;
	pages: number;
	rows: T[];
	total: number;
}

export interface PositionPermissionRow {
	id: string;
	entityName: string;
	scopeType: string;
	tableCode: string;
	ownerField: string;
	ownerOrgField: string;
}

export interface PositionPermissionSavePayload {
	id?: string;
	entityName: string;
	ownerField: string;
	ownerOrgField: string;
	scopeType: number;
	positionId: string;
}

function toStringId(v: unknown) {
	return String(v ?? "");
}

function toNumber(v: unknown, fallback = 0) {
	const n = Number(v);
	return Number.isFinite(n) ? n : fallback;
}

export async function queryPositionList(params: { name?: string; pageIndex: number; pageSize: number }): Promise<PageResult<PositionRow>> {
	const http = useHttp();
	const res = await http.get<unknown>("/org/position/list", {
		name: params.name || undefined,
		page: params.pageIndex,
		pageSize: params.pageSize,
	});
	const raw = res.data;
	const pageObj = (raw && typeof raw === "object" ? (raw as Record<string, unknown>) : {}) as Record<string, unknown>;
	const rowsRaw = Array.isArray(pageObj.rows) ? pageObj.rows : [];
	const rows = rowsRaw
		.map((i) => {
			if (!i || typeof i !== "object") return null;
			const o = i as Record<string, unknown>;
			const id = toStringId(o.id);
			const name = String(o.name ?? "");
			if (!id || !name) return null;
			return { id, name } as PositionRow;
		})
		.filter((i): i is PositionRow => Boolean(i));

	return {
		pageIndex: toNumber(pageObj.pageIndex, params.pageIndex),
		pageSize: toNumber(pageObj.pageSize, params.pageSize),
		pages: toNumber(pageObj.pages, 0),
		rows,
		total: toNumber(pageObj.total, rows.length),
	};
}

export async function savePosition(payload: { id?: string; name: string }): Promise<void> {
	const http = useHttp();
	await http.post("/org/position/save", {
		id: payload.id ? toNumber(payload.id) : undefined,
		name: payload.name,
	});
}

export async function deletePositions(ids: string[]): Promise<void> {
	const http = useHttp();
	// Apifox 绀轰緥閲?Body 鍙傛暟鏄剧ず涓?array[integer]锛岃繖閲岀洿鎺ュ彂 id 鏁扮粍
	await http.post("/org/position/delete", ids.map((i) => toNumber(i)));
}

export async function queryPositionPermissions(params: { positionId: string; pageIndex: number; pageSize: number }): Promise<PageResult<PositionPermissionRow>> {
	const http = useHttp();
	const res = await http.get<unknown>("/org/position/queryPermission", {
		positionId: toNumber(params.positionId),
		pageIndex: params.pageIndex,
		pageSize: params.pageSize,
	});

	const raw = res.data;
	const pageObj = (raw && typeof raw === "object" ? (raw as Record<string, unknown>) : {}) as Record<string, unknown>;
	const rowsRaw = Array.isArray(pageObj.rows) ? pageObj.rows : [];
	const rows = rowsRaw
		.map((i) => {
			if (!i || typeof i !== "object") return null;
			const o = i as Record<string, unknown>;
			const id = toStringId(o.id);
			if (!id) return null;
			return {
				id,
				entityName: String(o.entity_name ?? o.entityName ?? ""),
				scopeType: String(o.scope_type ?? o.scopeType ?? ""),
				tableCode: String(o.table_code ?? o.tableCode ?? o.entity_name ?? ""),
				ownerField: String(o.owner_field ?? o.ownerField ?? ""),
				ownerOrgField: String(o.owner_org_field ?? o.ownerOrgField ?? ""),
			} as PositionPermissionRow;
		})
		.filter((i): i is PositionPermissionRow => Boolean(i));

	return {
		pageIndex: toNumber(pageObj.pageIndex, params.pageIndex),
		pageSize: toNumber(pageObj.pageSize, params.pageSize),
		pages: toNumber(pageObj.pages, 0),
		rows,
		total: toNumber(pageObj.total, rows.length),
	};
}

export async function savePositionPermission(payload: PositionPermissionSavePayload): Promise<void> {
	const http = useHttp();
	await http.post("/org/position/savePermission", {
		id: payload.id ? toNumber(payload.id) : undefined,
		entity_name: payload.entityName,
		owner_field: payload.ownerField,
		owner_org_field: payload.ownerOrgField,
		scope_type: payload.scopeType,
		positionId: toNumber(payload.positionId),
	});
}

export async function removePositionPermissions(ids: string[]): Promise<void> {
	const http = useHttp();
	// Apifox 绀轰緥鏄剧ず body 鏄?string锛堝 "1"锛夛紝涔熸敮鎸佹壒閲忥細杩欓噷鎸?string[] 澶勭悊
	await http.delete("/org/position/removePermission", ids.length === 1 ? ids[0] : ids);
}



