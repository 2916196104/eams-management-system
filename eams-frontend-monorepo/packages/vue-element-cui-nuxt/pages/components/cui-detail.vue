<template>
  <div class="demo-page">
    <h1>CuiDetail 组件演示</h1>

    <div class="demo-section">
      <h2>基础详情展示</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
      />
    </div>

    <div class="demo-section">
      <h2>自定义列数</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        :columns="3"
      />
    </div>

    <div class="demo-section">
      <h2>自定义标签宽度</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        label-width="200px"
      />
    </div>

    <div class="demo-section">
      <h2>自定义渲染</h2>
      <cui-detail
        :fields="customFields"
        :data="customData"
      />
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiDetail } from '@packages/vue-element-cui';
import type { CuiDetailField } from '@packages/vue-element-cui';

const basicFields: CuiDetailField[] = [
  { label: '姓名', prop: 'name' },
  { label: '邮箱', prop: 'email' },
  { label: '电话', prop: 'phone' },
  { label: '地址', prop: 'address' },
];

const basicData = ref({
  name: 'John Doe',
  email: 'john@example.com',
  phone: '13800138000',
  address: '北京市朝阳区',
});

const customFields: CuiDetailField[] = [
  { label: '姓名', prop: 'name' },
  {
    label: '状态',
    prop: 'status',
    render: (row) => (row.status === 1 ? '✓ 活跃' : '✗ 禁用'),
  },
  {
    label: '创建时间',
    prop: 'createdAt',
    render: (row) => new Date(row.createdAt).toLocaleDateString(),
  },
];

const customData = ref({
  name: 'Jane Smith',
  status: 1,
  createdAt: '2024-01-15',
});
</script>

<style scoped lang="scss">
.demo-page {
  padding: 20px;
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
  }
}
</style>
