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
        <div class="sub">133123</div>
      </div>
    </div>
  </el-card>
</template>
<script setup lang="ts">
import People from './people.svg'
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
  flex-direction: column; /* 垂直排列（上下） */
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
