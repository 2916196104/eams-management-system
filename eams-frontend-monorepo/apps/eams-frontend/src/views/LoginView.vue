<!-- 登录页面 -->
<template>
	<div class="login-container">
		<!-- 雪花效果 -->
		<div class="snowflakes">
			<div v-for="i in 50" :key="i" class="snowflake" :style="getSnowflakeStyle()"></div>
		</div>

		<div class="login-wrapper">
			<div class="left-section">
				<div class="logo-area">
					<img src="/logo.jpg" alt="教务系统Logo" class="logo-img" />
					<h1 class="system-title">零壹教务系统</h1>
				</div>
				<div class="illustration-area">
					<img src="/login-illustration.png" alt="左侧插图" class="illustration-img" />
				</div>
			</div>
			<div class="right-section">
				<div class="login-box">
					<h2 class="welcome-title">欢迎登录</h2>
					<el-form :model="formData" class="login-form">
						<el-form-item>
							<el-input v-model="formData.username" placeholder="请输入账号" size="large" :prefix-icon="User" />
						</el-form-item>
						<el-form-item>
							<el-input
								v-model="formData.password"
								type="password"
								placeholder="请输入密码"
								size="large"
								:prefix-icon="Lock"
								show-password
							/>
						</el-form-item>
						<el-form-item>
							<el-button type="primary" size="large" class="login-btn" @click="submitForm">欢迎登录</el-button>
						</el-form-item>
						<el-form-item>
							<el-button type="default" size="large" class="qrcode-btn" @click="dialogVisible = true">
								手机端二维码
							</el-button>
						</el-form-item>
					</el-form>
					<router-link to="/sample" v-if="showTestLink" class="test-link">进入示例演示页面</router-link>
				</div>
			</div>
		</div>
	</div>
	<!-- 验证码组件 -->
	<Verify
		mode="pop"
		:captchaType="captchaType"
		:imgSize="{ width: '400px', height: '200px' }"
		ref="verify"
		@success="handleSuccess"
	></Verify>
	<!-- 二维码弹窗 -->
	<el-dialog v-model="dialogVisible" title="请用手机扫描" width="500px">
		<div class="qrcode-container">
			<div class="qrcode-item">
				<div class="qrcode-box">
					<img src="#" alt="老师端" class="qrcode-img" />
				</div>
				<div class="qrcode-label">老师端</div>
			</div>
			<div class="qrcode-item">
				<div class="qrcode-box">
					<img src="#" alt="家长端" class="qrcode-img" />
				</div>
				<div class="qrcode-label">家长端</div>
			</div>
		</div>
	</el-dialog>
</template>

<script setup lang="ts">
import Verify from "@/components/verifition/Verify.vue";
import { ref, reactive } from "vue";
import { login } from "@/apis/login/index";
import { ElMessage } from "element-plus";
import { useRouter } from "vue-router";
import { useTabStore } from "@/stores/tab";
import { User } from "@element-plus/icons-vue";
import { Lock } from "@element-plus/icons-vue";

// 是否显示示例演示界面连接
const showTestLink = ref(import.meta.env.DEV);

// 是否启用验证码
const enableVerify = ref(!import.meta.env.DEV);
//const enableVerify = ref(true);
// 获取router对象
const $router = useRouter();

// 二维码弹窗状态
const dialogVisible = ref(false);

// 定义登录数据对象
const formData = reactive({
	username: "admin",
	password: "123456",
});

/**
 * 执行登录
 * @param code 验证码字符串
 */
function doLogin(code: string) {
	// 发送登录请求
	login(
		{
			...formData,
			code: code,
			terminalType: "manager",
		},
		() => {
			// 重置标签页数据
			useTabStore().reset();
			// 跳转到首页
			$router.push("/home");
			// 登录成功提示
			ElMessage.success("登录成功，前往首页");
		},
		() => {
			ElMessage.error("账号或密码错误");
		},
	);
}

// 定义登录提交函数
function submitForm() {
	if (!formData.username || !formData.password) {
		ElMessage.warning("请输入账号和密码");
		return;
	}
	//账号格式校验
	if (!/^[a-zA-Z0-9_]{4,16}$/.test(formData.username)) {
		ElMessage.warning("账号格式错误，4-16位字母、数字或下划线");
		return;
	}

	// 添加密码长度校验
	if (formData.password.length < 6) {
		ElMessage.warning("密码长度不能少于 6 位");
		return;
	}

	if (!enableVerify.value) {
		doLogin("");
		return;
	}
	// 弹出验证码框
	useVerify("clickWord");
}

