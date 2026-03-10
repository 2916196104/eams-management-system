<template>
  <div class="demo-container">
    <h1>CuiAutocomplete 组件演示</h1>

    <section class="demo-section">
      <h2>基础用法</h2>
      <CuiAutocomplete
        v-model="basicValue"
        :suggestions="suggestions"
        placeholder="输入以搜索"
      />
      <p>当前值: {{ basicValue }}</p>
    </section>

    <section class="demo-section">
      <h2>禁用状态</h2>
      <CuiAutocomplete
        v-model="disabledValue"
        :suggestions="suggestions"
        disabled
      />
    </section>

    <section class="demo-section">
      <h2>不可清空</h2>
      <CuiAutocomplete
        v-model="notClearableValue"
        :suggestions="suggestions"
        :clearable="false"
      />
    </section>

    <section class="demo-section">
      <h2>选择事件</h2>
      <CuiAutocomplete
        v-model="selectValue"
        :suggestions="suggestions"
        placeholder="选择一个建议"
        @select="handleSelect"
      />
      <p>当前值: {{ selectValue }}</p>
      <p v-if="selectedItem">选择的项: {{ selectedItem.label }}</p>
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiAutocomplete } from '@ruan-cat/vue-element-cui';
import type { CuiAutocompleteSuggestion } from '@ruan-cat/vue-element-cui';

const basicValue = ref('');
const disabledValue = ref('apple');
const notClearableValue = ref('');
const selectValue = ref('');
const selectedItem = ref<CuiAutocompleteSuggestion | null>(null);

const suggestions: CuiAutocompleteSuggestion[] = [
  { value: 'apple', label: 'Apple' },
  { value: 'banana', label: 'Banana' },
  { value: 'cherry', label: 'Cherry' },
  { value: 'date', label: 'Date' },
  { value: 'elderberry', label: 'Elderberry' },
];

const handleSelect = (item: any) => {
  selectedItem.value = item;
};
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
