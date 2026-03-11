<!-- 登录页面 -->
<template>
  <div class="login-container">
    <div class="login-wrapper">
      <div class="left-section">
        <div class="logo-area">
          <img src="/logo.jpg" alt="教务系统Logo" class="logo-img" />
          <h1 class="system-title">零一教务系统</h1>
        </div>
        <div class="illustration-area">
          <img src="#" alt="左侧插图" class="illustration-img" />
        </div>
      </div>
      <div class="right-section">
        <div class="login-box">
          <h2 class="welcome-title">欢迎登录</h2>
          <el-form :model="formData" class="login-form">
            <el-form-item>
              <el-input
                v-model="formData.username"
                placeholder="请输入账号"
                size="large"
                :prefix-icon="User"
              />
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
              <el-button type="primary" size="large" class="login-btn" @click="submitForm">
                欢迎登录
              </el-button>
            </el-form-item>
            <el-form-item>
              <el-button
                type="default"
                size="large"
                class="qrcode-btn"
                @click="dialogVisible = true"
              >
                手机端二维码
              </el-button>
            </el-form-item>
          </el-form>
          <router-link to="/sample" v-if="showTestLink" class="test-link"
            >进入示例演示页面</router-link
          >
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
import Verify from '@/components/verifition/Verify.vue'
import { ref, reactive } from 'vue'
import { login } from '@/apis/login/index'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import { useTabStore } from '@/stores/tab'
import { User } from '@element-plus/icons-vue'
import { Lock } from '@element-plus/icons-vue'

// 是否显示示例演示界面连接
const showTestLink = ref(import.meta.env.DEV)

// 是否启用验证码
const enableVerify = ref(!import.meta.env.DEV)

// 获取router对象
const $router = useRouter()

// 二维码弹窗状态
const dialogVisible = ref(false)

// 定义登录数据对象
const formData = reactive({
  username: '',
  password: ''
})

/**
 * 执行登录
 * @param code 验证码字符串
 */
function doLogin(code: string) {
  // 发送登录请求
  login(
    {
      ...formData,
      code: code
    },
    () => {
      // 重置标签页数据
      useTabStore().reset()
      // 跳转到首页
      $router.push('/home')
      // 登录成功提示
      ElMessage.success('登录成功，前往首页')
    },
    () => {
      ElMessage.error('账号或密码错误')
    }
  )
}

// 定义登录提交函数
function submitForm() {
  if (!formData.username || !formData.password) {
    ElMessage.warning('请输入账号和密码')
    return
  }

  if (!enableVerify.value) {
    doLogin('')
    return
  }
  // 弹出验证码框
  useVerify('clickWord')
}

// 验证码组件引用
const verify = ref<InstanceType<typeof Verify> | null>(null)

// 验证码类型
const captchaType = ref('')

/**
 * 弹出验证码框
 * @param type 验证码类型 blockPuzzle滑块验证 clickWord点击文字验证
 */
function useVerify(type: string) {
  captchaType.value = type
  if (verify.value) verify.value.show()
}

/**
 * 验证码验证通过执行登录二次验证逻辑
 * @param res 验证通过信息
 */
function handleSuccess(res: { captchaVerification: string }) {
  doLogin(res.captchaVerification)
}
</script>

<style scoped>
.login-container {
  width: 100%;
  height: 100vh;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  display: flex;
  align-items: center;
  justify-content: center;
}

.login-wrapper {
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
  max-height: 100%;
  object-fit: contain;
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
  background: #667eea;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 8px;
  margin-bottom: 10px;
}

.qrcode-img {
  width: 160px;
  height: 160px;
  object-fit: contain;
}

.qrcode-label {
  font-size: 16px;
  font-weight: 500;
  color: #333;
}
</style>
