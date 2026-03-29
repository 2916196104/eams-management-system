import { defineStore } from "pinia";
import { ElMessage } from "element-plus";
import type { PageResult, PositionPermissionRow, PositionPermissionSavePayload, PositionRow } from "@/apis/org/positionManage";
import { deletePositions, queryPositionList, queryPositionPermissions, removePositionPermissions, savePosition, savePositionPermission } from "@/apis/org/positionManage";

export const usePositionManageStore = defineStore("positionManage", {
	state: () => ({
		keyword: "",
		loading: false,
		pageIndex: 1,
		pageSize: 30,
		total: 0,
		list: [] as PositionRow[],

		permissionLoading: false,
		permissionPositionId: "" as string,
		permissionPageIndex: 1,
		permissionPageSize: 10,
		permissionTotal: 0,
		permissionList: [] as PositionPermissionRow[],
	}),
	actions: {
		async fetchList() {
			this.loading = true;
			try {
				const res: PageResult<PositionRow> = await queryPositionList({
					name: this.keyword.trim() || undefined,
					pageIndex: this.pageIndex,
					pageSize: this.pageSize,
				});
				this.list = res.rows;
				this.total = res.total;
			} catch {
				ElMessage.error("加载数据失败");
			} finally {
				this.loading = false;
			}
		},
		async setPage(pageIndex: number) {
			this.pageIndex = pageIndex;
			await this.fetchList();
		},
		async setPageSize(pageSize: number) {
			this.pageSize = pageSize;
			this.pageIndex = 1;
			await this.fetchList();
		},
		async search(keyword: string) {
			this.keyword = keyword;
			this.pageIndex = 1;
			await this.fetchList();
		},
		async refresh() {
			await this.fetchList();
		},
		async savePosition(payload: { id?: string; name: string }) {
			try {
				await savePosition(payload);
				ElMessage.success(payload.id ? "修改成功" : "新增成功");
				await this.fetchList();
			} catch (e) {
				const err = e as Error;
				ElMessage.error(err.message || "保存失败");
			}
		},
		async batchDelete(ids: string[]) {
			if (!ids.length) return;
			try {
				await deletePositions(ids);
				ElMessage.success("删除成功");
				// 如果删空当前页，回到上一页
				if (this.list.length === ids.length && this.pageIndex > 1) this.pageIndex -= 1;
				await this.fetchList();
			} catch (e) {
				const err = e as Error;
				ElMessage.error(err.message || "删除失败");
			}
		},

		async openPermission(positionId: string) {
			this.permissionPositionId = positionId;
			this.permissionPageIndex = 1;
			await this.fetchPermissionList();
		},
		async fetchPermissionList() {
			if (!this.permissionPositionId) return;
			this.permissionLoading = true;
			try {
				const res = await queryPositionPermissions({
					positionId: this.permissionPositionId,
					pageIndex: this.permissionPageIndex,
					pageSize: this.permissionPageSize,
				});
				this.permissionList = res.rows;
				this.permissionTotal = res.total;
			} catch (e) {
				const err = e as Error;
				ElMessage.error(err.message || "获取数据权限失败");
			} finally {
				this.permissionLoading = false;
			}
		},
		async setPermissionPage(pageIndex: number) {
			this.permissionPageIndex = pageIndex;
			await this.fetchPermissionList();
		},
		async setPermissionPageSize(pageSize: number) {
			this.permissionPageSize = pageSize;
			this.permissionPageIndex = 1;
			await this.fetchPermissionList();
		},
		async savePermission(payload: Omit<PositionPermissionSavePayload, "positionId">) {
			if (!this.permissionPositionId) return;
			try {
				await savePositionPermission({
					...payload,
					positionId: this.permissionPositionId,
				});
				ElMessage.success(payload.id ? "修改成功" : "新增成功");
				await this.fetchPermissionList();
			} catch (e) {
				const err = e as Error;
				ElMessage.error(err.message || "保存失败");
			}
		},
		async removePermissions(ids: string[]) {
			if (!ids.length) return;
			try {
				await removePositionPermissions(ids);
				ElMessage.success("删除成功");
				await this.fetchPermissionList();
			} catch (e) {
				const err = e as Error;
				ElMessage.error(err.message || "删除失败");
			}
		},
	},
});

