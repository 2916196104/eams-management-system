<template>
	<section class="menu-placeholder">
		<el-card shadow="never" class="menu-placeholder__card">
			<el-result icon="info" :title="title" :sub-title="subTitle">
				<template #extra>
					<el-tag type="primary" effect="light">统一菜单已接入</el-tag>
				</template>
			</el-result>
		</el-card>
	</section>
</template>

<script setup lang="ts">
import { computed } from "vue";
import { useRoute } from "vue-router";

const route = useRoute();

const title = computed(() => (route.meta.label as string) || "页面建设中");
const subTitle = computed(
	() =>
		(route.meta.description as string) ||
		"当前页面已经接入统一参考菜单，业务内容后续可以继续在这个壳里补齐。",
);
</script>

<style scoped>
.menu-placeholder {
	min-height: 100%;
	padding: 24px;
	box-sizing: border-box;
}

.menu-placeholder__card {
	min-height: 360px;
	border-radius: 18px;
	border: 1px solid #e6ebf2;
}
</style>
