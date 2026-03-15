<template>
  <el-card class="statistics">
    <div class="wrapper">
      <!-- 左侧图标 -->
      <el-icon class="icon">
        <img :src="People" class="svg" />
      </el-icon>
      <!-- 右侧文字 -->
      <div class="text-container">
        <!-- 主文字 -->
        <div class="main">学员数</div>
        <!-- 副文字 -->
        <div class="sub" ref="countRef">0</div>
      </div>
    </div>
  </el-card>
</template>
<script setup lang="ts">
import { ref, onMounted } from 'vue'
import People from './people.svg'
import { CountUp } from 'countup.js'
const countRef = ref()
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
<style scoped>
.statistics {
  height: 108px;
  cursor: pointer;
}
.statistics .wrapper {
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 100%;
}
.statistics .icon {
  padding: 16px;
}
.statistics .svg {
  width: 1em;
  height: 1em;
  font-size: 48px;
}
.statistics .text-container {
  display: flex;
  flex-direction: column;
  gap: 12px;
}
.statistics .text-container .main {
  color: rgba(0, 0, 0, 0.45);
  font-size: 16px;
  font-weight: 700;
}
.statistics .text-container .sub {
  font-size: 20px;
  font-weight: 700;
}
</style>
