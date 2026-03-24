import { defineStore } from "pinia";
import { createOrg, deleteOrg, queryOrgManageTree, updateOrg, type OrgEditPayload, type OrgManageNode } from "@/apis/org/orgManage";

interface OrgManageState {
	tree: OrgManageNode[];
	expandedIds: string[];
	loading: boolean;
	submitting: boolean;
	error: string | null;
}

export const useOrgManageStore = defineStore("orgManage", {
	state: (): OrgManageState => ({
		tree: [],
		expandedIds: [],
		loading: false,
		submitting: false,
		error: null,
	}),
	actions: {
		async initPage() {
			await this.fetchTree();
		},
		async fetchTree() {
			this.loading = true;
			try {
				this.tree = await queryOrgManageTree();
				this.expandedIds = this.collectIds(this.tree);
			} catch (e: any) {
				this.error = e?.message || "获取组织树失败";
			} finally {
				this.loading = false;
			}
		},
		collectIds(nodes: OrgManageNode[]) {
			const ids: string[] = [];
			const walk = (items: OrgManageNode[]) => {
				items.forEach((i) => {
					ids.push(i.id);
					if (i.children?.length) walk(i.children);
				});
			};
			walk(nodes);
			return ids;
		},
		async addNode(payload: OrgEditPayload) {
			this.submitting = true;
			try {
				await createOrg(payload);
				await this.fetchTree();
			} finally {
				this.submitting = false;
			}
		},
		async editNode(payload: OrgEditPayload) {
			this.submitting = true;
			try {
				await updateOrg(payload);
				await this.fetchTree();
			} finally {
				this.submitting = false;
			}
		},
		async removeNode(id: string) {
			this.submitting = true;
			try {
				await deleteOrg(id);
				await this.fetchTree();
			} finally {
				this.submitting = false;
			}
		},
	},
});

