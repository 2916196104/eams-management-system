<script lang="ts" setup>
import { onMounted, ref } from "vue";

defineProps({
	/** 标题 */
	title: {
		type: String,
		default: "请输入标题",
	},
	/** 是否显示返回按钮 */
	showBack: {
		type: Boolean,
		default: true,
	},
});

const isAnimated = ref(false);

onMounted(() => {
	// 组件挂载后触发动画
	setTimeout(() => {
		isAnimated.value = true;
	}, 100);
});
// 返回按钮点击事件
function goBack() {
	uni.navigateBack();
}
</script>

<template>
	<view class="title-container" :class="{ 'title-animated': isAnimated }">
		<!-- 背景装饰元素 -->
		<view class="bg-element bg-element-1" />
		<view class="bg-element bg-element-2" />
		<view class="bg-element bg-element-3" />
		<!-- 返回按钮 -->
		<view v-if="showBack" class="back-btn" @click="goBack">
			<wd-icon name="arrow-left" color="white" size="30" />
		</view>
		<!-- 主标题 -->
		<view class="title-content">
			<wd-text :text="title" color="white" size="30px" weight="bold" class="title-text" />
		</view>
		<!-- 标题装饰线 -->
		<view class="title-underline" />
		<!-- 粒子效果 -->
		<view class="particles">
			<view
				v-for="i in 15"
				:key="i"
				class="particle"
				:style="{
					left: `${Math.random() * 100}%`,
					animationDelay: `${Math.random() * 2}s`,
					width: `${Math.random() * 6 + 2}px`,
					height: `${Math.random() * 6 + 2}px`,
					opacity: Math.random() * 0.7 + 0.3,
				}"
			/>
		</view>
	</view>
</template>

<style scoped>
/* 移动动画 */
@keyframes movebackbtn {
	0% {
		transform: translateX(0) scale(1);
	}

	100% {
		transform: translateX(-5px) scale(1.1);
	}
}

.back-btn {
	position: absolute;
	left: 5px;
	top: 5px;
	width: 40px;
	height: 40px;
	z-index: 999;

	.wd-icon {
		animation: movebackbtn 1s ease-in-out infinite alternate;
	}
}

