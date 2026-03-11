<template>
  <div class="demo-container">
    <h1>CuiSelectDict 组件演示</h1>

    <section class="demo-section">
      <h2>基础用法</h2>
      <CuiSelectDict
        v-model="basicValue"
        dict-code="TEST_DICT"
        placeholder="请选择字典值"
      />
      <p>当前值: {{ basicValue }}</p>
    </section>

    <section class="demo-section">
      <h2>禁用状态</h2>
      <CuiSelectDict
        v-model="disabledValue"
        dict-code="TEST_DICT"
        disabled
      />
    </section>

    <section class="demo-section">
      <h2>不可清空</h2>
      <CuiSelectDict
        v-model="notClearableValue"
        dict-code="TEST_DICT"
        :clearable="false"
      />
    </section>

    <section class="demo-section">
      <h2>不可过滤</h2>
      <CuiSelectDict
        v-model="notFilterableValue"
        dict-code="TEST_DICT"
        :filterable="false"
      />
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSelectDict } from '@eams/vue-element-cui';

const basicValue = ref('');
const disabledValue = ref('dict1');
const notClearableValue = ref('dict1');
const notFilterableValue = ref('');
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
