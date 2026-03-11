<template>
  <div class="demo-container">
    <h1>CuiSelect 组件演示</h1>

    <section class="demo-section">
      <h2>基础用法</h2>
      <CuiSelect
        v-model="basicValue"
        :options="basicOptions"
        placeholder="请选择一个选项"
      />
      <p>当前值: {{ basicValue }}</p>
    </section>

    <section class="demo-section">
      <h2>禁用状态</h2>
      <CuiSelect
        v-model="disabledValue"
        :options="basicOptions"
        disabled
      />
    </section>

    <section class="demo-section">
      <h2>多选模式</h2>
      <CuiSelect
        v-model="multipleValue"
        :options="basicOptions"
        multiple
        placeholder="请选择多个选项"
      />
      <p>当前值: {{ multipleValue }}</p>
    </section>

    <section class="demo-section">
      <h2>不可清空</h2>
      <CuiSelect
        v-model="notClearableValue"
        :options="basicOptions"
        :clearable="false"
      />
    </section>

    <section class="demo-section">
      <h2>不可过滤</h2>
      <CuiSelect
        v-model="notFilterableValue"
        :options="basicOptions"
        :filterable="false"
      />
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSelect } from '@ruan-cat/vue-element-cui';
import type { CuiSelectOption } from '@ruan-cat/vue-element-cui';

const basicValue = ref('');
const disabledValue = ref('opt1');
const multipleValue = ref([]);
const notClearableValue = ref('opt1');
const notFilterableValue = ref('');

const basicOptions: CuiSelectOption[] = [
  { label: '选项 1', value: 'opt1' },
  { label: '选项 2', value: 'opt2' },
  { label: '选项 3', value: 'opt3' },
  { label: '选项 4', value: 'opt4' },
];
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
