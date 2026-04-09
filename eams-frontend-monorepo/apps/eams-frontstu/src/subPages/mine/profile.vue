<script setup lang="ts">
import { computed } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "mineProfile",
	style: {
		navigationBarTitleText: "资料",
		titleNView: false,
	},
});

const userStore = useUserStore();
const userInfo = computed(() => userStore.userInfo);

function navigateToPassword() {
	uni.navigateTo({
		url: "/subPages/mine/password",
	});
}

function editName() {
	uni.showModal({
		title: "修改姓名",
		editable: true,
		placeholderText: "请输入姓名",
		content: userInfo.value.nickName,
		success: async (result) => {
			const nextName = (result.content || "").trim();
			if (!result.confirm) return;
			if (!nextName) {
				uni.showToast({ title: "请输入姓名", icon: "none" });
				return;
			}

			try {
				await (Apis as any).me.put_me_modify_name({
					params: {
						name: nextName,
					},
					data: {
						name: nextName,
						phone: userInfo.value.phone,
						regDate: userInfo.value.regDate || "",
					},
				});
				userStore.updateUserInfo({ nickName: nextName });
				uni.showToast({ title: "修改成功", icon: "success" });
			}
			catch {
				uni.showToast({ title: "修改失败", icon: "none" });
			}
		},
	});
}

function logout() {
	uni.reLaunch({
		url: "/pages/index/index",
	});
}
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="资料" />
		<view class="page-content">
			<view class="profile-card">
				<view class="profile-card__avatar">
					<view class="i-carbon:user-avatar-filled-alt text-76px text-#d9d9d9" />
				</view>

				<view class="profile-card__row" @click="editName">
					<text>姓名(可修改)</text>
					<view class="profile-card__row-right">
						<text>{{ userInfo.nickName }}</text>
						<view class="i-carbon:chevron-right text-16px text-#b4bcc9" />
					</view>
				</view>
				<view class="profile-card__row">
					<text>手机号</text>
					<text>{{ userInfo.phone }}</text>
				</view>
				<view class="profile-card__row">
					<text>注册时间</text>
					<text>{{ userInfo.regDate || "--" }}</text>
				</view>

				<view class="profile-card__btn profile-card__btn--primary" @click="navigateToPassword">修改密码</view>
				<view class="profile-card__btn profile-card__btn--plain" @click="logout">退出登录</view>
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
	padding: 12px 0 20px;
}

.profile-card {
	background: #fff;
}

.profile-card__avatar {
	height: 180px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.profile-card__row {
	padding: 16px 18px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-top: 1px solid #eef2f7;
	font-size: 15px;
	color: #111827;
}

.profile-card__row-right {
	display: flex;
	align-items: center;
	gap: 6px;
}

.profile-card__btn {
	margin: 16px 12px 0;
	height: 44px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	font-size: 18px;
}

.profile-card__btn--primary {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.profile-card__btn--plain {
	margin-bottom: 20px;
	border: 1px solid #31c7a5;
	color: #31c7a5;
	background: #fff;
}
</style>
