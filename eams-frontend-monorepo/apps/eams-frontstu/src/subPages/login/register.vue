<script lang="ts" setup>
import { ref, reactive } from "vue";
import { useRouter } from "vue-router";
import Apis from "@/api";
import { useToast } from "wot-design-uni";
import LoginHead from "@/components/LoginHead.vue";

definePage({
	name: "register",
	type: "page",
	style: {
		navigationBarTitleText: "用户注册",
		titleNView: false,
	},
});

// 路由对象
const router = useRouter();
// 弹框提示组件
const { success: showSuccess, error: showError } = useToast();

// 表单数据
const model = reactive<{
	phone: string;
	code: string;
	name: string;
	password: string;
}>({
	phone: "",
	code: "",
	name: "",
	password: "",
});
// 表单引用对象
const form = ref();

// 获取验证码
function getCode() {
	if (!model.phone) {
		showError({ msg: "请输入手机号", duration: 3000 });
		return;
	}

	// 模拟发送验证码
	showSuccess({ msg: "已发送验证码", duration: 3000 });
}

// 提交表单
function handleSubmit() {
	form.value
		.validate()
		.then(({ valid }: { valid: any }) => {
			if (valid) {
				// 模拟注册
				showSuccess({ msg: "注册成功", duration: 3000 });
				// 注册成功后跳转到登录页面
				setTimeout(() => {
					uni.navigateBack();
				}, 1500);
			}
		})
		.catch((error: any) => {
			console.log(error, "error");
		});
}

// 返回登录
function goLogin() {
	uni.navigateBack();
}
</script>

<template>
	<!-- 标题 -->
	<LoginHead title="欢迎注册账号" />
	<!-- 注册相关表单 -->
	<wd-form ref="form" :model="model">
		<wd-cell-group border>
			<wd-input
				v-model="model.phone"
				label="手机号码"
				label-width="100px"
				prop="phone"
				clearable
				placeholder="请输入手机号"
				:rules="[{ required: true, message: '请填写手机号' }]"
			/>
			<wd-input
				v-model="model.code"
				label="短信验证"
				label-width="100px"
				prop="code"
				clearable
				placeholder="请输入短信验证码"
				:rules="[{ required: true, message: '请填写验证码' }]"
			>
				<template #suffix>
					<wd-button type="primary" size="small" @click="getCode">获取验证码</wd-button>
				</template>
			</wd-input>
			<wd-input
				v-model="model.name"
				label="你的姓名"
				label-width="100px"
				prop="name"
				clearable
				placeholder="请输入你的姓名"
				:rules="[{ required: true, message: '请填写姓名' }]"
			/>
			<wd-input
				v-model="model.password"
				label="登录密码"
				label-width="100px"
				prop="password"
				show-password
				clearable
				placeholder="请输入密码"
				:rules="[{ required: true, message: '请填写密码' }]"
			/>
		</wd-cell-group>
		<view class="footer">
			<wd-button type="primary" size="large" :round="false" block @click="handleSubmit">注册</wd-button>
			<wd-button type="success" size="large" :round="false" plain block @click="goLogin">已有账号？去登录</wd-button>
		</view>
	</wd-form>
</template>

<style scoped>
.footer {
	display: flex;
	flex-direction: column;
	gap: 20px;
	padding: 20px 10px;
}
</style>
