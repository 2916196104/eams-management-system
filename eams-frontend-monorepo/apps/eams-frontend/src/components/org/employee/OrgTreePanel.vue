<template>
	<el-card class="org-panel" shadow="never">
		<template #header>
			<div class="panel-title"><el-icon><House /></el-icon>机构列表</div>
		</template>
		<el-tree
			v-loading="loading"
			:data="data"
			node-key="id"
			:props="{ label: 'name', children: 'children' }"
			:expand-on-click-node="false"
			highlight-current
			:current-node-key="selectedId"
			default-expand-all
			@node-click="handleNodeClick"
		>
			<template #default="{ data: node }">
				<span class="node-text">{{ node.name }}</span>
			</template>
		</el-tree>
	</el-card>
</template>

<script setup lang="ts">
import { House } from "@element-plus/icons-vue";
import type { OrgNode } from "@/apis/org/employeeManage";

defineProps<{
	data: OrgNode[];
	loading: boolean;
	selectedId: string;
}>();

const emit = defineEmits<{
	(e: "select", orgId: string): void;
}>();

function handleNodeClick(node: OrgNode) {
	emit("select", node.id);
}
</script>

<style scoped>
.org-panel {
	height: 100%;
}

.panel-title {
	display: flex;
	align-items: center;
	gap: 6px;
	font-weight: 700;
}

.node-text {
	font-size: 14px;
}
</style>

