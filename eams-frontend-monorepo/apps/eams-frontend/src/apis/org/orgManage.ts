export interface OrgManageNode {
	id: string;
	parentId?: string;
	name: string;
	fullName: string;
	level: "机构" | "分校";
	contact: string;
	phone: string;
	shortName?: string;
	fax?: string;
	email?: string;
	sortNo?: number;
	enabled: boolean;
	desc?: string;
	children?: OrgManageNode[];
}

export interface OrgEditPayload {
	id?: string;
	parentId?: string;
	name: string;
	level: "机构" | "分校";
	shortName?: string;
	contact?: string;
	phone?: string;
	fax?: string;
	email?: string;
	sortNo?: number;
	enabled: boolean;
	desc?: string;
}

const db: OrgManageNode[] = [
	{
		id: "root-1",
		name: "四川职业技术学院龙凤校区",
		fullName: "四川职业技术学院龙凤校区",
		level: "机构",
		contact: "1",
		phone: "",
		enabled: true,
		children: [
			{
				id: "zhs",
				parentId: "root-1",
				name: "ZHS校区",
				fullName: "四川职业技术学院龙凤校区 ZHS校区",
				level: "分校",
				contact: "DuanXJ",
				phone: "",
				enabled: true,
				children: [
					{ id: "zxx", parentId: "zhs", name: "ZXX校区", fullName: "四川职业技术学院龙凤校区 ZXX校区", level: "分校", contact: "", phone: "", enabled: true },
					{ id: "jsj", parentId: "zhs", name: "JSJ校区", fullName: "四川职业技术学院龙凤校区 JSJ校区", level: "分校", contact: "", phone: "", enabled: true },
					{ id: "hn", parentId: "zhs", name: "HN校区", fullName: "四川职业技术学院龙凤校区 HN校区", level: "分校", contact: "", phone: "", enabled: true },
				],
			},
			{ id: "zico", parentId: "root-1", name: "Zico Eplus少儿国际素养中心", fullName: "四川职业技术学院龙凤校区 Zico Eplus少儿国际素养中心", level: "分校", contact: "刘子豪", phone: "13100000000", enabled: true },
		],
	},
];

function wait<T>(data: T, ms = 220) {
	return new Promise<T>((resolve) => setTimeout(() => resolve(data), ms));
}

function findNode(nodes: OrgManageNode[], id: string): OrgManageNode | null {
	for (const n of nodes) {
		if (n.id === id) return n;
		if (n.children?.length) {
			const target = findNode(n.children, id);
			if (target) return target;
		}
	}
	return null;
}

function walkAndDelete(nodes: OrgManageNode[], id: string): boolean {
	const idx = nodes.findIndex((n) => n.id === id);
	if (idx !== -1) {
		nodes.splice(idx, 1);
		return true;
	}
	for (const n of nodes) {
		if (n.children?.length && walkAndDelete(n.children, id)) return true;
	}
	return false;
}

export async function queryOrgManageTree(): Promise<OrgManageNode[]> {
	return wait(JSON.parse(JSON.stringify(db)));
}

export async function createOrg(payload: OrgEditPayload): Promise<void> {
	const parent = payload.parentId ? findNode(db, payload.parentId) : null;
	const node: OrgManageNode = {
		id: `org-${Date.now()}`,
		parentId: payload.parentId,
		name: payload.name,
		fullName: parent ? `${parent.fullName} ${payload.name}` : payload.name,
		level: payload.level,
		contact: payload.contact || "",
		phone: payload.phone || "",
		shortName: payload.shortName,
		fax: payload.fax,
		email: payload.email,
		sortNo: payload.sortNo,
		enabled: payload.enabled,
		desc: payload.desc,
	};
	if (parent) {
		parent.children = parent.children || [];
		parent.children.push(node);
	} else {
		db.push(node);
	}
	return wait(undefined);
}

export async function updateOrg(payload: OrgEditPayload): Promise<void> {
	if (!payload.id) return wait(undefined);
	const node = findNode(db, payload.id);
	if (!node) return wait(undefined);
	node.name = payload.name;
	node.level = payload.level;
	node.contact = payload.contact || "";
	node.phone = payload.phone || "";
	node.shortName = payload.shortName;
	node.fax = payload.fax;
	node.email = payload.email;
	node.sortNo = payload.sortNo;
	node.enabled = payload.enabled;
	node.desc = payload.desc;
	return wait(undefined);
}

export async function deleteOrg(id: string): Promise<void> {
	walkAndDelete(db, id);
	return wait(undefined);
}

