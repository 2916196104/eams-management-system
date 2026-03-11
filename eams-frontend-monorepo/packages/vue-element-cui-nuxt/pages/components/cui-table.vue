<template>
  <div class="cui-table-demo">
    <h1>CuiTable 组件演示</h1>

    <!-- 基础表格 -->
    <section class="demo-section">
      <h2>基础表格</h2>
      <CuiTable :data="tableData" :columns="basicColumns" />
    </section>

    <!-- 带索引的表格 -->
    <section class="demo-section">
      <h2>带索引的表格</h2>
      <CuiTable :data="tableData" :columns="basicColumns" show-index />
    </section>

    <!-- 带选择的表格 -->
    <section class="demo-section">
      <h2>带选择的表格</h2>
      <CuiTable
        :data="tableData"
        :columns="basicColumns"
        show-selection
        @selection-change="handleSelectionChange"
      />
      <p v-if="selectedRows.length > 0">
        已选择 {{ selectedRows.length }} 行
      </p>
    </section>

    <!-- 可排序表格 -->
    <section class="demo-section">
      <h2>可排序表格</h2>
      <CuiTable
        :data="tableData"
        :columns="sortableColumns"
        @sort-change="handleSortChange"
      />
      <p v-if="sortInfo">
        排序字段: {{ sortInfo.prop }}, 排序方式: {{ sortInfo.order }}
      </p>
    </section>

    <!-- 自定义单元格表格 -->
    <section class="demo-section">
      <h2>自定义单元格表格</h2>
      <CuiTable :data="tableData" :columns="customColumns">
        <template #status="{ row }">
          <el-tag :type="row.status === 'active' ? 'success' : 'info'">
            {{ row.status === 'active' ? '活跃' : '非活跃' }}
          </el-tag>
        </template>
        <template #actions="{ row }">
          <el-button type="primary" size="small" @click="handleEdit(row)">
            编辑
          </el-button>
          <el-button type="danger" size="small" @click="handleDelete(row)">
            删除
          </el-button>
        </template>
      </CuiTable>
    </section>

    <!-- 加载状态表格 -->
    <section class="demo-section">
      <h2>加载状态表格</h2>
      <el-button @click="toggleLoading">切换加载状态</el-button>
      <CuiTable :data="tableData" :columns="basicColumns" :loading="loading" />
    </section>

    <!-- 带边框和斑马纹的表格 -->
    <section class="demo-section">
      <h2>带边框和斑马纹的表格</h2>
      <CuiTable
        :data="tableData"
        :columns="basicColumns"
        stripe
        border
      />
    </section>

    <!-- 固定高度的表格 -->
    <section class="demo-section">
      <h2>固定高度的表格</h2>
      <CuiTable
        :data="longTableData"
        :columns="basicColumns"
        height="300"
      />
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiTable } from '@eams/vue-element-cui';
import type { CuiTableColumn, SortChangeEvent } from '@eams/vue-element-cui';
import { ElButton, ElTag } from 'element-plus';

// 表格数据
const tableData = ref([
  { id: 1, name: 'Alice', age: 25, email: 'alice@example.com', status: 'active' },
  { id: 2, name: 'Bob', age: 30, email: 'bob@example.com', status: 'inactive' },
  { id: 3, name: 'Charlie', age: 35, email: 'charlie@example.com', status: 'active' },
  { id: 4, name: 'David', age: 28, email: 'david@example.com', status: 'active' },
]);

// 长表格数据（用于固定高度演示）
const longTableData = ref([
  ...tableData.value,
  { id: 5, name: 'Eve', age: 32, email: 'eve@example.com', status: 'inactive' },
  { id: 6, name: 'Frank', age: 27, email: 'frank@example.com', status: 'active' },
  { id: 7, name: 'Grace', age: 29, email: 'grace@example.com', status: 'active' },
  { id: 8, name: 'Henry', age: 31, email: 'henry@example.com', status: 'inactive' },
]);

// 基础列配置
const basicColumns: CuiTableColumn[] = [
  { prop: 'name', label: '姓名', width: 120 },
  { prop: 'age', label: '年龄', width: 80 },
  { prop: 'email', label: '邮箱' },
];

// 可排序列配置
const sortableColumns: CuiTableColumn[] = [
  { prop: 'name', label: '姓名', width: 120, sortable: true },
  { prop: 'age', label: '年龄', width: 80, sortable: true },
  { prop: 'email', label: '邮箱' },
];

// 自定义列配置
const customColumns: CuiTableColumn[] = [
  { prop: 'name', label: '姓名', width: 120 },
  { prop: 'age', label: '年龄', width: 80 },
  { prop: 'status', label: '状态', width: 100, slot: 'status' },
  { label: '操作', width: 180, slot: 'actions' },
];

// 选中的行
const selectedRows = ref<any[]>([]);

// 排序信息
const sortInfo = ref<SortChangeEvent | null>(null);

// 加载状态
const loading = ref(false);

// 处理选择变化
const handleSelectionChange = (selection: any[]) => {
  selectedRows.value = selection;
  console.log('选中的行:', selection);
};

// 处理排序变化
const handleSortChange = (event: SortChangeEvent) => {
  sortInfo.value = event;
  console.log('排序变化:', event);
};

// 切换加载状态
const toggleLoading = () => {
  loading.value = !loading.value;
};

// 编辑行
const handleEdit = (row: any) => {
  console.log('编辑:', row);
  alert(`编辑: ${row.name}`);
};

// 删除行
const handleDelete = (row: any) => {
  console.log('删除:', row);
  alert(`删除: ${row.name}`);
};
</script>

<style scoped>
.cui-table-demo {
  padding: 20px;
}

.demo-section {
  margin-bottom: 40px;
}

.demo-section h2 {
  margin-bottom: 16px;
  font-size: 18px;
  font-weight: 600;
}

.demo-section p {
  margin-top: 12px;
  color: #606266;
}
</style>
