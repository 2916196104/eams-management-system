<template>
	<!-- 离线隐藏打印容器 -->
	<div id="print-wrapper" class="print-wrapper">
		<div class="print-title">
			<h2>{{ printTitle }}</h2>
			<p>打印时间：{{ printTime }}</p>
		</div>
		<table class="print-content-table" border="1" cellpadding="8" cellspacing="0">
			<thead>
				<tr>
					<th v-for="item in props.columnList" :key="item.prop">
						{{ item.label }}
					</th>
				</tr>
			</thead>
			<tbody>
				<tr v-for="(row, idx) in props.tableData" :key="idx">
					<td v-for="item in props.columnList" :key="item.prop">
						{{ row[item.prop] ?? "-" }}
					</td>
				</tr>
			</tbody>
		</table>
	</div>
</template>

<script setup lang="ts">
import { computed } from "vue";

// 接收父组件传参
interface Props {
	// 打印标题
	printTitle?: string;
	// 表头配置 和页面表格一致
	columnList: Array<{ label: string; prop: string }>;
	// 表格数据源
	tableData: any[];
}

const props = defineProps<Props>();

// 格式化打印时间
const printTime = computed(() => {
	return new Date().toLocaleString();
});

// 暴露打印方法给父组件
const handlePrint = () => {
	// 核心浏览器打印逻辑
	const bodyDom = document.body;
	const originHtml = bodyDom.innerHTML;

	// 获取打印容器html
	const printDom = document.getElementById("print-wrapper");
	if (!printDom) return;

	// 替换页面内容为打印内容
	bodyDom.innerHTML = printDom.innerHTML;
	// 调用打印
	window.print();

	// 打印完成还原页面
	setTimeout(() => {
		bodyDom.innerHTML = originHtml;
		// 刷新vue响应式（防止页面卡死）
		window.location.reload();
	}, 200);
};

defineExpose({
	handlePrint,
});
</script>

<style scoped>
/* 默认把打印容器移出可视区 */
.print-wrapper {
	position: absolute;
	left: -9999px;
	top: 0;
}
.print-title {
	text-align: center;
	margin-bottom: 24px;
}
</style>

<style>
/* 全局打印媒体样式 */
@media print {
	@page {
		size: A4;
		margin: 15mm;
	}
	html,
	body {
		height: auto;
	}
	.print-content-table {
		width: 100%;
		border-collapse: collapse;
		font-size: 12px;
	}
	.print-content-table th,
	.print-content-table td {
		border: 1px solid #333;
		padding: 8px;
		text-align: center;
	}
	.print-content-table th {
		background-color: #f5f7fa;
	}
}
</style>
