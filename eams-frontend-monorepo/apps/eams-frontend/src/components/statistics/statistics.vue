<!-- 统计组件(控制版) -->
<template>
	<el-card class="statistics">
		<div class="wrapper">
			<!-- 左侧图标 -->
			<div class="icon">
				<Icon :icon="iconName" class="svg" />
			</div>
			<!-- 右侧文字 -->
			<div class="text-container">
				<!-- 主文字 -->
				<div class="main">{{ targetText }}</div>
				<!-- 副文字 -->
				<div class="sub" ref="countRef">0</div>
			</div>
		</div>
	</el-card>
</template>
<script setup lang="ts">
import { ref, onMounted } from "vue";
import { Icon } from "@iconify/vue";
import { CountUp } from "countup.js";
const countRef = ref(null);
const { targetText, targetNumber } = defineProps({
	targetText: {
		type: String,
		default: "学员数",
	},
	// 目标数字
	targetNumber: {
		type: Number,
		default: 1000,
	},
	// 图标
	iconName: {
		type: String,
		default: "mdi:account",
	},
	// 图标颜色
	iconColor: {
		type: String,
		default: "red",
	},
	// 鼠标悬停时图标颜色
	hoverIconColor: {
		type: String,
		default: "white",
	},
	// 鼠标悬停时背景颜色
	hoverBgColor: {
		type: String,
		default: "red",
	},
});
onMounted(() => {
	// 提取目标数字为变量，避免硬编码
	if (countRef.value) {
		// 判断是否需要千分位
		const useGrouping = targetNumber >= 1000;
		// 创建数字滚动实例
		const countUp = new CountUp(countRef.value, targetNumber, {
			startVal: 0, // 起始值
			duration: 2, // 持续时间（秒）
			separator: ",", // 千分位分隔符
			useEasing: true,
			decimalPlaces: 0, // 明确指定小数位数（整数设为0）
			useGrouping: useGrouping, // 是否使用千分位分隔符
		});
		// 启动动画
		if (!countUp.error) {
			countUp.start();
		} else {
			console.error("数字滚动初始化失败:", countUp.error);
		}
	}
});
</script>
<style scoped>
.statistics {
	height: 108px;
	cursor: pointer;
	container-type: inline-size; /* 创建容器 */
}
.statistics :deep(.el-card__body) {
	padding: 0px;
}
.statistics :deep(.el-card__body) {
	overflow: hidden;
}
.statistics .wrapper {
	display: flex;
	align-items: center;
	justify-content: space-between;
	height: 100%;
	transition: background-color 0.3s ease;
}
.statistics .icon {
	font-size: 48px;
	margin: 14px;
	padding: 16px;
	line-height: 1;
	/* 过渡动画：hover变色更丝滑，避免生硬切换 */
	transition: background-color 0.3s ease;
	border-radius: 8px;
}
.statistics:hover .icon {
	background-color: v-bind(hoverBgColor);
}
.statistics .svg {
	width: 1em;
	height: 1em;
	transition: color 0.3s ease;
	color: v-bind(iconColor);
}
.statistics .wrapper:hover .svg {
	color: v-bind(hoverIconColor);
}
.statistics .text-container {
	display: flex;
	flex-direction: column;
	margin: 26px;
	margin-left: 0;
	line-height: 1; /* 重置文字默认行高 */
}
.statistics .text-container .main {
	color: rgba(0, 0, 0, 0.45);
	font-size: 16px;
	font-weight: 700;
	margin-bottom: 12px;
	line-height: 1;
}
.statistics .text-container .sub {
	color: #666;
	font-size: 20px;
	font-weight: 700;
	line-height: 1;
}
/* 容器查询：当卡片小于一定宽度时 */
@container (max-width: 215px) {
	.statistics .text-container {
		display: none;
	}
	.statistics .wrapper {
		justify-content: center;
	}
	.statistics .wrapper:hover {
		background-color: v-bind(hoverBgColor);
	}
	/* 小卡片 hover 时图标变色 */
	.statistics .wrapper:hover .svg {
		color: v-bind(hoverIconColor);
	}

	/* 覆盖原来的 hover 效果 */
	.statistics:hover .icon {
		background-color: transparent;
	}
}
</style>
