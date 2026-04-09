<template>
	<div class="root">
		<div class="title">占位页面</div>
		<div class="desc">当前路由：{{ route.path }}</div>
	</div>
</template>

<script setup lang="ts">
import { useRoute } from "vue-router";

const route = useRoute();
</script>

<style scoped>
.root {
	background: #ffffff;
	border-radius: 6px;
	padding: 16px;
}

.title {
	font-size: 16px;
	font-weight: 600;
	margin-bottom: 8px;
}

.desc {
	color: #666;
}
</style>
