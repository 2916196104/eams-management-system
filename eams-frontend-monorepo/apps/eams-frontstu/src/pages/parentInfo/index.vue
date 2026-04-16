<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "parentInfo",
	style: {
		navigationBarTitleText: "家长信息",
		titleNView: false,
	},
});

interface ParentInfo {
	name?: string;
	phone?: string;
	email?: string;
	createTime?: string;
}

interface ParentEditForm {
	name: string;
	phone: string;
}

interface PasswordForm {
	oldPassword: string;
	newPassword: string;
	confirmPassword: string;
}

const userStore = useUserStore();
const userInfo = ref<ParentInfo>({});
const isLoading = ref(false);
const isEditing = ref(false);
const showPasswordModal = ref(false);
const isPasswordSubmitting = ref(false);
const editForm = ref<ParentEditForm>({
	name: "",
	phone: "",
});
const passwordForm = ref<PasswordForm>({
	oldPassword: "",
	newPassword: "",
	confirmPassword: "",
});

const displayName = computed(() => userInfo.value.name || userStore.userInfo.nickName || "家长用户");
const displayPhone = computed(() => userInfo.value.phone || userStore.userInfo.phone || "未设置");
const displayEmail = computed(() => userInfo.value.email || "未设置");
const registerTime = computed(() => userInfo.value.createTime || userStore.userInfo.regDate || "未记录");
const avatarText = computed(() => (displayName.value.trim().charAt(0) || "家").toUpperCase());
const profilePercent = computed(() => {
	const fields = [
		Boolean(userInfo.value.name || userStore.userInfo.nickName),
		Boolean(userInfo.value.phone || userStore.userInfo.phone),
		Boolean(userInfo.value.email),
		Boolean(userInfo.value.createTime || userStore.userInfo.regDate),
	];
	const filled = fields.filter(Boolean).length;
	return Math.round((filled / fields.length) * 100);
});
const passwordReady = computed(() => {
	return Boolean(
		passwordForm.value.oldPassword.trim() &&
			passwordForm.value.newPassword.trim() &&
			passwordForm.value.confirmPassword.trim(),
	);
});

function syncEditForm() {
	editForm.value = {
		name: userInfo.value.name || userStore.userInfo.nickName || "",
		phone: userInfo.value.phone || userStore.userInfo.phone || "",
	};
}

function resetPasswordForm() {
	passwordForm.value = {
		oldPassword: "",
		newPassword: "",
		confirmPassword: "",
	};
}

function toggleEditMode() {
	if (isEditing.value) {
		syncEditForm();
		isEditing.value = false;
		return;
	}

	syncEditForm();
	isEditing.value = true;
}

function openPasswordModal() {
	resetPasswordForm();
	showPasswordModal.value = true;
}

function closePasswordModal() {
	if (isPasswordSubmitting.value) return;
	showPasswordModal.value = false;
	resetPasswordForm();
}

