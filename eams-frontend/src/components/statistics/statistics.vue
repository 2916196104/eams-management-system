<template>
  <el-card class="statistics">
    <div class="wrapper">
      <!-- 左侧图标 -->
      <div class="icon">
        <img :src="peopleIcon" class="svg" />
      </div>
      <!-- 右侧文字 -->
      <div class="text-container">
        <!-- 主文字 -->
        <div class="main">{{ targetText }}</div>
        <!-- 副文字 -->
        <div class="sub" ref="countRef">0</div>
      </div>
    </div>
  </el-card>
</template>
<style scoped>
.statistics {
  height: 108px;
  cursor: pointer;
}
.statistics :deep(.el-card__body) {
  padding: 0px;
}
.statistics .wrapper {
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 100%;
}
.statistics .icon {
  font-size: 48px;
  margin: 14px;
  padding: 16px;
  line-height: 1;
  /* 过渡动画：hover变色更丝滑，避免生硬切换 */
  transition: background-color 0.3s ease;
  border-radius: 8px;
}
.statistics:hover .icon {
  background-color: black;
}
.statistics .svg {
  width: 1em;
  height: 1em;
}
.statistics .text-container {
  display: flex;
  flex-direction: column;
  margin: 26px;
  margin-left: 0;
  line-height: 1; /* 重置文字默认行高 */
}
.statistics .text-container .main {
  color: rgba(0, 0, 0, 0.45);
  font-size: 16px;
  font-weight: 700;
  margin-bottom: 12px;
  line-height: 1;
}
.statistics .text-container .sub {
  color: #666;
  font-size: 20px;
  font-weight: 700;
  line-height: 1;
}
</style>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import peopleIcon from './people.svg'
import { CountUp } from 'countup.js'
const countRef = ref()
const targetText = ref('学员数') // 目标文本
const targetNumber = 12333 // 目标数字
onMounted(() => {
  // 提取目标数字为变量，避免硬编码
  if (countRef.value) {
    // 创建数字滚动实例
    const countUp = new CountUp(countRef.value, targetNumber, {
      startVal: 0, // 起始值
      duration: 2, // 持续时间（秒）
      separator: '', // 去掉千分位分隔符（根据需求调整）
      useEasing: true,
      decimalPlaces: 0, // 明确指定小数位数（整数设为0）
      useGrouping: false // 关闭分组（千分位），和 separator 配合使用
    })
    // 启动动画
    if (!countUp.error) {
      countUp.start()
    } else {
      console.error('数字滚动初始化失败:', countUp.error)
      // 降级显示目标数字，而非固定0
      countRef.value.textContent = targetNumber.toString()
    }
  }
})
</script>
