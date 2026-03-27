<template>
	<div class="student-placeholder">
		<el-result icon="info" :title="title" sub-title="该页面为菜单占位，后续可替换为真实业务页面。" />
	</div>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { useRoute } from "vue-router";

const route = useRoute();
const title = computed(() => (route.meta?.label as string) || "学员模块");
</script>

<style scoped>
.student-placeholder {
	padding: 48px 24px;
	background: #fff;
	border-radius: 6px;
	min-height: 360px;
}
</style>
