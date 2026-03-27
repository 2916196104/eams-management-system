<template>
	<section class="panel-card notice-page">
		<div class="notice-page__title">{{ config.title }}</div>

		<el-form label-width="140px" class="notice-form">
			<el-form-item label="邮件通知">
				<el-switch v-model="setting.emailon" />
			</el-form-item>
			<el-form-item label="微信通知">
				<el-switch v-model="setting.wechaton" />
			</el-form-item>
			<el-form-item label="微信消息模板ID">
				<el-input v-model="setting.noticewechatId" />
			</el-form-item>
			<el-form-item label="短信通知">
				<el-switch v-model="setting.messageon" />
			</el-form-item>
			<el-form-item label="短信模板ID">
				<el-input v-model="setting.messageId_eg" />
			</el-form-item>
			<el-form-item label="提示信息">
				<el-input v-model="setting.tips" type="textarea" :rows="3" />
			</el-form-item>
		</el-form>

		<div class="notice-page__footer">
			<el-button type="primary" @click="handleSave">{{ config.saveButtonText }}</el-button>
		</div>
	</section>
</template>

<script setup lang="ts">
import { onMounted, reactive } from "vue";
import { ElMessage } from "element-plus";
import type { NoticeSettingDTO } from "@/apis/system/type";
import type { SystemNotificationPageConfig } from "../shared";

const props = defineProps<{
	config: SystemNotificationPageConfig;
}>();

const setting = reactive<NoticeSettingDTO>({
	name: props.config.settingName,
	emailon: false,
	messageId_eg: "",
	messageon: false,
	noticewechatId: "",
	tips: "",
	wechaton: false,
});

async function loadSetting() {
	const data = await props.config.loadSetting(props.config.settingName);
	setting.id = data.id;
	setting.name = props.config.settingName;
	setting.emailon = Boolean(data.emailon);
	setting.messageId_eg = data.messageId_eg || "";
	setting.messageon = Boolean(data.messageon);
	setting.noticewechatId = data.noticewechatId || "";
	setting.tips = data.tips || "";
	setting.wechaton = Boolean(data.wechaton);
}

async function handleSave() {
	await props.config.saveSetting({
		id: setting.id,
		name: props.config.settingName,
		emailon: Boolean(setting.emailon),
		messageId_eg: setting.messageId_eg || "",
		messageon: Boolean(setting.messageon),
		noticewechatId: setting.noticewechatId || "",
		tips: setting.tips || "",
		wechaton: Boolean(setting.wechaton),
	});
	ElMessage.success("通知设置已更新");
}

onMounted(() => {
	loadSetting();
});
</script>

<style scoped>
.panel-card {
	padding: 20px 24px;
	margin: 16px;
	background: #ffffff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.notice-page {
	max-width: 920px;
}

.notice-page__title {
	margin-bottom: 20px;
	font-size: 18px;
	font-weight: 700;
	color: #2f3c55;
}

.notice-form {
	max-width: 760px;
}

.notice-page__footer {
	padding-top: 8px;
}
</style>
