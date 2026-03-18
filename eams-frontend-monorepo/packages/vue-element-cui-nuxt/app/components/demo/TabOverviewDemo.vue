<template>
	<div class="space-y-4">
		<CuiTab v-model:active-tab="activeTab" :tabs="tabs" />
		<div class="rounded-xl border border-dashed border-border bg-muted/20 p-3 text-sm text-muted-foreground">
			当前激活标签：{{ activeTab }}
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";

import { CuiTab } from "@eams-monorepo/vue-element-cui";
import type { CuiTabItem } from "@eams-monorepo/vue-element-cui";

const activeTab = ref("basic");

const tabs: CuiTabItem[] = [
	{ name: "basic", label: "基础信息", content: "管理资产主数据、负责人和状态。" },
	{ name: "logs", label: "处理记录", content: "集中展示流转日志和审批意见。" },
	{ name: "attachments", label: "附件", content: "挂载图片、附件和导入导出模板。" },
];
</script>
