<script setup lang="ts">
import { ref } from "vue";
import type { CuiTableColumn } from "@eams-monorepo/vue-element-cui";

const rows = ref([
	{ name: "固定资产", status: "启用" },
	{ name: "库存物料", status: "停用" },
]);

const columns: CuiTableColumn<(typeof rows.value)[number]>[] = [
	{ prop: "name", label: "名称" },
	{ prop: "status", label: "状态" },
];
</script>

<template>
	<CuiTable :data="rows" :columns="columns" border />
</template>
