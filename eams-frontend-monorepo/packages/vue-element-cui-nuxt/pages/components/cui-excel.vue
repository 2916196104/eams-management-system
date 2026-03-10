<template>
  <div class="demo-page">
    <h1>CuiExcel 组件演示</h1>

    <div class="demo-section">
      <h2>基础 Excel 导入</h2>
      <el-button @click="showExcelDialog = true">打开 Excel 导入</el-button>

      <cui-excel
        v-model="showExcelDialog"
        title="导入 Excel 数据"
        upload-url="http://example.com/upload"
        @success="handleExcelSuccess"
      />
    </div>

    <div class="demo-section">
      <h2>带模板下载的 Excel 导入</h2>
      <el-button @click="showExcelWithTemplate = true">打开 Excel 导入（带模板）</el-button>

      <cui-excel
        v-model="showExcelWithTemplate"
        title="导入学生数据"
        upload-url="http://example.com/upload"
        template-url="http://example.com/template.xlsx"
        @success="handleExcelSuccess"
      />
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElMessage } from 'element-plus';
import { CuiExcel } from '@packages/vue-element-cui';

const showExcelDialog = ref(false);
const showExcelWithTemplate = ref(false);

const handleExcelSuccess = (response: any, file: any, fileList: any) => {
  ElMessage.success('Excel 导入成功');
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
}
</style>
