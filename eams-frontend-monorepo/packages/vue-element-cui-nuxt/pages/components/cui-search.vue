<template>
  <div class="cui-search-demo">
    <h1>CuiSearch 组件演示</h1>

    <!-- 基础搜索 -->
    <section class="demo-section">
      <h2>基础搜索</h2>
      <CuiSearch
        v-model="basicSearchForm"
        :fields="basicFields"
        @search="handleBasicSearch"
        @reset="handleBasicReset"
      />
      <div v-if="basicSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(basicSearchResult, null, 2) }}</pre>
      </div>
    </section>

    <!-- 带选择器的搜索 -->
    <section class="demo-section">
      <h2>带选择器的搜索</h2>
      <CuiSearch
        v-model="selectSearchForm"
        :fields="selectFields"
        @search="handleSelectSearch"
        @reset="handleSelectReset"
      />
      <div v-if="selectSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(selectSearchResult, null, 2) }}</pre>
      </div>
    </section>

    <!-- 带日期的搜索 -->
    <section class="demo-section">
      <h2>带日期的搜索</h2>
      <CuiSearch
        v-model="dateSearchForm"
        :fields="dateFields"
        @search="handleDateSearch"
        @reset="handleDateReset"
      />
      <div v-if="dateSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(dateSearchResult, null, 2) }}</pre>
      </div>
    </section>

    <!-- 高级搜索（可折叠） -->
    <section class="demo-section">
      <h2>高级搜索（可折叠）</h2>
      <CuiSearch
        v-model="advancedSearchForm"
        :fields="advancedFields"
        :collapsible="true"
        @search="handleAdvancedSearch"
        @reset="handleAdvancedReset"
      />
      <div v-if="advancedSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(advancedSearchResult, null, 2) }}</pre>
      </div>
    </section>

    <!-- 综合示例 -->
    <section class="demo-section">
      <h2>综合示例</h2>
      <CuiSearch
        v-model="comprehensiveSearchForm"
        :fields="comprehensiveFields"
        :collapsible="true"
        @search="handleComprehensiveSearch"
        @reset="handleComprehensiveReset"
      />
      <div v-if="comprehensiveSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(comprehensiveSearchResult, null, 2) }}</pre>
      </div>
    </section>

    <!-- 非内联布局 -->
    <section class="demo-section">
      <h2>非内联布局</h2>
      <CuiSearch
        v-model="blockSearchForm"
        :fields="basicFields"
        :inline="false"
        @search="handleBlockSearch"
        @reset="handleBlockReset"
      />
      <div v-if="blockSearchResult" class="search-result">
        <h3>搜索结果：</h3>
        <pre>{{ JSON.stringify(blockSearchResult, null, 2) }}</pre>
      </div>
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiSearch } from '@eams/vue-element-cui';
import type { CuiSearchField } from '@eams/vue-element-cui';

// 基础搜索
const basicSearchForm = ref({});
const basicSearchResult = ref<any>(null);
const basicFields: CuiSearchField[] = [
  { prop: 'name', label: '姓名', type: 'input', placeholder: '请输入姓名' },
  { prop: 'email', label: '邮箱', type: 'input', placeholder: '请输入邮箱' },
];

const handleBasicSearch = (values: any) => {
  basicSearchResult.value = values;
  console.log('基础搜索:', values);
};

const handleBasicReset = (values: any) => {
  basicSearchResult.value = null;
  console.log('基础重置:', values);
};

// 带选择器的搜索
const selectSearchForm = ref({});
const selectSearchResult = ref<any>(null);
const selectFields: CuiSearchField[] = [
  { prop: 'name', label: '姓名', type: 'input', placeholder: '请输入姓名' },
  {
    prop: 'status',
    label: '状态',
    type: 'select',
    placeholder: '请选择状态',
    options: [
      { label: '启用', value: 1 },
      { label: '禁用', value: 0 },
    ],
  },
  {
    prop: 'role',
    label: '角色',
    type: 'select',
    placeholder: '请选择角色',
    options: [
      { label: '管理员', value: 'admin' },
      { label: '用户', value: 'user' },
      { label: '访客', value: 'guest' },
    ],
  },
];

const handleSelectSearch = (values: any) => {
  selectSearchResult.value = values;
  console.log('选择器搜索:', values);
};

