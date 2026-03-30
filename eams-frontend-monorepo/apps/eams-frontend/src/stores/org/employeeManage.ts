import { defineStore } from "pinia";
import { ElMessage } from "element-plus";
import {
	changeEmployeeStatus,
	createEmployee,
	deleteEmployees,
	exportEmployees,
	queryEmployeeList,
	queryOrgTree,
	queryRoleOptions,
	queryStudentCandidates,
	setEmployeeRole,
	resetEmployeePassword,
	transferEmployeeOrg,
	transferToStudent,
	type EmployeeCreatePayload,
	type EmployeeItem,
	type EmployeeUpdatePayload,
	type OrgNode,
	type StudentCandidate,
	updateEmployee,
} from "@/apis/org/employeeManage";

interface EmployeeManageState {
	orgTree: OrgNode[];
	selectedOrgId: string;
	keyword: string;
	status: "" | "在职" | "离职";
	page: number;
	pageSize: number;
	total: number;
	list: EmployeeItem[];
	roleOptions: string[];
	studentCandidates: StudentCandidate[];
	loading: {
		org: boolean;
		list: boolean;
		add: boolean;
		batch: boolean;
		student: boolean;
	};
}

export const useEmployeeManageStore = defineStore("employeeManage", {
	state: (): EmployeeManageState => ({
		orgTree: [],
		selectedOrgId: "",
		keyword: "",
		status: "",
		page: 1,
		pageSize: 20,
		total: 0,
		list: [],
		roleOptions: [],
		studentCandidates: [],
		loading: {
			org: false,
			list: false,
			add: false,
			batch: false,
			student: false,
		},
	}),
	actions: {
		async initPage() {
			const results = await Promise.allSettled([this.fetchOrgTree(), this.fetchEmployeeList(), this.fetchRoleOptions()]);
			if (results.some((r) => r.status === "rejected")) {
				ElMessage.error("加载数据失败");
			}
		},
		async fetchOrgTree() {
			this.loading.org = true;
			try {
				this.orgTree = await queryOrgTree();
			} catch (e) {
				throw e;
			} finally {
				this.loading.org = false;
			}
		},
		async fetchEmployeeList() {
			this.loading.list = true;
			try {
				const { list, total } = await queryEmployeeList({
					orgId: this.selectedOrgId || undefined,
					keyword: this.keyword,
					status: this.status,
					page: this.page,
					pageSize: this.pageSize,
				});
				this.list = list;
				this.total = total;
			} catch (e) {
				throw e;
			} finally {
				this.loading.list = false;
			}
		},
		async exportEmployeeList() {
			this.loading.batch = true;
			try {
				await exportEmployees({
					orgId: this.selectedOrgId || undefined,
					keyword: this.keyword,
					status: this.status,
					page: this.page,
					pageSize: this.pageSize,
				});
			} finally {
				this.loading.batch = false;
			}
		},
		setOrgAndQuery(orgId: string) {
			this.selectedOrgId = orgId;
			this.page = 1;
			return this.fetchEmployeeList();
		},
		setQueryAndSearch(payload: { keyword?: string; status?: "" | "在职" | "离职" }) {
			if (typeof payload.keyword !== "undefined") this.keyword = payload.keyword;
			if (typeof payload.status !== "undefined") this.status = payload.status;
			this.page = 1;
			return this.fetchEmployeeList();
		},
		setPage(page: number) {
			this.page = page;
			return this.fetchEmployeeList();
		},
		setPageSize(pageSize: number) {
			this.pageSize = pageSize;
			this.page = 1;
			return this.fetchEmployeeList();
		},
		async addEmployee(payload: EmployeeCreatePayload) {
			this.loading.add = true;
			try {
				await createEmployee(payload);
				this.page = 1;
				await this.fetchEmployeeList();
			} catch (e) {
				throw e;
			} finally {
				this.loading.add = false;
			}
		},
		async editEmployee(payload: EmployeeUpdatePayload) {
			this.loading.add = true;
			try {
				await updateEmployee(payload);
				await this.fetchEmployeeList();
			} finally {
				this.loading.add = false;
			}
		},
		async changePassword(id: string, newPassword: string) {
			this.loading.batch = true;
			try {
				await resetEmployeePassword(id, newPassword);
			} finally {
				this.loading.batch = false;
			}
		},
		async fetchRoleOptions() {
			try {
				this.roleOptions = await queryRoleOptions();
			} catch (e) {
				throw e;
			}
		},
		async batchSetRole(ids: string[], roleName: string) {
			this.loading.batch = true;
			try {
				await setEmployeeRole(ids, roleName);
				await this.fetchEmployeeList();
			} finally {
				this.loading.batch = false;
			}
		},
		async batchDelete(ids: string[]) {
			this.loading.batch = true;
			try {
				await deleteEmployees(ids);
				this.page = 1;
				await this.fetchEmployeeList();
			} finally {
				this.loading.batch = false;
			}
		},
		async batchTransferOrg(ids: string[], targetOrgId: string) {
			this.loading.batch = true;
			try {
				await transferEmployeeOrg(ids, targetOrgId);
				await this.fetchEmployeeList();
			} finally {
				this.loading.batch = false;
			}
		},
		async batchChangeStatus(ids: string[], status: "在职" | "离职", date?: string) {
			this.loading.batch = true;
			try {
				await changeEmployeeStatus(ids, status, date);
				await this.fetchEmployeeList();
			} finally {
				this.loading.batch = false;
			}
		},
		async fetchStudentCandidates(keyword = "") {
			this.loading.student = true;
			try {
				this.studentCandidates = await queryStudentCandidates(keyword);
			} finally {
				this.loading.student = false;
			}
		},
		async batchTransferStudent(ids: string[], studentId: string) {
			this.loading.batch = true;
			try {
				await transferToStudent(ids, studentId);
			} finally {
				this.loading.batch = false;
			}
		},
	},
});

