import { defineStore } from "pinia";
import { ElMessage } from "element-plus";
import {
	buildOrgTreeFromList,
	queryOrgDetail,
	queryOrgList,
	removeOrg,
	saveOrg,
	type OrgDetail,
	type OrgListQuery,
	type OrgSavePayload,
	type OrgTreeRow,
} from "@/apis/org/orgManage";

interface OrgManageState {
	tree: OrgTreeRow[];
	listQuery: OrgListQuery;
	loading: boolean;
	submitting: boolean;
	detailLoading: boolean;
}

export const useOrgManageStore = defineStore("orgManage", {
	state: (): OrgManageState => ({
		tree: [],
		listQuery: {},
		loading: false,
		submitting: false,
		detailLoading: false,
	}),
	actions: {
		async initPage() {
			await this.fetchTree();
		},
		setListQuery(q: OrgListQuery) {
			this.listQuery = { ...q };
		},
		async fetchTree() {
			this.loading = true;
			try {
				const flat = await queryOrgList(this.listQuery);
				this.tree = buildOrgTreeFromList(flat);
			} catch {
				ElMessage.error("加载数据失败");
			} finally {
				this.loading = false;
			}
		},
		async loadDetail(orgId: number): Promise<OrgDetail | undefined> {
			this.detailLoading = true;
			try {
				return await queryOrgDetail(orgId);
			} finally {
				this.detailLoading = false;
			}
		},
		async save(payload: OrgSavePayload) {
			this.submitting = true;
			try {
				await saveOrg(payload);
				await this.fetchTree();
			} finally {
				this.submitting = false;
			}
		},
		async removeNode(orgId: number) {
			this.submitting = true;
			try {
				await removeOrg(orgId);
				await this.fetchTree();
			} finally {
				this.submitting = false;
			}
		},
	},
});
