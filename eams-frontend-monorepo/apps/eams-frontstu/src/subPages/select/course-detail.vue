<script setup lang="ts">
import { computed } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { getSelectCourseById } from "@/pages/select/mock";

definePage({
	name: "selectCourseDetail",
	style: {
		navigationBarTitleText: "课程详情",
		titleNView: false,
	},
});

const route = useRoute() as any;

// 当前选中的 mock 课程
const course = computed(() => getSelectCourseById(String(route.query?.id || "")));

function applyCourse() {
	if (!course.value) return;

	uni.showToast({
		title: `${course.value.title} 报名接口待接入`,
		icon: "none",
	});
}
</script>

<template>
	<view class="detail-page">
		<ParentNavBar title="课程详情" />

		<view class="detail-page__content">
			<view v-if="course" class="detail-card">
				<!-- 顶部封面信息 -->
				<view class="detail-card__hero" :style="{ background: course.coverColor }">
					<view class="detail-card__badge">{{ course.subject }}</view>
					<view class="detail-card__title">{{ course.title }}</view>
					<view class="detail-card__subtitle">{{ course.subTitle }}</view>
				</view>

				<!-- 课程基础信息 -->
				<view class="detail-card__section">
					<view class="detail-card__title-row">
						<view class="detail-card__section-title">课程信息</view>
						<view class="detail-card__price">¥{{ course.price }}</view>
					</view>
					<view class="detail-card__meta-grid">
						<view class="detail-card__metric">
							<text class="detail-card__metric-label">授课老师</text>
							<text class="detail-card__metric-value">{{ course.teacher }}</text>
						</view>
						<view class="detail-card__metric">
							<text class="detail-card__metric-label">总课次</text>
							<text class="detail-card__metric-value">{{ course.lessonCount }}</text>
						</view>
						<view class="detail-card__metric">
							<text class="detail-card__metric-label">适合年级</text>
							<text class="detail-card__metric-value">{{ course.suitableFor }}</text>
						</view>
						<view class="detail-card__metric">
							<text class="detail-card__metric-label">课程状态</text>
							<text class="detail-card__metric-value">待接选课接口</text>
						</view>
					</view>
				</view>

				<!-- 课程标签 -->
				<view class="detail-card__section">
					<view class="detail-card__section-title">课程标签</view>
					<view class="detail-card__tags">
						<view v-for="tag in course.tags" :key="tag" class="detail-card__tag">{{ tag }}</view>
					</view>
				</view>

				<!-- 课程亮点 -->
				<view class="detail-card__section">
					<view class="detail-card__section-title">课程亮点</view>
					<view class="detail-card__highlight-list">
						<view v-for="item in course.highlights" :key="item" class="detail-card__highlight-item">
							<view class="detail-card__highlight-dot" />
							<text>{{ item }}</text>
						</view>
					</view>
				</view>

				<!-- 课程介绍 -->
				<view class="detail-card__section">
					<view class="detail-card__section-title">课程介绍</view>
					<view class="detail-card__description">{{ course.description }}</view>
				</view>
			</view>

			<ParentEmptyState v-else text="暂无课程详情" sub-text="请返回上一页重新选择课程" min-height="220px" />
		</view>

		<!-- 底部报名按钮 -->
		<view v-if="course" class="detail-page__footer">
			<view class="detail-page__footer-tip">当前为选课原型页，后续接入真实选课接口</view>
			<view class="detail-page__submit-btn" @click="applyCourse">立即报名</view>
		</view>
	</view>
</template>

<style scoped>
.detail-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.detail-page__content {
	padding: 12px 12px 98px;
}

.detail-card {
	overflow: hidden;
	border-radius: 20px;
	background: #fff;
	box-shadow: 0 8px 24px rgba(64, 86, 122, 0.08);
}

.detail-card__hero {
	padding: 22px 18px 26px;
	color: #fff;
}

.detail-card__badge {
	width: fit-content;
	padding: 4px 10px;
	border-radius: 999px;
	background: rgba(255, 255, 255, 0.22);
	font-size: 12px;
	font-weight: 700;
}

.detail-card__title {
	margin-top: 16px;
	font-size: 26px;
	font-weight: 800;
}

.detail-card__subtitle {
	margin-top: 8px;
	font-size: 14px;
	line-height: 1.7;
	color: rgba(255, 255, 255, 0.92);
}

.detail-card__section {
	padding: 18px 16px;
	border-top: 1px solid #eef2f7;
}

.detail-card__title-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	gap: 12px;
}

.detail-card__section-title {
	font-size: 16px;
	font-weight: 700;
	color: #1f2937;
}

.detail-card__price {
	font-size: 24px;
	font-weight: 800;
	color: #ff7d4d;
}

.detail-card__meta-grid {
	margin-top: 14px;
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 12px;
}

.detail-card__metric {
	padding: 12px 14px;
	border-radius: 14px;
	background: #f8fafc;
	display: flex;
	flex-direction: column;
	gap: 6px;
}

.detail-card__metric-label {
	font-size: 12px;
	color: #94a3b8;
}

.detail-card__metric-value {
	font-size: 15px;
	font-weight: 700;
	color: #1f2937;
}

.detail-card__tags {
	margin-top: 14px;
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.detail-card__tag {
	padding: 6px 12px;
	border-radius: 999px;
	background: #edf9f5;
	font-size: 12px;
	color: #20a786;
}

.detail-card__highlight-list {
	margin-top: 12px;
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.detail-card__highlight-item {
	display: flex;
	align-items: flex-start;
	gap: 10px;
	font-size: 14px;
	line-height: 1.7;
	color: #475569;
}

.detail-card__highlight-dot {
	width: 8px;
	height: 8px;
	margin-top: 8px;
	border-radius: 999px;
	background: #31c7a5;
	flex-shrink: 0;
}

.detail-card__description {
	margin-top: 12px;
	font-size: 14px;
	line-height: 1.9;
	color: #475569;
}

.detail-page__footer {
	position: fixed;
	left: 0;
	right: 0;
	bottom: 0;
	padding: 12px 16px calc(12px + env(safe-area-inset-bottom));
	background: rgba(245, 247, 251, 0.96);
}

.detail-page__footer-tip {
	margin-bottom: 10px;
	text-align: center;
	font-size: 12px;
	color: #94a3b8;
}

.detail-page__submit-btn {
	height: 46px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	font-size: 16px;
	font-weight: 700;
	color: #fff;
	box-shadow: 0 10px 20px rgba(49, 199, 165, 0.22);
}
</style>
