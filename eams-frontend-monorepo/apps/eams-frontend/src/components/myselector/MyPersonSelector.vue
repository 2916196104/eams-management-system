<template>
	<div ref="rootRef" class="my-person-selector">
		<!-- 触发输入框 -->
		<el-input v-model="selectedPersonName" :placeholder="placeholder" readonly @click="toggleSelector">
			<template #suffix>
				<el-icon :class="{ 'rotate-icon': selectorVisible }">
					<ArrowDown />
				</el-icon>
			</template>
		</el-input>

		<!-- 选择器面板 -->
		<transition name="el-zoom-in-top">
			<div v-show="selectorVisible" class="selector-panel" :style="{ width: panelWidth }">
				<!-- 搜索框 -->
				<div class="search-box">
					<el-input v-model="searchKeyword" :placeholder="searchPlaceholder" clearable @input="handleSearch">
						<template #prefix>
							<el-icon><Search /></el-icon>
						</template>
					</el-input>
				</div>

				<!-- 数据表格 -->
				<div class="table-container">
					<el-table :data="filteredData" :height="tableHeight" stripe border>
						<el-table-column type="index" label="序号" width="60" align="center" />

						<el-table-column
							v-for="col in props.columns"
							:key="col.prop"
							:prop="col.prop"
							:label="col.label"
							:min-width="col.minWidth"
							:width="col.width"
						/>

						<el-table-column label="操作" width="80" align="center">
							<template #default="{ row }">
								<el-button type="primary" size="small" link @click="selectPerson(row)">选择</el-button>
							</template>
						</el-table-column>
					</el-table>
				</div>

				<!-- 分页器 -->
				<div class="pagination-container">
					<el-pagination
						size="small"
						:pager-count="5"
						v-model:current-page="currentPage"
						v-model:page-size="pageSize"
						:page-sizes="pageSizes"
						:total="filteredTotal"
						layout="total, sizes, prev, pager, next, jumper"
						@size-change="handleSizeChange"
						@current-change="handleCurrentChange"
					/>
				</div>
			</div>
		</transition>
	</div>
</template>

<script setup lang="ts">
import { ref, computed, watch, onMounted, onUnmounted } from "vue";
import { ArrowDown, Search } from "@element-plus/icons-vue";
import type { MyPersonSelectorProps, PersonData } from "./type";

const rootRef = ref<HTMLElement | null>(null);
// 定义组件属性
const props = withDefaults(defineProps<MyPersonSelectorProps>(), {
	placeholder: "请选择",
	searchPlaceholder: "请输入关键字搜索",
	panelWidth: "580px",
	tableHeight: "438px",
	pageSizes: () => [10, 20, 50, 100],
	defaultPageSize: 10,
	columns: () => [
		{ prop: "name", label: "姓名", minWidth: 100 },
		{ prop: "department", label: "部门", minWidth: 120 },
		{ prop: "phone", label: "手机号", minWidth: 130 },
	],
});

// 定义组件事件
const emit = defineEmits<{
	select: [person: PersonData];
	"update:modelValue": [person: PersonData | null];
}>();

// 内部状态
const selectorVisible = ref(false);
const searchKeyword = ref("");
const currentPage = ref(1);
const pageSize = ref(props.defaultPageSize);
const selectedPerson = ref<PersonData | null>(props.modelValue || null);
const allData = ref<PersonData[]>([]);

// 计算选中的姓名显示
const selectedPersonName = computed(() => {
	return selectedPerson.value?.name || "";
});

// 计算过滤后的数据
const filteredData = computed(() => {
	let data = allData.value;

	// 根据搜索关键字过滤
	if (searchKeyword.value) {
		const keyword = searchKeyword.value.toLowerCase();
		data = data.filter((item) => item.name.toLowerCase().includes(keyword));
	}

	// 分页处理
	const start = (currentPage.value - 1) * pageSize.value;
	const end = start + pageSize.value;
	return data.slice(start, end);
});

// 计算过滤后的总数
const filteredTotal = computed(() => {
	if (searchKeyword.value) {
		const keyword = searchKeyword.value.toLowerCase();
		return allData.value.filter((item) => item.name.toLowerCase().includes(keyword)).length;
	}
	return allData.value.length;
});

// 切换选择器显示状态
function toggleSelector() {
	selectorVisible.value = !selectorVisible.value;
}

// 处理搜索
function handleSearch() {
	currentPage.value = 1;
}

// 处理每页显示条数变化
function handleSizeChange(val: number) {
	pageSize.value = val;
	currentPage.value = 1;
}

// 处理当前页变化
function handleCurrentChange(val: number) {
	currentPage.value = val;
}

// 选择人员
function selectPerson(person: PersonData) {
	selectedPerson.value = person;
	emit("select", person);
	emit("update:modelValue", person);
	selectorVisible.value = false;
}

// 加载数据
async function loadData() {
	if (props.dataLoader) {
		try {
			const data = await props.dataLoader();
			allData.value = data;
		} catch (error) {
			console.error("加载人员数据失败:", error);
		}
	} else if (props.data) {
		allData.value = props.data;
	}
}

// 监听外部数据变化
watch(
	() => props.data,
	(newData) => {
		if (newData) {
			allData.value = newData;
		}
	},
	{ immediate: true },
);

// 监听 modelValue 变化
watch(
	() => props.modelValue,
	(newValue) => {
		selectedPerson.value = newValue ?? null;
	},
);

// 点击外部关闭选择器
function handleClickOutside(event: MouseEvent) {
	const target = event.target;
	if (rootRef.value && target instanceof Node && !rootRef.value.contains(target)) {
		selectorVisible.value = false;
	}
}

onMounted(() => {
	loadData();
	document.addEventListener("click", handleClickOutside);
});

onUnmounted(() => {
	document.removeEventListener("click", handleClickOutside);
});

// 暴露方法给父组件
defineExpose({
	openSelector: () => {
		selectorVisible.value = true;
	},
	closeSelector: () => {
		selectorVisible.value = false;
	},
	loadData,
});
</script>

<style scoped>
.my-person-selector {
	position: relative;
	display: inline-block;
	width: 100%;
}

.my-person-selector .rotate-icon {
	transform: rotate(180deg);
	transition: transform 0.3s;
}

.my-person-selector .selector-panel {
	position: absolute;
	top: 100%;
	left: 0;
	z-index: 1000;
	margin-top: 8px;
	background: #fff;
	border-radius: 4px;
	box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
	overflow: hidden;
}

.my-person-selector .selector-panel .search-box {
	padding: 12px;
	border-bottom: 1px solid #ebeef5;
}

.my-person-selector .selector-panel .table-container {
	padding: 12px;
}

.my-person-selector .selector-panel .pagination-container {
	padding: 12px;
	border-top: 1px solid #ebeef5;
	background: #fafafa;
	display: flex;
	justify-content: flex-end;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination) {
	display: flex;
	flex-wrap: wrap;
	justify-content: flex-end;
	align-items: center;
	gap: 8px;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .el-pagination__total) {
	flex-shrink: 0;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .el-pagination__sizes) {
	flex-shrink: 0;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .btn-prev),
.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .btn-next) {
	flex-shrink: 0;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .el-pager) {
	flex-shrink: 0;
}

.my-person-selector .selector-panel .pagination-container :deep(.el-pagination .el-pagination__jump) {
	flex-shrink: 0;
}
</style>
