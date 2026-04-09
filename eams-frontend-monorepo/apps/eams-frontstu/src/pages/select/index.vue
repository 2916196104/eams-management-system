<script setup lang="ts">
import { computed, ref } from "vue";
import ParentEmptyState from "@/components/parent/ParentEmptyState.vue";
import { selectCategories, selectCourses, type SelectCategory, type SelectCourse } from "./mock";

definePage({
	name: "select",
	layout: "tabbar",
	style: {
		navigationBarTitleText: "选课",
		titleNView: false,
	},
});

const router = useRouter();
const showCategoryPanel = ref(false);
const activeCategoryId = ref("geography");

// 顶部第一排固定展示的分类
const visibleTabs = computed(() => selectCategories.slice(0, 6));

// 当前激活分类
const activeCategory = computed<SelectCategory | undefined>(() =>
	selectCategories.find(item => item.id === activeCategoryId.value),
);

// mock 动态筛选课程
const filteredCourses = computed<Array<SelectCourse>>(() => {
	if (activeCategoryId.value === "recommend") {
		return selectCourses.filter(item => item.recommended);
	}

	return selectCourses.filter(item => item.categoryId === activeCategoryId.value);
});

function selectCategory(categoryId: string) {
	activeCategoryId.value = categoryId;
	showCategoryPanel.value = false;
}

function toggleCategoryPanel() {
	showCategoryPanel.value = !showCategoryPanel.value;
}

function closeCategoryPanel() {
	showCategoryPanel.value = false;
}

function openCourseDetail(courseId: string) {
	router.push({
		path: "/subPages/select/course-detail",
		query: {
			id: courseId,
		},
	} as any);
}

function applyCourse(course: SelectCourse) {
	uni.showToast({
		title: `${course.title} 报名接口待接入`,
		icon: "none",
	});
}
</script>

<template>
	<view class="select-page">
		<!-- 顶部分类栏 -->
		<view class="select-page__header">
			<scroll-view scroll-x class="select-page__tabs" :show-scrollbar="false">
				<view class="select-page__tabs-inner">
					<view
						v-for="item in visibleTabs"
						:key="item.id"
						class="select-page__tab"
						:class="{ 'select-page__tab--active': activeCategoryId === item.id }"
						@click="selectCategory(item.id)"
					>
						{{ item.name }}
					</view>
				</view>
			</scroll-view>

			<view class="select-page__toggle" @click="toggleCategoryPanel">
				<view class="i-carbon:grid text-18px text-#31c7a5" />
			</view>
		</view>

		<!-- 展开的全部分类面板 -->
		<view v-if="showCategoryPanel" class="select-page__panel-mask" @click="closeCategoryPanel">
			<view class="select-page__panel" @click.stop>
				<view class="select-page__panel-grid">
					<view
						v-for="item in selectCategories"
						:key="item.id"
						class="select-page__panel-chip"
						:class="{ 'select-page__panel-chip--active': activeCategoryId === item.id }"
						@click="selectCategory(item.id)"
					>
						{{ item.name }}
					</view>
				</view>
				<view class="select-page__panel-close" @click="closeCategoryPanel">
					<view class="i-carbon:close text-18px text-#94a3b8" />
				</view>
			</view>
		</view>

		<!-- 课程内容列表 -->
		<view class="select-page__content">
			<view class="select-page__summary">
				<view class="select-page__summary-title">{{ activeCategory?.name || "课程" }}</view>
				<view class="select-page__summary-subtitle">当前共 {{ filteredCourses.length }} 门课程可选</view>
			</view>

			<template v-if="filteredCourses.length">
				<view
					v-for="course in filteredCourses"
					:key="course.id"
					class="course-card"
					@click="openCourseDetail(course.id)"
				>
					<view class="course-card__cover" :style="{ background: course.coverColor }">
						<view class="course-card__subject">{{ course.subject }}</view>
						<view class="course-card__title">{{ course.title }}</view>
						<view class="course-card__subtitle">{{ course.subTitle }}</view>
					</view>

					<view class="course-card__body">
						<view class="course-card__meta">
							<text>{{ course.teacher }}</text>
							<text>{{ course.lessonCount }} 课次</text>
							<text>{{ course.suitableFor }}</text>
						</view>

						<view class="course-card__tags">
							<text v-for="tag in course.tags" :key="tag" class="course-card__tag">{{ tag }}</text>
						</view>

						<view class="course-card__footer">
							<view>
								<text class="course-card__price-symbol">¥</text>
								<text class="course-card__price">{{ course.price }}</text>
							</view>
							<view class="course-card__action" @click.stop="applyCourse(course)">立即报名</view>
						</view>
					</view>
				</view>
			</template>

			<ParentEmptyState
				v-else
				text="暂无课程 敬请期待"
				sub-text="可以切换其它分类看看"
				:card="false"
				min-height="260px"
			/>
		</view>
	</view>
