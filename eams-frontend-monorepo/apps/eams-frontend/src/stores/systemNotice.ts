import { defineStore } from "pinia";
import { ref } from "vue";
import { delNotice, editNotice, getNoticeDetail, getNoticeList } from "@/apis/system/notice";
import type { INoticeList, INoticeSave } from "@/apis/system/notice/type";

export interface NoticeItem {
	id: number;
	title: string;
	content: string;
	type?: string;
	publisher?: string;
	creator?: number;
	editor?: number;
	isTop?: number;
	isEnable?: number;
	viewNum?: number;
	createTime: string;
	updateTime?: string;
}

function unwrapPayload(input: unknown): unknown {
	let current = input;

	while (current && typeof current === "object" && "data" in (current as Record<string, unknown>)) {
		const next = (current as { data?: unknown }).data;
		if (next === undefined || next === current) {
			break;
		}
		current = next;
	}

	return current;
}

function hasServerPayload(input: unknown) {
	return Boolean(
		input &&
		typeof input === "object" &&
		("data" in (input as Record<string, unknown>) || "status" in (input as Record<string, unknown>)),
	);
}

function normalizeNotice(detail: unknown): NoticeItem | null {
	if (!detail || typeof detail !== "object") {
		return null;
	}

	const source = detail as Partial<NoticeItem> & {
		addTime?: string;
		editTime?: string;
		creator?: number | string;
		editor?: number | string;
		viewNum?: number | string;
	};
	if (source.id == null) {
		return null;
	}

	return {
		id: Number(source.id),
		title: source.title ?? "",
		content: source.content ?? "",
		type: source.type,
		publisher: source.publisher,
		creator: source.creator == null ? undefined : Number(source.creator),
		editor: source.editor == null ? undefined : Number(source.editor),
		isTop: source.isTop,
		isEnable: source.isEnable,
		viewNum: source.viewNum == null ? undefined : Number(source.viewNum),
		createTime: source.createTime ?? source.addTime ?? "",
		updateTime: source.updateTime ?? source.editTime,
	};
}

function extractNoticeRows(data: unknown): NoticeItem[] {
	const normalizeRows = (rows: unknown[]) =>
		rows.map((item) => normalizeNotice(item)).filter((item): item is NoticeItem => Boolean(item));

	if (Array.isArray(data)) {
		return normalizeRows(data);
	}

	if (data && typeof data === "object") {
		const source = data as { records?: unknown[]; list?: unknown[]; rows?: unknown[] };
		const rows = source.records ?? source.list ?? source.rows;
		return Array.isArray(rows) ? normalizeRows(rows) : [];
	}

	return [];
}

function extractNoticeTotal(data: unknown, rows: NoticeItem[]) {
	if (data && typeof data === "object" && "total" in (data as Record<string, unknown>)) {
		const total = Number((data as { total?: unknown }).total);
		if (Number.isFinite(total)) {
			return total;
		}
	}

	return rows.length;
}

export const useSystemNoticeStore = defineStore("systemNotice", () => {
	const tableData = ref<NoticeItem[]>([]);
	const loading = ref(false);
	const total = ref(0);

	const searchParams = ref<INoticeList>({
		title: "",
		pageSize: 10,
		pageNum: 1,
	});

	async function fetchList() {
		loading.value = true;
		try {
			const res = await getNoticeList(searchParams.value);
			const payload = unwrapPayload(res);
			const rows = extractNoticeRows(payload);
			tableData.value = rows;
			total.value = extractNoticeTotal(payload, rows);
			return true;
		} catch (error) {
			const payload = unwrapPayload(error);
			const rows = extractNoticeRows(payload);
			if (rows.length > 0 || hasServerPayload(error)) {
				tableData.value = rows;
				total.value = extractNoticeTotal(payload, rows);
				return true;
			}

			tableData.value = [];
			total.value = 0;
			return false;
		} finally {
			loading.value = false;
		}
	}

	async function saveNotice(data: INoticeSave) {
		try {
			await editNotice(data);
			await fetchList();
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchList();
		}
	}

	async function deleteNotice(ids: number[]) {
		try {
			await delNotice({ ids });
			await fetchList();
			return true;
		} catch (error) {
			if (!hasServerPayload(error)) {
				return false;
			}

			return fetchList();
		}
	}

	async function fetchDetail(id: number) {
		try {
			const res = await getNoticeDetail(id);
			return normalizeNotice(unwrapPayload(res));
		} catch (error) {
			if (!hasServerPayload(error)) {
				return null;
			}

			return normalizeNotice(unwrapPayload(error));
		}
	}

	function setSearchParams(params: Partial<INoticeList>) {
		searchParams.value = { ...searchParams.value, ...params };
	}

	function resetSearchParams() {
		searchParams.value = { title: "", pageSize: 10, pageNum: 1 };
	}

	return {
		tableData,
		loading,
		total,
		searchParams,
		fetchList,
		saveNotice,
		deleteNotice,
		fetchDetail,
		setSearchParams,
		resetSearchParams,
	};
});
