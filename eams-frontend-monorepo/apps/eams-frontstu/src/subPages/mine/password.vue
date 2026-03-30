<script setup lang="ts">
import { reactive } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "minePassword",
	style: {
		navigationBarTitleText: "修改密码",
		titleNView: false,
	},
});

const userStore = useUserStore();
const form = reactive({
	oldPassword: "",
	newPassword: "",
	confirmPassword: "",
});

const visibleMap = reactive({
	oldPassword: false,
	newPassword: false,
	confirmPassword: false,
});

async function submit() {
	if (!form.oldPassword || !form.newPassword || !form.confirmPassword) {
		uni.showToast({ title: "请填写完整信息", icon: "none" });
		return;
	}
	if (form.newPassword !== form.confirmPassword) {
		uni.showToast({ title: "两次密码不一致", icon: "none" });
		return;
	}

	try {
		await (Apis as any).me.put_me_modify_password({
			params: {
				oldPassword: form.oldPassword,
				newPassword: form.newPassword,
				verifyPassword: form.confirmPassword,
			},
			data: {
				name: userStore.userInfo.nickName,
				phone: userStore.userInfo.phone,
				regDate: userStore.userInfo.regDate || "",
			},
		});
		uni.showToast({ title: "修改成功", icon: "success" });
		setTimeout(() => {
			uni.navigateBack();
		}, 500);
	}
	catch {
		uni.showToast({ title: "修改失败", icon: "none" });
	}
}
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="修改密码" />
		<view class="page-content">
			<view class="password-card">
				<view class="password-card__row">
					<text class="password-card__label">旧密码</text>
					<input v-model="form.oldPassword" class="password-card__input" :password="!visibleMap.oldPassword" placeholder="请输入内容" />
					<view class="i-carbon:view text-18px text-#c0c7d2" @click="visibleMap.oldPassword = !visibleMap.oldPassword" />
				</view>
				<view class="password-card__row">
					<text class="password-card__label">新密码</text>
					<input v-model="form.newPassword" class="password-card__input" :password="!visibleMap.newPassword" placeholder="请输入内容" />
					<view class="i-carbon:view text-18px text-#c0c7d2" @click="visibleMap.newPassword = !visibleMap.newPassword" />
				</view>
				<view class="password-card__row">
					<text class="password-card__label">重复新密码</text>
					<input
						v-model="form.confirmPassword"
						class="password-card__input"
						:password="!visibleMap.confirmPassword"
						placeholder="请输入内容"
					/>
					<view class="i-carbon:view text-18px text-#c0c7d2" @click="visibleMap.confirmPassword = !visibleMap.confirmPassword" />
				</view>

				<view class="password-card__submit" @click="submit">提交</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 12px;
}

.password-card {
	padding: 18px 16px;
	border-radius: 16px;
	background: #fff;
}

.password-card__row {
	padding: 12px 0;
	display: grid;
	grid-template-columns: 92px 1fr 24px;
	align-items: center;
	border-bottom: 1px solid #eef2f7;
}

.password-card__label {
	font-size: 15px;
	color: #111827;
}

.password-card__input {
	font-size: 14px;
	color: #111827;
}

.password-card__submit {
	margin-top: 26px;
	height: 44px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	border: 1px solid #31c7a5;
	font-size: 18px;
	color: #31c7a5;
}
</style>
