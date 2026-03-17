<template>
	<div class="space-y-4">
		<CuiTable :data="tableData" :columns="columns" border stripe>
			<template #status="{ row }">
				<el-tag :type="row.status === 'active' ? 'success' : 'info'">
					{{ row.status === "active" ? "启用" : "停用" }}
				</el-tag>
			</template>
		</CuiTable>
		<p class="text-sm text-muted-foreground">示例展示了状态标签插槽、默认边框和斑马纹配置。</p>
	</div>
</template>

<script setup lang="ts">
import { CuiTable } from "@eams-monorepo/vue-element-cui";
import type { CuiTableColumn } from "@eams-monorepo/vue-element-cui";

const tableData = [
	{ id: 1, name: "固定资产", owner: "财务共享中心", status: "active" },
	{ id: 2, name: "库存物料", owner: "供应链团队", status: "active" },
	{ id: 3, name: "报废工单", owner: "设备运维组", status: "inactive" },
];

const columns: CuiTableColumn[] = [
	{ prop: "name", label: "对象" },
	{ prop: "owner", label: "归属团队", minWidth: 160 },
	{ prop: "status", label: "状态", slot: "status", width: 120, align: "center" },
];
</script>