</template>

<style scoped>
.select-page {
	min-height: 100vh;
	background: #f5f7fb;
}

.select-page__header {
	position: sticky;
	top: 0;
	z-index: 8;
	display: grid;
	grid-template-columns: 1fr 52px;
	align-items: center;
	background: #fff;
	border-bottom: 1px solid #eef2f7;
}

.select-page__tabs {
	white-space: nowrap;
}

.select-page__tabs-inner {
	display: inline-flex;
	align-items: center;
	padding: 0 10px;
}

.select-page__tab {
	position: relative;
	padding: 14px 12px;
	font-size: 15px;
	color: #3f4a5a;
}

.select-page__tab--active {
	color: #31c7a5;
	font-weight: 700;
}

.select-page__tab--active::after {
	content: "";
	position: absolute;
	left: 50%;
	bottom: 6px;
	width: 22px;
	height: 3px;
	border-radius: 999px;
	background: #31c7a5;
	transform: translateX(-50%);
}

.select-page__toggle {
	height: 100%;
	display: flex;
	align-items: center;
	justify-content: center;
	border-left: 1px solid #eef2f7;
	background: #fff;
}

.select-page__panel-mask {
	position: fixed;
	inset: 44px 0 0;
	z-index: 9;
	background: rgba(17, 24, 39, 0.06);
}

.select-page__panel {
	padding: 16px 14px 12px;
	border-radius: 0 0 22px 22px;
	background: #fff;
	box-shadow: 0 10px 24px rgba(64, 86, 122, 0.08);
}

.select-page__panel-grid {
	display: grid;
	grid-template-columns: repeat(4, minmax(0, 1fr));
	gap: 12px;
}

.select-page__panel-chip {
	height: 34px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 12px;
	background: #f3f5f8;
	font-size: 14px;
	color: #202939;
}

.select-page__panel-chip--active {
	background: #31c7a5;
	color: #fff;
	font-weight: 700;
}

.select-page__panel-close {
	margin-top: 12px;
	display: flex;
	justify-content: flex-end;
}

.select-page__content {
	padding: 14px 12px 24px;
	display: flex;
	flex-direction: column;
	gap: 14px;
}

.select-page__summary {
	padding: 6px 2px 0;
}

.select-page__summary-title {
	font-size: 18px;
	font-weight: 700;
	color: #1f2937;
}

.select-page__summary-subtitle {
	margin-top: 4px;
	font-size: 12px;
	color: #94a3b8;
}

.course-card {
	overflow: hidden;
	border-radius: 18px;
	background: #fff;
	box-shadow: 0 8px 22px rgba(64, 86, 122, 0.08);
}

.course-card__cover {
	padding: 18px 16px 20px;
	color: #fff;
}

.course-card__subject {
	width: fit-content;
	padding: 4px 10px;
	border-radius: 999px;
	background: rgba(255, 255, 255, 0.22);
	font-size: 12px;
	font-weight: 700;
}

.course-card__title {
	margin-top: 16px;
	font-size: 22px;
	font-weight: 700;
}

.course-card__subtitle {
	margin-top: 8px;
	font-size: 13px;
	line-height: 1.5;
	color: rgba(255, 255, 255, 0.9);
}

.course-card__body {
	padding: 16px;
}

.course-card__meta {
	display: flex;
	flex-wrap: wrap;
	gap: 8px 14px;
	font-size: 13px;
	color: #697589;
}

.course-card__tags {
	margin-top: 14px;
	display: flex;
	flex-wrap: wrap;
	gap: 8px;
}

.course-card__tag {
	padding: 4px 10px;
	border-radius: 999px;
	background: #edf9f5;
	font-size: 12px;
	color: #20a786;
}

.course-card__footer {
	margin-top: 18px;
	display: flex;
	align-items: center;
	justify-content: space-between;
}

.course-card__price-symbol {
	font-size: 14px;
	font-weight: 700;
	color: #ff7d4d;
}

.course-card__price {
	font-size: 26px;
	font-weight: 800;
	color: #ff7d4d;
}

.course-card__action {
	padding: 10px 18px;
	border-radius: 999px;
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	font-size: 14px;
	font-weight: 700;
	color: #fff;
}
</style>