const handleSelectReset = (values: any) => {
  selectSearchResult.value = null;
  console.log('选择器重置:', values);
};

// 带日期的搜索
const dateSearchForm = ref({});
const dateSearchResult = ref<any>(null);
const dateFields: CuiSearchField[] = [
  { prop: 'name', label: '姓名', type: 'input', placeholder: '请输入姓名' },
  { prop: 'createDate', label: '创建日期', type: 'date', placeholder: '请选择日期' },
  { prop: 'dateRange', label: '日期范围', type: 'daterange' },
];

const handleDateSearch = (values: any) => {
  dateSearchResult.value = values;
  console.log('日期搜索:', values);
};

const handleDateReset = (values: any) => {
  dateSearchResult.value = null;
  console.log('日期重置:', values);
};

// 高级搜索
const advancedSearchForm = ref({});
const advancedSearchResult = ref<any>(null);
const advancedFields: CuiSearchField[] = [
  { prop: 'name', label: '姓名', type: 'input', placeholder: '请输入姓名' },
  { prop: 'email', label: '邮箱', type: 'input', placeholder: '请输入邮箱', advanced: true },
  { prop: 'phone', label: '电话', type: 'input', placeholder: '请输入电话', advanced: true },
  {
    prop: 'department',
    label: '部门',
    type: 'select',
    placeholder: '请选择部门',
    advanced: true,
    options: [
      { label: '技术部', value: 'tech' },
      { label: '市场部', value: 'marketing' },
      { label: '销售部', value: 'sales' },
    ],
  },
];

const handleAdvancedSearch = (values: any) => {
  advancedSearchResult.value = values;
  console.log('高级搜索:', values);
};

const handleAdvancedReset = (values: any) => {
  advancedSearchResult.value = null;
  console.log('高级重置:', values);
};

// 综合示例
const comprehensiveSearchForm = ref({});
const comprehensiveSearchResult = ref<any>(null);
const comprehensiveFields: CuiSearchField[] = [
  { prop: 'keyword', label: '关键词', type: 'input', placeholder: '请输入关键词' },
  {
    prop: 'category',
    label: '分类',
    type: 'select',
    placeholder: '请选择分类',
    options: [
      { label: '文章', value: 'article' },
      { label: '视频', value: 'video' },
      { label: '图片', value: 'image' },
    ],
  },
  { prop: 'createDate', label: '创建日期', type: 'date' },
  { prop: 'author', label: '作者', type: 'input', placeholder: '请输入作者', advanced: true },
  {
    prop: 'status',
    label: '状态',
    type: 'select',
    placeholder: '请选择状态',
    advanced: true,
    options: [
      { label: '已发布', value: 'published' },
      { label: '草稿', value: 'draft' },
      { label: '已删除', value: 'deleted' },
    ],
  },
  { prop: 'dateRange', label: '更新时间', type: 'daterange', advanced: true },
];

const handleComprehensiveSearch = (values: any) => {
  comprehensiveSearchResult.value = values;
  console.log('综合搜索:', values);
};

const handleComprehensiveReset = (values: any) => {
  comprehensiveSearchResult.value = null;
  console.log('综合重置:', values);
};

// 非内联布局
const blockSearchForm = ref({});
const blockSearchResult = ref<any>(null);

const handleBlockSearch = (values: any) => {
  blockSearchResult.value = values;
  console.log('非内联搜索:', values);
};

const handleBlockReset = (values: any) => {
  blockSearchResult.value = null;
  console.log('非内联重置:', values);
};
</script>

<style scoped>
.cui-search-demo {
  padding: 20px;
}

.demo-section {
  margin-bottom: 40px;
  padding: 20px;
  background: #f5f7fa;
  border-radius: 4px;
}

.demo-section h2 {
  margin-bottom: 16px;
  font-size: 18px;
  font-weight: 600;
}

.search-result {
  margin-top: 20px;
  padding: 16px;
  background: white;
  border-radius: 4px;
  border: 1px solid #dcdfe6;
}

.search-result h3 {
  margin-bottom: 12px;
  font-size: 14px;
  font-weight: 600;
  color: #303133;
}

.search-result pre {
  margin: 0;
  padding: 12px;
  background: #f5f7fa;
  border-radius: 4px;
  font-size: 12px;
  color: #606266;
  overflow-x: auto;
}
</style>
