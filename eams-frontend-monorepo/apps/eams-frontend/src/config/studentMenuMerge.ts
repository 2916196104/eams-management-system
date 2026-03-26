import type { Menu } from "@/apis/login/type";

/**
 * 与截图一致的「学员」二级菜单（顺序固定）。
 * 若后端已返回同名项，会保留后端的 id 等字段，但 href 以本地为准（避免指错路由）。
 */
export const STUDENT_SUB_MENU_ITEMS: Menu[] = [
	{ id: "local-stu-online", text: "在学学员", icon: "ep/user", href: "/student/online" },
	{ id: "local-stu-intention", text: "意向学员", icon: "ep/user", href: "/student/intention" },
	{ id: "local-stu-graduated", text: "结业学员", icon: "ep/user", href: "/student/graduated" },
	{ id: "local-stu-parent", text: "家长账号", icon: "ep/user", href: "/student/parent-accounts" },
];

/**
 * 与截图一致的「我的跟进」一级菜单。
 * 若后端已返回同名项，会保留后端的 id 等字段，但 href 以本地为准（避免指错路由）。
 */
export const MY_FOLLOW_MENU_ITEM: Menu = {
	id: "local-my-follow",
	text: "我的跟进",
	icon: "ep/message",
	href: "/follow",
};

function mergeStudentChildren(existing: Menu[] = []): Menu[] {
	const byText = new Map(existing.map((c) => [String(c.text ?? "").trim(), { ...c }]));
	const result: Menu[] = [];
	for (const item of STUDENT_SUB_MENU_ITEMS) {
		const key = item.text.trim();
		const prev = byText.get(key);
		result.push({
			...item,
			...prev,
			id: prev?.id ?? item.id,
			href: item.href ?? prev?.href,
			icon: prev?.icon || item.icon,
			text: item.text,
		});
		byText.delete(key);
	}
	for (const [, rest] of byText) {
		result.push(rest);
	}
	return result;
}

function mergeChildByText(existing: Menu[] = [], local: Menu): Menu[] {
	const byText = new Map(existing.map((c) => [String(c.text ?? "").trim(), { ...c }]));
	const key = String(local.text ?? "").trim();
	const prev = byText.get(key);
	const merged: Menu = {
		...local,
		...prev,
		id: prev?.id ?? local.id,
		href: local.href ?? prev?.href,
		icon: prev?.icon || local.icon,
		text: local.text,
	};
	byText.delete(key);
	return [merged, ...Array.from(byText.values())];
}

function mergeMyFollowBranch(menus: Menu[]): Menu[] {
	const out: Menu[] = menus.map((m) => ({
		...m,
		children: m.children?.length ? m.children.map((c) => ({ ...c })) : m.children,
	}));

	const candidates = ["工作台", "控制台", "首页"];
	const idx = out.findIndex((m) => candidates.includes(String(m.text ?? "").trim()));
	if (idx >= 0) {
		const prev = out[idx];
		out[idx] = {
			...prev,
			children: mergeChildByText(prev.children || [], MY_FOLLOW_MENU_ITEM),
		};
		return out;
	}

	out.push({
		id: "local-dashboard-branch",
		text: "工作台",
		icon: "ep/home-filled",
		children: [MY_FOLLOW_MENU_ITEM],
	});
	return out;
}

/**
 * 在侧边栏中挂载本地兜底菜单：
 * - 「我的跟进」：若后端缺失则追加；若已存在则修正 href 并保留后端字段
 * - 「学员」分支：若后端已有「学员」则合并子菜单；否则追加一级「学员」菜单
 */
export function mergeStudentMenuBranch(menus: Menu[]): Menu[] {
	const out = mergeMyFollowBranch(menus);
	const idx = out.findIndex((m) => String(m.text ?? "").trim() === "学员");
	if (idx >= 0) {
		const item = out[idx];
		out[idx] = {
			...item,
			icon: item.icon || "ep/user",
			children: mergeStudentChildren(item.children || []),
		};
		return out;
	}
	out.push({
		id: "local-student-branch",
		text: "学员",
		icon: "ep/user",
		children: mergeStudentChildren([]),
	});
	return out;
}
