<script lang="ts" setup>
definePage({
	name: "login",
	type: "page",
	style: {
		navigationBarTitleText: "用户登录",
		titleNView: false,
	},
});

// 路由对象
const router = useRouter();
// 提示信息组件
const toast = useGlobalToast();

// 用户名
const username = ref<string>("");
// 密码
const password = ref<string>("");
// 版权信息
const copyright = ref<string>("Copyright © 2026-2027 零壹星球");
const isDevMode = import.meta.env.MODE === "development";

// 页面跳转
function navigateTo(name: string) {
	router.push({ name });
}

// 执行登录
async function login() {
	Apis.login
		.post_login_auth_login({
			data: { username: username.value, password: password.value, terminalType: "user" },
		})
		.then((res) => {
			if (res.code === 10000 && res.data) {
				// 存储token信息
				const { token, tokenHead, refreshToken } = res.data;
				uni.setStorageSync('token', token);
				uni.setStorageSync('tokenHead', tokenHead);
				uni.setStorageSync('refreshToken', refreshToken);
				
				router.pushTab({ name: "home" });
			} else {
				toast.error({ msg: "登录失败，请检查用户名或密码", duration: 3000 });
			}
		})
		.catch(() => {
			toast.error({ msg: "登录请求失败，请稍后重试", duration: 3000 });
		});
}

function debugEnterHome() {
	router.pushTab({ name: "home" });
}
</script>

<template>
	<!-- 标题 -->
	<login-head title="欢迎-登录零壹教务家长端" :show-back="false" />

	<!-- 用户名和密码输入框 -->
	<view class="input-box bg-white dark:bg-[var(--wot-dark-background2)]">
		<wd-input v-model="username" placeholder="输入用户名" size="large" center>
			<template #prefix>
				<view class="i-carbon:user text-22px dark:text-white" />
			</template>
		</wd-input>

		<wd-input v-model="password" placeholder="请输入密码" size="large" center show-password>
			<template #prefix>
				<view class="i-carbon:password text-19px dark:text-white" />
			</template>
		</wd-input>

		<wd-text text="登录密码从管理员获取或">
			<template #suffix>
				<wd-text text="找回密码" type="primary" @click="navigateTo('forget')" />
			</template>
		</wd-text>
	</view>

	<!-- 操作按钮 -->
	<view class="btn-box">
		<wd-button type="primary" :round="false" size="large" block @click="login">登录</wd-button>
		<wd-button type="success" :round="false" size="large" plain block @click="navigateTo('register')">注册</wd-button>
		<wd-button v-if="isDevMode" type="warning" :round="false" size="large" plain block @click="debugEnterHome">
			开发调试进入首页
		</wd-button>
	</view>

	<!-- 版权信息 -->
	<view class="copyright">
		{{ copyright }}
	</view>
</template>

<style scoped>
.input-box {
	padding-top: 25px;
	padding-bottom: 25px;
	display: flex;
	flex-direction: column;
	gap: 15px;
	text-align: right;

	.wd-input {
		height: 30px;
	}

	.wd-text {
		margin-right: 10px;
	}
}

.btn-box {
	display: flex;
	flex-direction: column;
	padding: 20px 10px;
	gap: 20px;
}

.copyright {
	position: absolute;
	bottom: 15px;
	width: 100%;
	text-align: center;
	color: grey;
}
</style>
