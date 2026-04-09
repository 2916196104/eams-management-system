const routes = [
	{
		path: "/material/manage",
		name: "MaterialManage",
		component: () => import("@/views/material/materialManagement/MaterialManagement.vue"),
	},
	{
		path: "/material/inventory",
		name: "MaterialInventory",
		component: () => import("@/views/material/inventoryRecords/InventoryRecords.vue"),
	},
];
export default routes;
