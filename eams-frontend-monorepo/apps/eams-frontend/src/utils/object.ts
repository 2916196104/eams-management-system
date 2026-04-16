/**
 * 深度比较两个对象，将空字符串和undefined视为相等
 * @param a 第一个对象
 * @param b 第二个对象
 * @returns 是否相等
 */
export function isEqualWithEmpty(a: any, b: any): boolean {
	// 处理基本类型和空值
	if (a === b) return true;

	// 特殊处理：空字符串和 undefined 视为相等
	if ((a === "" && b === undefined) || (a === undefined && b === "")) {
		return true;
	}

	// 处理 null 和 undefined
	if (a == null || b == null) {
		return a === b;
	}

	// 处理数组
	if (Array.isArray(a) && Array.isArray(b)) {
		if (a.length !== b.length) return false;
		for (let i = 0; i < a.length; i++) {
			if (!isEqualWithEmpty(a[i], b[i])) return false;
		}
		return true;
	}

	// 处理对象
	if (typeof a === "object" && typeof b === "object") {
		const keysA = Object.keys(a);
		const keysB = Object.keys(b);
		const allKeys = new Set([...keysA, ...keysB]);

		for (const key of allKeys) {
			// 特殊处理空字符串和 undefined
			if (
				(a[key] === "" && !(key in b)) ||
				(b[key] === "" && !(key in a)) ||
				(a[key] === undefined && b[key] === "") ||
				(a[key] === "" && b[key] === undefined)
			) {
				continue;
			}

			// 递归比较其他情况
			if (!isEqualWithEmpty(a[key], b[key])) {
				return false;
			}
		}
		return true;
	}

	// 其他情况不相等
	return false;
}

/**
 * 浅拷贝对象，只拷贝存在的属性
 * @param target 目标对象
 * @param sources 源对象
 * @returns 目标对象
 */
export function assignOnlyExisting<T extends object>(target: T, ...sources: Partial<T>[]): T {
	if (!target) return target;
	const targetKeys = Object.keys(target) as Array<keyof T>;
	sources.forEach((source) => {
		if (!source) return;
		Object.keys(source).forEach((key) => {
			if (targetKeys.includes(key as keyof T)) {
				(target as any)[key] = (source as any)[key];
			}
		});
	});
	return target;
}
