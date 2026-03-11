<template>
  <div class="demo-page">
    <h1>CuiDetail 组件演示</h1>

    <!-- 基础详情展示 -->
    <section class="demo-section">
      <h2>基础详情展示</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
      />
    </section>

    <!-- 不同字段类型展示 -->
    <section class="demo-section">
      <h2>不同字段类型展示</h2>
      <cui-detail
        :fields="typeFields"
        :data="typeData"
      />
    </section>

    <!-- 自定义列数 -->
    <section class="demo-section">
      <h2>自定义列数（3列）</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        :columns="3"
      />
    </section>

    <!-- 单列布局 -->
    <section class="demo-section">
      <h2>单列布局</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        :columns="1"
      />
    </section>

    <!-- 自定义标签宽度 -->
    <section class="demo-section">
      <h2>自定义标签宽度（200px）</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        label-width="200px"
      />
    </section>

    <!-- 窄标签宽度 -->
    <section class="demo-section">
      <h2>窄标签宽度（80px）</h2>
      <cui-detail
        :fields="basicFields"
        :data="basicData"
        label-width="80px"
      />
    </section>

    <!-- 自定义渲染 -->
    <section class="demo-section">
      <h2>自定义渲染</h2>
      <cui-detail
        :fields="customFields"
        :data="customData"
      />
    </section>

    <!-- 复杂数据展示 -->
    <section class="demo-section">
      <h2>复杂数据展示</h2>
      <cui-detail
        :fields="complexFields"
        :data="complexData"
        :columns="1"
      />
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiDetail } from '@eams/vue-element-cui';
import type { CuiDetailField } from '@eams/vue-element-cui';

// 基础字段
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

// 不同字段类型
const typeFields: CuiDetailField[] = [
  { label: '文本字段', prop: 'text' },
  { label: '数字字段', prop: 'number' },
  { label: '布尔字段', prop: 'boolean', render: (row) => row.boolean ? '是' : '否' },
  { label: '日期字段', prop: 'date' },
  { label: '金额字段', prop: 'amount', render: (row) => `¥${row.amount.toFixed(2)}` },
  { label: '百分比字段', prop: 'percentage', render: (row) => `${row.percentage}%` },
];

const typeData = ref({
  text: '这是一段文本内容',
  number: 12345,
  boolean: true,
  date: '2024-03-11',
  amount: 9999.99,
  percentage: 85,
});

// 自定义渲染字段
const customFields: CuiDetailField[] = [
  { label: '姓名', prop: 'name' },
  {
    label: '状态',
    prop: 'status',
    render: (row) => (row.status === 1 ? '✓ 活跃' : '✗ 禁用'),
  },
  {
    label: '等级',
    prop: 'level',
    render: (row) => {
      const levels = ['普通', '白银', '黄金', '铂金', '钻石'];
      return levels[row.level] || '未知';
    },
  },
  {
    label: '创建时间',
    prop: 'createdAt',
    render: (row) => new Date(row.createdAt).toLocaleString('zh-CN'),
  },
];

const customData = ref({
  name: 'Jane Smith',
  status: 1,
  level: 3,
  createdAt: '2024-01-15T10:30:00',
});

// 复杂数据
const complexFields: CuiDetailField[] = [
  { label: '订单编号', prop: 'orderNo' },
  { label: '客户名称', prop: 'customerName' },
  { label: '联系电话', prop: 'phone' },
  {
    label: '订单状态',
    prop: 'status',
    render: (row) => {
      const statusMap: Record<number, string> = {
        0: '待支付',
        1: '已支付',
        2: '配送中',
        3: '已完成',
        4: '已取消',
      };
      return statusMap[row.status] || '未知';
    },
  },
  {
    label: '订单金额',
    prop: 'totalAmount',
    render: (row) => `¥${row.totalAmount.toFixed(2)}`,
  },
  {
    label: '优惠金额',
    prop: 'discountAmount',
    render: (row) => `¥${row.discountAmount.toFixed(2)}`,
  },
  {
    label: '实付金额',
    prop: 'paidAmount',
    render: (row) => `¥${row.paidAmount.toFixed(2)}`,
  },
  {
    label: '下单时间',
    prop: 'orderTime',
    render: (row) => new Date(row.orderTime).toLocaleString('zh-CN'),
  },
  {
    label: '支付时间',
    prop: 'payTime',
    render: (row) => row.payTime ? new Date(row.payTime).toLocaleString('zh-CN') : '-',
  },
  { label: '收货地址', prop: 'address' },
  { label: '备注', prop: 'remark' },
];

const complexData = ref({
  orderNo: 'ORD20240311001',
  customerName: '张三',
  phone: '13800138000',
  status: 2,
  totalAmount: 1299.00,
  discountAmount: 100.00,
  paidAmount: 1199.00,
  orderTime: '2024-03-11T09:30:00',
  payTime: '2024-03-11T09:35:00',
  address: '北京市朝阳区某某街道某某小区1号楼2单元301室',
  remark: '请在工作日配送，联系电话保持畅通',
});
</script>


<style scoped>
.demo-page {
  padding: 20px;
}

.demo-section {
  margin-bottom: 40px;
  padding: 20px;
  background: #f5f7fa;
  border-radius: 4px;
}

.demo-section h2 {
  margin-top: 0;
  margin-bottom: 16px;
  font-size: 18px;
  font-weight: 600;
}
</style>
