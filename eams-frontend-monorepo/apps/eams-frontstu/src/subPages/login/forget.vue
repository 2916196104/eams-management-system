<script lang="ts" setup>
import { ref } from "vue";
import { useToast } from "wot-design-uni";
import LoginHead from "@/components/LoginHead.vue";

definePage({
	name: "forget",
	type: "page",
	style: {
		navigationBarTitleText: "忘记密码",
		titleNView: false,
	},
});

// 弹框提示组件
const { success: showSuccess, error: showError } = useToast();

const phone = ref<string>("");
const code = ref<string>("");
const password = ref<string>("");

// 返回登录
function goLogin() {
	uni.navigateBack();
}

// 获取验证码
function getCode() {
	if (!phone.value) {
		showError({ msg: "请输入手机号", duration: 3000 });
		return;
	}

	// 模拟发送验证码
	showSuccess({ msg: "已发送验证码", duration: 3000 });
}

// 提交密码修改
function settingPassword() {
	if (!phone.value || !code.value || !password.value) {
		showError({ msg: "请填写完整信息", duration: 3000 });
		return;
	}

	// 模拟密码修改
	showSuccess({ msg: "密码修改成功", duration: 3000 });
	// 密码修改成功后跳转到登录页面
	setTimeout(() => {
		uni.navigateBack();
	}, 1500);
}
</script>

<template>
	<!-- 标题 -->
	<LoginHead title="设置新密码" />
	<!-- 修改密码相关表单 -->
	<view class="input-box bg-white dark:bg-[var(--wot-dark-background2)]">
		<wd-input v-model="phone" placeholder="请输入手机号" prefix-icon="phone" size="large" center>
			<template #prefix>
				<wd-icon name="mobile" size="22px" class="dark:text-white" />
			</template>
		</wd-input>
		<wd-input v-model="code" placeholder="请输入短信验证码" size="large" center>
			<template #prefix>
				<wd-icon name="code" size="22px" class="dark:text-white" />
			</template>
			<template #suffix>
				<wd-button type="primary" size="small" @click="getCode">获取验证码</wd-button>
			</template>
		</wd-input>
		<wd-input v-model="password" placeholder="请输入新密码" size="large" center show-password>
			<template #prefix>
				<view class="i-carbon:password text-18px dark:text-white" />
			</template>
		</wd-input>
		<view class="login-text">
			<wd-text text="去登录" @click="goLogin" />
		</view>
	</view>
	<!-- 提交按钮 -->
	<wd-button type="primary" :round="false" size="large" :block="true" @click="settingPassword">提交密码修改</wd-button>
</template>

<style scoped>
.input-box {
	padding-top: 25px;
	padding-bottom: 15px;
	margin-bottom: 10px;

	.wd-input {
		height: 30px;
	}

	.login-text {
		text-align: right;
		margin-top: 20px;
		padding-right: 10px;
	}
}
</style>
