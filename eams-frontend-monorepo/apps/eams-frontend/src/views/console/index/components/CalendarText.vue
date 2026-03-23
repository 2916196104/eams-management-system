<template>
	<el-tooltip content="Append to .target" placement="right">
		<el-button text class="calendar-text">
			<div class="dot"></div>
			<slot name="default"></slot>
		</el-button>
	</el-tooltip>
</template>
<style scoped>
.calendar-text:hover {
	background-color: var(--el-button-hover-bg-color) !important;
}
.calendar-text {
	display: inline-flex;
	align-items: center; /* 垂直居中圆点和文本 */
	justify-content: flex-start; /* 水平靠左 */
	white-space: nowrap;
	overflow: hidden;
	max-width: 150px; /* 根据需要设置最大宽度 */
	padding: 0;
	height: auto;
}
.dot {
	width: 10px;
	height: 10px;
	border-radius: 50%;
	background-color: rgb(103, 194, 58);
	flex-shrink: 0;
	margin-right: 5px;
}
</style>
