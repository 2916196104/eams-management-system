<template>
	<el-card class="school-notice">
		<h5 class="title">{{ title }}</h5>

		<!-- 公告表格 -->
		<el-table :data="list" border size="small" style="width: 100%" max-height="300">
			<el-table-column prop="title" label="标题" />

			<el-table-column label="操作" width="90" fixed="right">
				<template #default="{ row }">
					<el-button type="text" size="small" @click="openDetail(row)">详情</el-button>
				</template>
			</el-table-column>
		</el-table>

		<!-- 详情弹窗 -->
		<el-dialog v-model="visible" :title="current.title" width="900px" class="custom-dialog">
			<div v-html="current.content"></div>

			<template #footer>
				<el-button size="small" @click="visible = false">关闭</el-button>
			</template>
		</el-dialog>
	</el-card>
</template>

<script setup>
import { ref, watch } from "vue";

/* ===== props ===== */
const props = defineProps({
	title: {
		type: String,
		default: "学校公告",
	},
	data: {
		type: Array,
		default: () => [],
	},
});

/* ===== 数据 ===== */
const list = ref([]);
const visible = ref(false);
const current = ref({});

/* ===== 监听父组件数据 ===== */
watch(
	() => props.data,
	(val) => {
		list.value = val || [];
	},
	{ immediate: true },
);

/* ===== 打开详情 ===== */
const openDetail = (row) => {
	current.value = row;
	visible.value = true;
};
</script>

<style scoped>
.school-notice {
	margin: 10px;
	margin-top: 0;
	margin-right: 0;
}

.title {
	margin: 0 0 5px;
	font-weight: bold;
}

.custom-dialog img {
	max-width: 100%;
}
</style>