// 验证码组件引用
const verify = ref<InstanceType<typeof Verify> | null>(null);

// 验证码类型
const captchaType = ref("");

/**
 * 弹出验证码框
 * @param type 验证码类型 blockPuzzle滑块验证 clickWord点击文字验证
 */
function useVerify(type: string) {
	captchaType.value = type;
	if (verify.value) verify.value.show();
}

/**
 * 验证码验证通过执行登录二次验证逻辑
 * @param res 验证通过信息
 */
function handleSuccess(res: { captchaVerification: string }) {
	doLogin(res.captchaVerification);
}

/**
 * 生成雪花的随机样式
 */
function getSnowflakeStyle() {
	const left = Math.random() * 100; // 随机水平位置 0-100%
	const delay = Math.random() * 10; // 随机延迟 0-10 秒
	const duration = 8 + Math.random() * 7; // 随机下落时间 8-15 秒
	const size = 2 + Math.random() * 4; // 随机大小 2-6px
	const opacity = 0.3 + Math.random() * 0.5; // 随机透明度 0.3-0.8

	return {
		left: `${left}%`,
		animationDelay: `${delay}s`,
		animationDuration: `${duration}s`,
		width: `${size}px`,
		height: `${size}px`,
		opacity: opacity,
	};
}
</script>

<style scoped>
/* 雪花容器 */
.snowflakes {
	position: absolute;
	top: 0;
	left: 0;
	width: 100%;
	height: 100%;
	overflow: hidden;
	pointer-events: none;
	z-index: 1;
}

/* 单个雪花 */
.snowflake {
	position: absolute;
	top: -10px;
	background: rgba(255, 255, 255, 0.8);
	border-radius: 50%;
	animation: fall linear infinite;
	pointer-events: none;
}

/* 雪花下落动画 */
@keyframes fall {
	0% {
		transform: translateY(-10px) translateX(0);
		opacity: 0;
	}
	10% {
		opacity: 1;
	}
	90% {
		opacity: 1;
	}
	100% {
		transform: translateY(100vh) translateX(20px);
		opacity: 0;
	}
}

.login-container {
	width: 100%;
	height: 100vh;
	background: #0f80d9;
	display: flex;
	align-items: center;
	justify-content: center;
}

.login-wrapper {
	position: relative;
	z-index: 2;
	width: 72%;
	max-width: 960px;
	height: 64vh;
	max-height: 480px;
	background: #fff;
	border-radius: 16px;
	box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
	display: flex;
	overflow: hidden;
}

.left-section {
	flex: 1;
	background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
	display: flex;
	flex-direction: column;
	justify-content: center;
	align-items: center;
	padding: 40px;
	position: relative;
}

.logo-area {
	display: flex;
	align-items: center;
	justify-content: center;
	margin-bottom: 40px;
	position: relative;
	top: 20px;
}

.logo-img {
	width: 25px;
	height: 25px;
	object-fit: contain;
	margin-right: 10px;
}

.system-title {
	font-size: 25px;
	font-weight: 700;
	color: #333;
	margin: 0;
	line-height: 1;
}

.illustration-area {
	flex: 1;
	display: flex;
	align-items: center;
	justify-content: center;
}

.illustration-img {
	max-width: 100%;
	max-height: 85%;
	object-fit: contain;
	border-radius: 16px;
}

.right-section {
	width: 450px;
	display: flex;
	align-items: center;
	justify-content: center;
	padding: 40px;
}

.login-box {
	width: 100%;
}

.welcome-title {
	font-size: 28px;
	font-weight: 700;
	color: #333;
	text-align: center;
	margin-bottom: 40px;
}

.login-form {
	width: 100%;
}

.login-btn {
	width: 100%;
	margin-top: 10px;
}

.test-link {
	display: block;
	text-align: center;
	margin-top: 20px;
	color: #909399;
	text-decoration: none;
	font-size: 14px;
}

.test-link:hover {
	color: #409eff;
}

.qrcode-btn {
	width: 100%;
	margin-top: 10px;
}

.qrcode-container {
	display: flex;
	justify-content: space-around;
	padding: 20px 0;
}

.qrcode-item {
	text-align: center;
}

.qrcode-box {
	width: 180px;
	height: 180px;
	background: #0e81da;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 8px;
	margin-bottom: 10px;
}

.qrcode-img {
	width: 160px;
	height: 120px;
	object-fit: contain;
}

.qrcode-label {
	font-size: 16px;
	font-weight: 500;
	color: #333;
}
</style>
