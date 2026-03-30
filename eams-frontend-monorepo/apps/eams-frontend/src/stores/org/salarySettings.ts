import { defineStore } from "pinia";
import { querySalaryList, querySalaryOrgTree, updateSalaryRow, type SalaryRow, type SalaryUpdatePayload } from "@/apis/org/salarySettings";
import type { OrgNode } from "@/apis/org/employeeManage";

interface SalarySettingsState {
	orgTree: OrgNode[];
	selectedOrgId: string;
	list: SalaryRow[];
	page: number;
	pageSize: number;
	total: number;
	loading: {
		org: boolean;
		list: boolean;
		update: boolean;
	};
	error: string | null;
}

export const useSalarySettingsStore = defineStore("salarySettings", {
	state: (): SalarySettingsState => ({
		orgTree: [],
		selectedOrgId: "",
		list: [],
		page: 1,
		pageSize: 20,
		total: 0,
		loading: {
			org: false,
			list: false,
			update: false,
		},
		error: null,
	}),
	actions: {
		async initPage() {
			this.error = null;
			await Promise.all([this.fetchOrgTree(), this.fetchList()]);
		},
		async fetchOrgTree() {
			this.loading.org = true;
			try {
				this.orgTree = await querySalaryOrgTree();
			} catch (e: any) {
				this.error = e?.message || "获取机构树失败";
			} finally {
				this.loading.org = false;
			}
		},
		async fetchList() {
			this.loading.list = true;
			try {
				const { list, total } = await querySalaryList({
					orgId: this.selectedOrgId || undefined,
					page: this.page,
					pageSize: this.pageSize,
				});
				this.list = list;
				this.total = total;
			} catch (e: any) {
				this.error = e?.message || "获取薪资列表失败";
			} finally {
				this.loading.list = false;
			}
		},
		async setOrgAndQuery(orgId: string) {
			this.selectedOrgId = orgId;
			this.page = 1;
			await this.fetchList();
		},
		async setPage(page: number) {
			this.page = page;
			await this.fetchList();
		},
		async setPageSize(pageSize: number) {
			this.pageSize = pageSize;
			this.page = 1;
			await this.fetchList();
		},
		async updateRow(payload: SalaryUpdatePayload) {
			this.loading.update = true;
			try {
				await updateSalaryRow(payload);
				await this.fetchList();
			} catch (e: any) {
				this.error = e?.message || "修改薪资失败";
				throw e;
			} finally {
				this.loading.update = false;
			}
		},
	},
});

