import { beforeEach, describe, expect, test, vi } from "vitest";
import { createPinia, setActivePinia } from "pinia";
import { useSystemPermissionStore } from "@/stores/systemPermission";
import {
	addRolepermStaff,
	deleteRoleperm,
	getPermissionList,
	getRolepermNameList,
	getRolepermStaffList,
	getSelectedPermissionList,
	saveRoleperm,
} from "@/apis/system/permission";

vi.mock("@/apis/system/permission", () => ({
	getRolepermNameList: vi.fn(),
	saveRoleperm: vi.fn(),
	deleteRoleperm: vi.fn(),
	getRolepermStaffList: vi.fn(),
	addRolepermStaff: vi.fn(),
	removeRolepermStaff: vi.fn(),
	getPermissionList: vi.fn(),
	getSelectedPermissionList: vi.fn(),
	saveRolePermission: vi.fn(),
}));

describe("useSystemPermissionStore", () => {
	beforeEach(() => {
		setActivePinia(createPinia());
		vi.clearAllMocks();
	});

	test("fetchRoles 失败时不会回退到本地静态角色", async () => {
		vi.mocked(getRolepermNameList).mockRejectedValue(new Error("network error"));

		const store = useSystemPermissionStore();

		const success = await store.fetchRoles();

		expect(success).toBe(false);
		expect(store.roles).toEqual([]);
	});

	test("fetchRoles 能兼容 reject 但响应体中仍有角色列表的情况", async () => {
		vi.mocked(getRolepermNameList).mockRejectedValue({
			data: {
				data: [{ id: 3, code: "leader", name: "校长" }],
			},
		});

		const store = useSystemPermissionStore();

		const success = await store.fetchRoles();

		expect(success).toBe(true);
		expect(store.roles).toEqual([{ id: 3, code: "leader", name: "校长" }]);
	});

	test("selectRole 会加载员工和已选权限", async () => {
		vi.mocked(getRolepermStaffList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: {
				rows: [{ staffId: 8, roleId: 2, name: "张老师", mobile: "13800000000" }],
			},
		});
		vi.mocked(getSelectedPermissionList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: {
				list: [
					{
						groupName: "系统管理",
						selectedPermissions: [{ id: 11, name: "系统参数", code: "system:param" }],
					},
				],
			},
		});

		const store = useSystemPermissionStore();

		await store.selectRole(2);

		expect(store.currentRoleId).toBe(2);
		expect(store.staffs).toEqual([{ staffId: 8, roleId: 2, name: "张老师", mobile: "13800000000" }]);
		expect(store.selectedPermissionIds).toEqual([11]);
	});

	test("fetchPermissions 能兼容 reject 且空数组响应", async () => {
		vi.mocked(getPermissionList).mockRejectedValue({
			status: 200,
			data: {
				data: [],
			},
		});

		const store = useSystemPermissionStore();

		const success = await store.fetchPermissions();

		expect(success).toBe(true);
		expect(store.permissionGroups).toEqual([]);
	});

	test("removeRole 能兼容 reject 但服务端已处理成功的情况", async () => {
		vi.mocked(deleteRoleperm).mockRejectedValue({
			status: 200,
			data: {
				message: "ok",
			},
		});
		vi.mocked(getRolepermNameList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: [],
		});

		const store = useSystemPermissionStore();

		const success = await store.removeRole(5);

		expect(success).toBe(true);
		expect(store.roles).toEqual([]);
	});

	test("addStaff 能兼容 reject 但刷新后可读到新人员的情况", async () => {
		vi.mocked(addRolepermStaff).mockRejectedValue({
			status: 200,
			data: {
				message: "ok",
			},
		});
		vi.mocked(getRolepermStaffList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: {
				rows: [{ staffId: 12, roleId: 3, name: "李老师", mobile: "13900000000" }],
			},
		});

		const store = useSystemPermissionStore();

		const success = await store.addStaff({ roleId: 3, name: "李老师", mobile: "13900000000" });

		expect(success).toBe(true);
		expect(store.staffs).toEqual([{ staffId: 12, roleId: 3, name: "李老师", mobile: "13900000000" }]);
	});

	test("saveRole 能兼容 reject 但刷新后可读到新角色的情况", async () => {
		vi.mocked(saveRoleperm).mockRejectedValue({
			status: 200,
			data: {
				message: "ok",
			},
		});
		vi.mocked(getRolepermNameList).mockResolvedValue({
			code: 10000,
			message: "ok",
			data: [{ id: 9, code: "manager", name: "管理员" }],
		});

		const store = useSystemPermissionStore();

		const success = await store.saveRole({ id: 9, code: "manager", name: "管理员" });

		expect(success).toBe(true);
		expect(store.roles).toEqual([{ id: 9, code: "manager", name: "管理员" }]);
	});
});