.title-container {
	position: relative;
	display: flex;
	justify-content: center;
	align-items: center;
	height: 200px;
	background: linear-gradient(to bottom, #00c6fb 0%, #005bea 100%);
	overflow: hidden;
	transition: all 0.8s cubic-bezier(0.175, 0.885, 0.32, 1.275);
	transform: translateY(20px);
	opacity: 0;
}

.title-animated {
	transform: translateY(0);
	opacity: 1;
}

.title-container::before {
	content: "";
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	bottom: 0;
	background: linear-gradient(45deg, transparent 30%, rgba(255, 255, 255, 0.1) 50%, transparent 70%);
	background-size: 200% 200%;
	animation: shimmer 3s infinite linear;
	z-index: 1;
}

.title-content {
	position: relative;
	z-index: 3;
	padding: 20px;
	text-align: center;
}

.title-text {
	position: relative;
	display: inline-block;
	text-shadow: 0 2px 10px rgba(0, 0, 0, 0.2);
	letter-spacing: 1px;
	animation: textGlow 2s ease-in-out infinite alternate;
}

.title-text::after {
	content: "";
	position: absolute;
	bottom: -8px;
	left: 50%;
	transform: translateX(-50%);
	width: 0;
	height: 3px;
	background: rgba(255, 255, 255, 0.8);
	border-radius: 2px;
	transition: width 0.5s ease;
}

.title-container:hover .title-text::after {
	width: 100%;
}

.title-underline {
	position: absolute;
	bottom: 20px;
	left: 50%;
	transform: translateX(-50%) scaleX(0);
	width: 80%;
	height: 2px;
	background: linear-gradient(90deg, transparent, rgba(255, 255, 255, 0.8), transparent);
	border-radius: 1px;
	animation: underlineReveal 1s ease-out 0.5s forwards;
}

/* 背景装饰元素 */
.bg-element {
	position: absolute;
	border-radius: 50%;
	background: rgba(255, 255, 255, 0.1);
	z-index: 1;
}

.bg-element-1 {
	top: -50px;
	right: -30px;
	width: 150px;
	height: 150px;
	animation: floatElement 20s infinite linear;
}

.bg-element-2 {
	bottom: -60px;
	left: -40px;
	width: 180px;
	height: 180px;
	animation: floatElement 25s infinite linear reverse;
}

.bg-element-3 {
	top: 50%;
	left: 20%;
	width: 80px;
	height: 80px;
	animation: floatElement 15s infinite linear;
	background: rgba(255, 255, 255, 0.05);
}

/* 粒子效果 */
.particles {
	position: absolute;
	top: 0;
	left: 0;
	width: 100%;
	height: 100%;
	pointer-events: none;
	z-index: 2;
}

.particle {
	position: absolute;
	background: rgba(255, 255, 255, 0.6);
	border-radius: 50%;
	animation: floatParticle 8s infinite linear;
}

/* 动画定义 */
@keyframes shimmer {
	0% {
		background-position: -200% -200%;
	}

	100% {
		background-position: 200% 200%;
	}
}

@keyframes textGlow {
	0% {
		text-shadow:
			0 2px 10px rgba(0, 0, 0, 0.2),
			0 0 20px rgba(255, 255, 255, 0.3);
	}

	100% {
		text-shadow:
			0 2px 15px rgba(0, 0, 0, 0.3),
			0 0 30px rgba(255, 255, 255, 0.5),
			0 0 40px rgba(255, 255, 255, 0.3);
	}
}

@keyframes underlineReveal {
	0% {
		transform: translateX(-50%) scaleX(0);
		opacity: 0;
	}

	50% {
		opacity: 0.5;
	}

	100% {
		transform: translateX(-50%) scaleX(1);
		opacity: 1;
	}
}

@keyframes floatElement {
	0% {
		transform: translate(0, 0) rotate(0deg);
	}

	25% {
		transform: translate(20px, 20px) rotate(90deg);
	}

	50% {
		transform: translate(0, 40px) rotate(180deg);
	}

	75% {
		transform: translate(-20px, 20px) rotate(270deg);
	}

	100% {
		transform: translate(0, 0) rotate(360deg);
	}
}

@keyframes floatParticle {
	0% {
		transform: translateY(200px) rotate(0deg);
		opacity: 0;
	}

	10% {
		opacity: 1;
	}

	90% {
		opacity: 1;
	}

	100% {
		transform: translateY(-100px) rotate(360deg);
		opacity: 0;
	}
}

/* 悬停效果 */
.title-container:hover .bg-element-1 {
	animation-duration: 15s;
}

.title-container:hover .bg-element-2 {
	animation-duration: 20s;
}

/* 响应式调整 */
@media (max-width: 768px) {
	.title-container {
		height: 160px;
	}

	.title-text {
		font-size: 24px;
	}

	.bg-element-1,
	.bg-element-2,
	.bg-element-3 {
		display: none;
		/* 在移动端隐藏大元素以提升性能 */
	}

	.particle {
		animation-duration: 6s;
	}
}

/* 暗色主题适配 */
@media (prefers-color-scheme: dark) {
	.title-container {
		background: linear-gradient(to bottom, #0066cc 0%, #003366 100%);
	}

	.title-text {
		text-shadow: 0 2px 8px rgba(0, 0, 0, 0.5);
	}

	.particle {
		background: rgba(255, 255, 255, 0.4);
	}
}

/* 加载时的骨架屏效果 */
.title-container:not(.title-animated) {
	background: linear-gradient(90deg, #e0e0e0 25%, #f0f0f0 50%, #e0e0e0 75%);
	background-size: 200% 100%;
	animation: loading 1.5s infinite;
}

@keyframes loading {
	0% {
		background-position: 200% 0;
	}

	100% {
		background-position: -200% 0;
	}
}
</style>