async function loadParentInfo() {
	isLoading.value = true;
	try {
		const res: any = await Apis.me.get_me_get_parentinfo({});
		userInfo.value = res?.data || {};
		if (userInfo.value.name || userInfo.value.phone) {
			userStore.updateUserInfo({
				nickName: userInfo.value.name || userStore.userInfo.nickName,
				phone: userInfo.value.phone || userStore.userInfo.phone,
			});
		}
		syncEditForm();
	}
	catch (error) {
		console.error("获取家长信息失败:", error);
		uni.showToast({
			title: "加载失败，请稍后重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function updateParentInfo() {
	if (!editForm.value.name.trim() || !editForm.value.phone.trim()) {
		uni.showToast({
			title: "请填写姓名和手机号",
			icon: "none",
		});
		return;
	}

	isLoading.value = true;
	try {
		const res: any = await Apis.me.put_me_modify_name({
			data: {
				name: editForm.value.name.trim(),
				phone: editForm.value.phone.trim(),
			},
		});

		if (res?.code === 10000) {
			userStore.updateUserInfo({
				nickName: editForm.value.name.trim(),
				phone: editForm.value.phone.trim(),
			});
			uni.showToast({
				title: "修改成功",
				icon: "success",
			});
			isEditing.value = false;
			await loadParentInfo();
		}
	}
	catch (error) {
		console.error("修改家长信息失败:", error);
		uni.showToast({
			title: "修改失败，请重试",
			icon: "none",
		});
	}
	finally {
		isLoading.value = false;
	}
}

async function updatePassword() {
	const oldPassword = passwordForm.value.oldPassword.trim();
	const newPassword = passwordForm.value.newPassword.trim();
	const confirmPassword = passwordForm.value.confirmPassword.trim();

	if (!oldPassword || !newPassword || !confirmPassword) {
		uni.showToast({
			title: "请填写完整密码信息",
			icon: "none",
		});
		return;
	}

	if (newPassword !== confirmPassword) {
		uni.showToast({
			title: "两次输入的新密码不一致",
			icon: "none",
		});
		return;
	}

	isPasswordSubmitting.value = true;
	try {
		const res: any = await Apis.me.put_me_modify_password({
			data: {
				oldPassword,
				newPassword,
			},
		});

		if (res?.code === 10000) {
			uni.showToast({
				title: "密码修改成功",
				icon: "success",
			});
			closePasswordModal();
		}
	}
	catch (error) {
		console.error("修改密码失败:", error);
		uni.showToast({
			title: "修改失败，请重试",
			icon: "none",
		});
	}
	finally {
		isPasswordSubmitting.value = false;
	}
}

onMounted(() => {
	loadParentInfo();
});
</script>

<template>
	<view class="parent-info-page">
		<view class="parent-info-page__bg" />
		<ParentNavBar title="家长信息" :right-text="isEditing ? '取消' : '编辑'" @right-click="toggleEditMode" />

		<view class="parent-info-page__content">
			<view class="profile-hero">
				<view class="profile-hero__badge">家长账号</view>
				<view class="profile-hero__main">
					<view class="profile-hero__avatar">{{ avatarText }}</view>
					<view class="profile-hero__copy">
						<view class="profile-hero__name">{{ displayName }}</view>
						<view class="profile-hero__phone">{{ displayPhone }}</view>
					</view>
				</view>
				<view class="profile-hero__stats">
					<view class="profile-hero__stat">
						<view class="profile-hero__value">{{ profilePercent }}%</view>
						<view class="profile-hero__label">资料完整度</view>
					</view>
					<view class="profile-hero__stat profile-hero__stat--right">
						<view class="profile-hero__value profile-hero__value--small">{{ registerTime }}</view>
						<view class="profile-hero__label">注册时间</view>
					</view>
				</view>
			</view>

			<view v-if="!isEditing" class="section-card">
				<view class="section-card__header">
					<view class="section-card__title">基础资料</view>
					<view class="section-card__subtitle">以下信息将展示在家长端个人资料中</view>
				</view>

				<view class="info-row">
					<view class="info-row__icon">
						<view class="i-carbon:user-profile text-18px text-#15916f" />
					</view>
					<view class="info-row__content">
						<view class="info-row__label">姓名</view>
						<view class="info-row__value">{{ displayName }}</view>
					</view>
				</view>

				<view class="info-row">
					<view class="info-row__icon">
						<view class="i-carbon:phone text-18px text-#15916f" />
					</view>
					<view class="info-row__content">
						<view class="info-row__label">手机号</view>
						<view class="info-row__value">{{ displayPhone }}</view>
					</view>
				</view>

				<view class="info-row">
					<view class="info-row__icon">
						<view class="i-carbon:email text-18px text-#15916f" />
					</view>
					<view class="info-row__content">
						<view class="info-row__label">邮箱</view>
						<view class="info-row__value">{{ displayEmail }}</view>
					</view>
				</view>

				<view class="info-row info-row--last">
					<view class="info-row__icon">
						<view class="i-carbon:calendar text-18px text-#15916f" />
					</view>
					<view class="info-row__content">
						<view class="info-row__label">注册时间</view>
						<view class="info-row__value">{{ registerTime }}</view>
					</view>
				</view>
			</view>

			<view v-if="!isEditing" class="section-card section-card--soft">
				<view class="section-card__header">
					<view class="section-card__title">账号安全</view>
					<view class="section-card__subtitle">弹窗已改成更适合输入密码的表单样式，确认前会先校验新密码是否一致</view>
				</view>
				<button class="primary-btn" :disabled="isLoading" @click="openPasswordModal">修改登录密码</button>
			</view>

			<view v-else class="section-card section-card--soft">
				<view class="section-card__header">
					<view class="section-card__title">编辑资料</view>
					<view class="section-card__subtitle">保存后，我的页面和个人资料会同步更新</view>
				</view>

				<view class="form-field">
					<view class="form-field__label">姓名</view>
					<view class="form-field__shell">
						<input v-model="editForm.name" class="form-field__input" placeholder="请输入姓名" />
					</view>
				</view>

				<view class="form-field">
					<view class="form-field__label">手机号</view>
					<view class="form-field__shell">
						<input v-model="editForm.phone" class="form-field__input" placeholder="请输入手机号" />
					</view>
				</view>

				<view class="action-row">
					<button class="ghost-btn" :disabled="isLoading" @click="toggleEditMode">取消</button>
					<button class="primary-btn" :disabled="isLoading" @click="updateParentInfo">保存资料</button>
				</view>
			</view>
		</view>

		<uni-popup v-model:visible="showPasswordModal" mode="center">
			<view class="password-modal">
				<view class="password-modal__badge">账号安全</view>
				<view class="password-modal__title">修改登录密码</view>
				<view class="password-modal__desc">请输入当前密码，并设置新的登录密码。保存前会校验两次输入是否一致。</view>

				<view class="password-field">
					<view class="password-field__label">旧密码</view>
					<view class="password-field__shell">
						<input
							v-model="passwordForm.oldPassword"
							password
							class="password-field__input"
							placeholder="请输入旧密码"
						/>
					</view>
				</view>

				<view class="password-field">
					<view class="password-field__label">新密码</view>
					<view class="password-field__shell">
						<input
							v-model="passwordForm.newPassword"
							password
							class="password-field__input"
							placeholder="请输入新密码"
						/>
					</view>
				</view>

				<view class="password-field">
					<view class="password-field__label">确认新密码</view>
					<view class="password-field__shell">
						<input
							v-model="passwordForm.confirmPassword"
							password
							class="password-field__input"
							placeholder="请再次输入新密码"
						/>
					</view>
				</view>

				<view class="password-tips">
					<view class="password-tip">
						<view class="i-carbon:checkmark-filled text-12px text-#15916f" />
						<text>提交前会先校验两次新密码是否一致</text>
					</view>
					<view class="password-tip">
						<view class="i-carbon:checkmark-filled text-12px text-#15916f" />
						<text>密码修改成功后，下次登录请使用新密码</text>
					</view>
				</view>

				<view class="password-actions">
					<button class="ghost-btn" :disabled="isPasswordSubmitting" @click="closePasswordModal">取消</button>
					<button
						class="primary-btn"
						:disabled="isPasswordSubmitting || !passwordReady"
						@click="updatePassword"
					>
						确认修改
					</button>
				</view>
			</view>
		</uni-popup>
	</view>
</template>

<style scoped>
.parent-info-page {
	position: relative;
	min-height: 100vh;
	background: #f4f7fb;
	overflow: hidden;
}

.parent-info-page__bg {
	position: absolute;
	top: 0;
	left: 0;
	right: 0;
	height: 260px;
	background: linear-gradient(180deg, #ddfff6 0%, rgba(221, 255, 246, 0) 100%);
}

.parent-info-page__content {
	position: relative;
	padding: 16px 16px 28px;
}

.profile-hero {
	padding: 22px 20px;
	border-radius: 28px;
	color: #fff;
	background: linear-gradient(135deg, #31c7a5 0%, #34a5ff 100%);
	box-shadow: 0 18px 42px rgba(49, 199, 165, 0.24);
}

.profile-hero__badge {
	display: inline-flex;
	align-items: center;
	padding: 6px 12px;
	border-radius: 999px;
	background: rgba(255, 255, 255, 0.18);
	font-size: 12px;
	font-weight: 600;
}

.profile-hero__main {
	display: flex;
	align-items: center;
	margin-top: 16px;
}

.profile-hero__avatar {
	width: 64px;
	height: 64px;
	flex-shrink: 0;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 24px;
	background: rgba(255, 255, 255, 0.22);
	font-size: 28px;
	font-weight: 700;
}

.profile-hero__copy {
	flex: 1;
	margin-left: 14px;
	min-width: 0;
}

.profile-hero__name {
	font-size: 24px;
	font-weight: 700;
	line-height: 1.25;
}

.profile-hero__phone {
	margin-top: 8px;
	font-size: 14px;
	color: rgba(255, 255, 255, 0.88);
}

.profile-hero__stats {
	display: flex;
	margin-top: 20px;
	padding-top: 18px;
	border-top: 1px solid rgba(255, 255, 255, 0.2);
}

.profile-hero__stat {
	flex: 1;
}

.profile-hero__stat--right {
	padding-left: 18px;
	margin-left: 18px;
	border-left: 1px solid rgba(255, 255, 255, 0.2);
}

.profile-hero__value {
	font-size: 28px;
	font-weight: 700;
	line-height: 1.2;
}

.profile-hero__value--small {
	font-size: 16px;
	word-break: break-all;
}

.profile-hero__label {
	margin-top: 8px;
	font-size: 13px;
	color: rgba(255, 255, 255, 0.84);
}

.section-card {
	margin-top: 16px;
	padding: 18px 16px;
	border-radius: 24px;
	background: #fff;
	box-shadow: 0 12px 30px rgba(15, 23, 42, 0.06);
}

.section-card--soft {
	background: linear-gradient(180deg, #ffffff 0%, #f8fbff 100%);
}

.section-card__header {
	margin-bottom: 6px;
}

.section-card__title {
	font-size: 18px;
	font-weight: 700;
	color: #111827;
}

.section-card__subtitle {
	margin-top: 6px;
	font-size: 13px;
	line-height: 1.6;
	color: #6b7280;
}

.info-row {
	display: flex;
	align-items: flex-start;
	padding: 14px 0;
	border-bottom: 1px solid #eef2f7;
}

.info-row--last {
	border-bottom: none;
	padding-bottom: 0;
}

.info-row__icon {
	width: 40px;
	height: 40px;
	flex-shrink: 0;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 16px;
	background: #effbf7;
}

.info-row__content {
	flex: 1;
	margin-left: 12px;
	min-width: 0;
}

.info-row__label {
	font-size: 13px;
	color: #6b7280;
}

.info-row__value {
	margin-top: 6px;
	font-size: 16px;
	font-weight: 600;
	color: #111827;
	word-break: break-all;
}

.form-field {
	margin-top: 14px;
}

.form-field__label {
	margin-bottom: 8px;
	font-size: 14px;
	font-weight: 600;
	color: #374151;
}

.form-field__shell {
	padding: 0 14px;
	border: 1px solid #e5edf6;
	border-radius: 16px;
	background: #f8fafc;
}

.form-field__input {
	width: 100%;
	height: 48px;
	font-size: 15px;
	color: #111827;
}

.action-row,
.password-actions {
	display: flex;
	margin-top: 20px;
}

.action-row button + button,
.password-actions button + button {
	margin-left: 12px;
}

.primary-btn,
.ghost-btn {
	flex: 1;
	height: 46px;
	border-radius: 16px;
	display: flex;
	align-items: center;
	justify-content: center;
	font-size: 15px;
	font-weight: 600;
}

.primary-btn {
	color: #fff;
	border: none;
	background: linear-gradient(135deg, #31c7a5 0%, #20b486 100%);
	box-shadow: 0 12px 24px rgba(49, 199, 165, 0.22);
}

.ghost-btn {
	color: #15916f;
	border: 1px solid rgba(49, 199, 165, 0.3);
	background: #fff;
}

.primary-btn::after,
.ghost-btn::after {
	border: none;
}

.primary-btn:disabled,
.ghost-btn:disabled {
	opacity: 0.65;
}

.password-modal {
	width: 86vw;
	max-width: 420px;
	padding: 20px 18px;
	border-radius: 28px;
	background: linear-gradient(180deg, #ffffff 0%, #f7fbff 100%);
	box-shadow: 0 22px 48px rgba(15, 23, 42, 0.18);
}

.password-modal__badge {
	display: inline-flex;
	align-items: center;
	padding: 6px 12px;
	border-radius: 999px;
	background: #effbf7;
	font-size: 12px;
	font-weight: 600;
	color: #15916f;
}

.password-modal__title {
	margin-top: 14px;
	font-size: 22px;
	font-weight: 700;
	color: #111827;
}

.password-modal__desc {
	margin-top: 8px;
	font-size: 14px;
	line-height: 1.7;
	color: #6b7280;
}

.password-field {
	margin-top: 16px;
}

.password-field__label {
	margin-bottom: 8px;
	font-size: 14px;
	font-weight: 600;
	color: #374151;
}

.password-field__shell {
	padding: 0 14px;
	border: 1px solid #dfe7f3;
	border-radius: 16px;
	background: #fff;
	box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.8);
}

.password-field__input {
	width: 100%;
	height: 48px;
	font-size: 15px;
	color: #111827;
}

.password-tips {
	margin-top: 16px;
	padding: 14px 14px 4px;
	border-radius: 18px;
	background: #f2fbf8;
}

.password-tip {
	display: flex;
	align-items: flex-start;
	margin-bottom: 10px;
	font-size: 13px;
	line-height: 1.6;
	color: #4b5563;
}

.password-tip text {
	margin-left: 8px;
}
</style>
