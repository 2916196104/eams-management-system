/** 是否包含至少一个汉字（用于判断后端提示是否适合直接展示） */
function hasChinese(s: string): boolean {
	return /[\u4e00-\u9fff]/.test(s);
}

/**
 * 从 axios / 封装层抛出的异常上取出后端 message
 */
function pickBackendMessage(e: unknown): string | undefined {
	if (!e || typeof e !== "object") return undefined;
	const o = e as Record<string, unknown>;
	// 形如 AxiosResponse：{ data: JsonVO }
	if (o.data && typeof o.data === "object" && "message" in o.data) {
		const m = (o.data as { message?: unknown }).message;
		if (typeof m === "string" && m.trim()) return m.trim();
	}
	// 形如 AxiosError：{ response: { data: JsonVO } }
	if (o.response && typeof o.response === "object") {
		const d = (o.response as { data?: unknown }).data;
		if (d && typeof d === "object" && "message" in d) {
			const m = (d as { message?: unknown }).message;
			if (typeof m === "string" && m.trim()) return m.trim();
		}
	}
	return undefined;
}

/**
 * 将接口异常转为面向用户的中文说明；避免展示纯英文或技术性英文句子。
 */
export function toZhUserMessage(e: unknown, fallback: string): string {
	const backend = pickBackendMessage(e);
	if (backend && hasChinese(backend)) return backend;

	if (e instanceof Error) {
		const m = e.message;
		if (hasChinese(m)) return m;
		if (/network/i.test(m)) return "网络错误，请检查网络连接";
		if (/timeout|超时/i.test(m)) return "请求超时，请稍后重试";
	}

	return fallback;
}
