<script setup lang="ts">
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";

definePage({
	name: "teacherHomeworkPublish",
	style: {
		navigationBarTitleText: "布置作业内容",
		titleNView: false,
	},
});

const toast = useGlobalToast();

function submitForm() {
	toast.show("发布作业接口的请求体还未明确，当前先保留表单展示。");
}
</script>

<template>
	<view class="teacher-publish-page">
		<teacher-nav-bar title="布置作业内容" :show-refresh="false" />
		<view class="teacher-publish-card">
			<view class="teacher-publish-tip">当前接口还缺少明确的请求 DTO，页面先保留表单形态，等后端补齐后再接真实提交。</view>
			<view class="teacher-publish-row">
				<text class="teacher-publish-label teacher-publish-label--required">选择班级</text>
				<text class="teacher-publish-value">待接班级选择</text>
			</view>
			<view class="teacher-publish-row">
				<text class="teacher-publish-label teacher-publish-label--required">作业标题</text>
				<text class="teacher-publish-value">请输入标题</text>
			</view>
			<view class="teacher-publish-row teacher-publish-row--textarea">
				<text class="teacher-publish-label teacher-publish-label--required">作业要求</text>
				<text class="teacher-publish-value">请输入内容</text>
			</view>
			<view class="teacher-publish-row teacher-publish-row--upload">
				<text class="teacher-publish-label">附件</text>
				<view class="teacher-publish-upload">
					<view class="i-carbon:add text-26px text-#667085" />
					<text>选择图片</text>
				</view>
			</view>
		</view>
		<view class="teacher-publish-action">
			<wd-button type="primary" block @click="submitForm">提交</wd-button>
		</view>
	</view>
</template>

<style scoped>
.teacher-publish-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-publish-card {
	margin-top: 10px;
	background: #fff;
}

.teacher-publish-tip {
	padding: 16px;
	font-size: 13px;
	line-height: 1.7;
	color: #f97316;
	background: #fff7ed;
}

.teacher-publish-row {
	display: flex;
	align-items: center;
	justify-content: space-between;
	padding: 16px;
	border-bottom: 1px solid #edf0f5;
}

.teacher-publish-row--textarea {
	align-items: flex-start;
	flex-direction: column;
	gap: 10px;
	min-height: 108px;
}

.teacher-publish-row--upload {
	align-items: flex-start;
	flex-direction: column;
	gap: 14px;
}

.teacher-publish-label {
	font-size: 15px;
	color: #111827;
}

.teacher-publish-label--required::before {
	content: "*";
	margin-right: 2px;
	color: #f04438;
}

.teacher-publish-value {
	font-size: 15px;
	color: #b5bfce;
}

.teacher-publish-upload {
	display: flex;
	flex-direction: column;
	align-items: center;
	justify-content: center;
	width: 96px;
	height: 96px;
	border-radius: 10px;
	background: #f3f4f6;
	gap: 6px;
	font-size: 13px;
	color: #667085;
}

.teacher-publish-action {
	position: fixed;
	right: 12px;
	bottom: calc(env(safe-area-inset-bottom) + 18px);
	left: 12px;
}
</style>
