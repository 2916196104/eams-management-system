<script lang="ts" setup>
definePage({
	name: "register",
	type: "page",
	style: {
		navigationBarTitleText: "用户注册",
		titleNView: false,
	},
});

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
// 弹框提示组件
const { success: showSuccess } = useToast();

// 获取验证码
function getCode() {
	showSuccess({
		msg: "已发送验证码",
	});
}
// 提交表单
function handleSubmit() {
	form.value
		.validate()
		.then(({ valid }: { valid: any }) => {
			if (valid) {
				showSuccess({
					msg: "校验通过",
				});
			}
		})
		.catch((error: any) => {
			console.log(error, "error");
		});
}
// 返回登录
function goLogin() {
	showSuccess({
		msg: "已返回登录页面",
	});
	uni.navigateBack();
}
</script>

<template>
	<!-- 标题 -->
	<login-head title="欢迎注册账号" />
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
