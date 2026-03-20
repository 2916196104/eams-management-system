<!-- 分页 -->
<template>
	<!-- 本组件完全沿用elm的分页插件，只做简单的封装，不做任何修改 -->
	<el-pagination
		v-model:page-size="pageSize"
		:size="'small'"
		:total="1000"
		:page-sizes="[10, 20, 50, 100, 200]"
		background
		layout="total, sizes, prev, pager, next, jumper"
	/>
</template>
<script setup lang="ts">
import { ref } from "vue";
const pageSize = ref(20);
</script>
