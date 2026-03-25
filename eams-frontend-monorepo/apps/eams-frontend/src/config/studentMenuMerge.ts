import type { Menu } from "@/apis/login/type";

/**
 * 与截图一致的「学员」二级菜单（顺序固定）。
 * 若后端已返回同名项，会保留后端的 id 等字段，但 href 以本地为准（避免指错路由）。
 */
export const STUDENT_SUB_MENU_ITEMS: Menu[] = [
	{ id: "local-stu-online", text: "在学学员", icon: "IconUser", href: "/student/online" },
	{ id: "local-stu-intention", text: "意向学员", icon: "IconUser", href: "/student/intention" },
	{ id: "local-stu-graduated", text: "结业学员", icon: "IconUser", href: "/student/graduated" },
	{ id: "local-stu-parent", text: "家长账号", icon: "IconUser", href: "/student/parent-accounts" },
	{ id: "local-stu-lesson-progress", text: "课时进度", icon: "IconUser", href: "/student/lesson-progress" },
	{ id: "local-stu-lesson-summary", text: "课时汇总", icon: "IconUser", href: "/student/lesson-summary" },
	{ id: "local-stu-enroll", text: "报名记录", icon: "IconTickets", href: "/student/enrollment-records" },
	{ id: "local-stu-follow", text: "跟进记录", icon: "IconMessage", href: "/student/follow-records" },
];

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

/**
 * 在侧边栏中挂载「学员」分支：若后端已有「学员」则合并子菜单；否则追加一级「学员」菜单。
 */
export function mergeStudentMenuBranch(menus: Menu[]): Menu[] {
	const out: Menu[] = menus.map((m) => ({
		...m,
		children: m.children?.length ? m.children.map((c) => ({ ...c })) : m.children,
	}));
	const idx = out.findIndex((m) => String(m.text ?? "").trim() === "学员");
	if (idx >= 0) {
		const item = out[idx];
		out[idx] = {
			...item,
			icon: item.icon || "IconUser",
			children: mergeStudentChildren(item.children || []),
		};
		return out;
	}
	out.push({
		id: "local-student-branch",
		text: "学员",
		icon: "IconUser",
		children: mergeStudentChildren([]),
	});
	return out;
}
