import { queryOrgTree, type OrgNode } from "@/apis/org/employeeManage";

export type SalaryMode = "非底薪模式" | "底薪模式";
export interface LessonFeeSetting {
	id: string;
	duration: string;
	lessonFee: number;
	assistFee: number;
}

export interface SalaryRow {
	id: string;
	teacherName: string;
	phone: string;
	orgId: string;
	orgName: string;
	salaryMode: SalaryMode;
	baseSalary: number;
	targetLessonCount: number;
	trialLessonPay: number;
	lessonDuration: string;
	lessonBonus: number;
	performancePay: number;
	lessonFeeSettings: LessonFeeSetting[];
}

export interface SalaryQuery {
	orgId?: string;
	page: number;
	pageSize: number;
}

export interface SalaryUpdatePayload {
	id: string;
	salaryMode: SalaryMode;
	baseSalary: number;
	targetLessonCount: number;
	trialLessonPay: number;
	lessonDuration: string;
	lessonBonus: number;
	performancePay: number;
	lessonFeeSettings: LessonFeeSetting[];
}

const orgIds = ["org-root-lf", "org-hn", "org-zxx", "org-jsj", "org-zhs", "org-art", "org-301", "org-km", "org-zico", "org-admin", "org-teach", "org-sale", "org-jswx", "org-jsnj"];
const orgNames: Record<string, string> = {
	"org-root-lf": "四川职业技术学院龙凤校区",
	"org-hn": "HN校区",
	"org-zxx": "ZXX校区",
	"org-jsj": "JSJ校区",
	"org-zhs": "ZHS校区",
	"org-art": "美术学院",
	"org-301": "301",
	"org-km": "昆明经管校区",
	"org-zico": "Zico Eplus少儿国际素养中心",
	"org-admin": "行政部",
	"org-teach": "教学部",
	"org-sale": "销售部",
	"org-jswx": "江苏无锡校区-清北信奥",
	"org-jsnj": "江苏南京校区-清北信奥",
};
const salaryDb: SalaryRow[] = Array.from({ length: 54 }).map((_, i) => ({
	id: `salary-${i + 1}`,
	teacherName: i === 0 ? "翠花" : i === 1 ? "王伟大" : `老师${i + 1}`,
	phone: `13${String(888888888 + i * 17).slice(0, 9)}`,
	orgId: orgIds[i % orgIds.length],
	orgName: orgNames[orgIds[i % orgIds.length]] || "",
	salaryMode: i % 5 === 0 ? "底薪模式" : "非底薪模式",
	baseSalary: i % 5 === 0 ? 10000 + (i % 3) * 5000 : 0,
	targetLessonCount: i % 5 === 0 ? 80 + (i % 4) * 10 : 0,
	trialLessonPay: i % 7 === 0 ? 180 : i % 3 === 0 ? 90 : 60,
	lessonDuration: i % 3 === 0 ? "90分钟" : "60分钟",
	lessonBonus: i % 5 === 0 ? 200 + i : i % 6 === 0 ? 1000 : i % 4,
	performancePay: i % 5 === 0 ? 100 + i : i % 2,
	lessonFeeSettings: [
		{
			id: `fee-${i + 1}-1`,
			duration: i % 3 === 0 ? "90分钟" : "60分钟",
			lessonFee: i % 7 === 0 ? 180 : 90,
			assistFee: i % 5 === 0 ? 20 : 0,
		},
	],
}));

function wait<T>(data: T, ms = 280) {
	return new Promise<T>((resolve) => setTimeout(() => resolve(data), ms));
}

export async function querySalaryOrgTree(): Promise<OrgNode[]> {
	return queryOrgTree();
}

export async function querySalaryList(params: SalaryQuery): Promise<{ list: SalaryRow[]; total: number }> {
	const filtered = salaryDb.filter((item) => (params.orgId ? item.orgId === params.orgId : true));
	const total = filtered.length;
	const start = (params.page - 1) * params.pageSize;
	const end = start + params.pageSize;
	return wait({ list: filtered.slice(start, end), total });
}

export async function updateSalaryRow(payload: SalaryUpdatePayload): Promise<void> {
	const idx = salaryDb.findIndex((item) => item.id === payload.id);
	if (idx === -1) return wait(undefined, 180);
	salaryDb[idx] = { ...salaryDb[idx], ...payload };
	return wait(undefined, 220);
}

