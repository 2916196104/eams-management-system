<template>
  <div class="demo-container">
    <h1>CuiCheckboxEnum 组件演示</h1>

    <section class="demo-section">
      <h2>基础用法</h2>
      <CuiCheckboxEnum
        v-model="basicValue"
        enum-code="TEST_ENUM"
      />
      <p>当前值: {{ basicValue }}</p>
    </section>

    <section class="demo-section">
      <h2>禁用状态</h2>
      <CuiCheckboxEnum
        v-model="disabledValue"
        enum-code="TEST_ENUM"
        disabled
      />
    </section>

    <section class="demo-section">
      <h2>预选多个值</h2>
      <CuiCheckboxEnum
        v-model="preselectedValue"
        enum-code="TEST_ENUM"
      />
      <p>当前值: {{ preselectedValue }}</p>
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiCheckboxEnum } from '@eams/vue-element-cui';

const basicValue = ref([]);
const disabledValue = ref(['1', '2']);
const preselectedValue = ref(['1', '3']);
</script>

<style scoped lang="scss">
.demo-container {
  padding: 20px;
  max-width: 800px;
  margin: 0 auto;

  h1 {
    margin-bottom: 30px;
    color: #333;
  }

  .demo-section {
    margin-bottom: 30px;
    padding: 20px;
    border: 1px solid #ddd;
    border-radius: 4px;

    h2 {
      margin-top: 0;
      margin-bottom: 15px;
      font-size: 16px;
      color: #666;
    }

    p {
      margin-top: 10px;
      color: #999;
      font-size: 14px;
    }
  }
}
</style>
