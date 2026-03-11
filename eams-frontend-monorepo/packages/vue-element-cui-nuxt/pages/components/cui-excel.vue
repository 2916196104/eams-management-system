<template>
  <div class="demo-page">
    <h1>CuiExcel 组件演示</h1>

    <!-- 基础导入 -->
    <div class="demo-section">
      <h2>基础 Excel 导入</h2>
      <el-button type="primary" @click="showBasicImport = true">打开导入对话框</el-button>

      <cui-excel
        v-model="showBasicImport"
        title="导入用户数据"
        upload-url="/api/upload/excel"
        @success="handleImportSuccess"
        @error="handleImportError"
      />
    </div>

    <!-- 带模板下载的导入 -->
    <div class="demo-section">
      <h2>带模板下载的 Excel 导入</h2>
      <el-button type="primary" @click="showTemplateImport = true">打开导入对话框（带模板）</el-button>

      <cui-excel
        v-model="showTemplateImport"
        title="导入学生数据"
        upload-url="/api/upload/students"
        template-url="/templates/students-template.xlsx"
        @success="handleImportSuccess"
        @error="handleImportError"
      />
    </div>

    <!-- 导入数据预览 -->
    <div v-if="importedData.length > 0" class="demo-section">
      <h2>导入数据预览</h2>
      <p class="demo-description">共导入 {{ importedData.length }} 条记录</p>

      <el-table :data="importedData" border stripe style="width: 100%">
        <el-table-column prop="id" label="ID" width="80" />
        <el-table-column prop="name" label="姓名" width="120" />
        <el-table-column prop="email" label="邮箱" width="200" />
        <el-table-column prop="phone" label="电话" width="150" />
        <el-table-column prop="department" label="部门" width="120" />
        <el-table-column prop="position" label="职位" width="120" />
        <el-table-column prop="status" label="状态" width="100">
          <template #default="{ row }">
            <el-tag :type="row.status === '在职' ? 'success' : 'info'">
              {{ row.status }}
            </el-tag>
          </template>
        </el-table-column>
      </el-table>

      <div class="demo-actions">
        <el-button @click="clearImportedData">清空数据</el-button>
      </div>
    </div>

    <!-- 事件处理示例 -->
    <div class="demo-section">
      <h2>导入事件处理示例</h2>
      <el-button type="primary" @click="showEventDemo = true">打开导入对话框（查看事件）</el-button>

      <cui-excel
        v-model="showEventDemo"
        title="导入数据（事件演示）"
        upload-url="/api/upload/demo"
        @success="handleEventSuccess"
        @error="handleEventError"
      />

      <div v-if="eventLogs.length > 0" class="event-logs">
        <h3>事件日志：</h3>
        <div v-for="(log, index) in eventLogs" :key="index" class="event-log-item">
          <el-tag :type="log.type">{{ log.event }}</el-tag>
          <span class="log-time">{{ log.time }}</span>
          <pre class="log-data">{{ log.data }}</pre>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElTable, ElTableColumn, ElTag, ElMessage } from 'element-plus';
import { CuiExcel } from '@eams/vue-element-cui';

// 对话框状态
const showBasicImport = ref(false);
const showTemplateImport = ref(false);
const showEventDemo = ref(false);

// 导入的数据
const importedData = ref<any[]>([]);

// 事件日志
const eventLogs = ref<any[]>([]);

// 示例数据
const sampleData = [
  { id: 1, name: '张三', email: 'zhangsan@example.com', phone: '13800138001', department: '技术部', position: '工程师', status: '在职' },
  { id: 2, name: '李四', email: 'lisi@example.com', phone: '13800138002', department: '市场部', position: '经理', status: '在职' },
  { id: 3, name: '王五', email: 'wangwu@example.com', phone: '13800138003', department: '人事部', position: '专员', status: '离职' },
  { id: 4, name: '赵六', email: 'zhaoliu@example.com', phone: '13800138004', department: '财务部', position: '会计', status: '在职' },
  { id: 5, name: '孙七', email: 'sunqi@example.com', phone: '13800138005', department: '技术部', position: '架构师', status: '在职' },
];

// 处理导入成功
const handleImportSuccess = (response: any, file: any, fileList: any) => {
  ElMessage.success('Excel 导入成功');
  // 模拟导入的数据（实际应该从 response 中获取）
  importedData.value = [...sampleData];
};

// 处理导入失败
const handleImportError = (error: any) => {
  ElMessage.error('Excel 导入失败，请检查文件格式');
  console.error('导入错误:', error);
};

// 清空导入的数据
const clearImportedData = () => {
  importedData.value = [];
  ElMessage.info('已清空导入数据');
};

// 事件演示：处理成功
const handleEventSuccess = (response: any, file: any, fileList: any) => {
  ElMessage.success('导入成功');
  eventLogs.value.unshift({
    event: 'success',
    type: 'success',
    time: new Date().toLocaleTimeString(),
    data: JSON.stringify({ response, fileName: file.name, fileCount: fileList.length }, null, 2),
  });
};

// 事件演示：处理失败
const handleEventError = (error: any) => {
  ElMessage.error('导入失败');
  eventLogs.value.unshift({
    event: 'error',
    type: 'danger',
    time: new Date().toLocaleTimeString(),
    data: JSON.stringify(error, null, 2),
  });
};
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

  .demo-description {
    margin-bottom: 15px;
    color: #666;
    font-size: 14px;
  }
}

.demo-actions {
  margin-top: 16px;
}

.event-logs {
  margin-top: 20px;
  padding: 15px;
  background: #f5f7fa;
  border-radius: 4px;

  h3 {
    margin-top: 0;
    margin-bottom: 10px;
    font-size: 14px;
  }
}

.event-log-item {
  margin-bottom: 10px;
  padding: 10px;
  background: #fff;
  border-radius: 4px;

  .log-time {
    margin-left: 10px;
    color: #909399;
    font-size: 12px;
  }

  .log-data {
    margin-top: 8px;
    padding: 8px;
    background: #f5f7fa;
    border-radius: 4px;
    font-size: 12px;
    overflow-x: auto;
  }
}
</style>
