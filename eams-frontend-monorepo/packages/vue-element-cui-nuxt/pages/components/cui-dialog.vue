<template>
  <div class="demo-page">
    <h1>CuiDialog 组件演示</h1>

    <div class="demo-section">
      <h2>基础对话框</h2>
      <el-button @click="showBasicDialog = true">打开对话框</el-button>

      <cui-dialog
        v-model="showBasicDialog"
        title="基础对话框"
        @confirm="handleBasicConfirm"
        @cancel="handleBasicCancel"
      >
        <p>这是一个基础对话框示例。</p>
      </cui-dialog>
    </div>

    <div class="demo-section">
      <h2>加载状态</h2>
      <el-button @click="showLoadingDialog = true">打开加载对话框</el-button>

      <cui-dialog
        v-model="showLoadingDialog"
        title="加载状态对话框"
        :loading="isLoading"
        @confirm="handleLoadingConfirm"
      >
        <p>点击确认按钮查看加载状态。</p>
      </cui-dialog>
    </div>

    <div class="demo-section">
      <h2>自定义宽度</h2>
      <el-button @click="showCustomDialog = true">打开自定义宽度对话框</el-button>

      <cui-dialog
        v-model="showCustomDialog"
        title="自定义宽度对话框"
        width="30%"
        @confirm="handleCustomConfirm"
      >
        <p>这个对话框的宽度是 30%。</p>
      </cui-dialog>
    </div>

    <div class="demo-section">
      <h2>禁用确认按钮</h2>
      <el-button @click="showDisabledDialog = true">打开禁用按钮对话框</el-button>

      <cui-dialog
        v-model="showDisabledDialog"
        title="禁用按钮对话框"
        :confirm-disabled="true"
        @cancel="showDisabledDialog = false"
      >
        <p>确认按钮已禁用。</p>
      </cui-dialog>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElMessage } from 'element-plus';
import { CuiDialog } from '@packages/vue-element-cui';

const showBasicDialog = ref(false);
const showLoadingDialog = ref(false);
const showCustomDialog = ref(false);
const showDisabledDialog = ref(false);
const isLoading = ref(false);

const handleBasicConfirm = () => {
  ElMessage.success('确认按钮被点击');
  showBasicDialog.value = false;
};

const handleBasicCancel = () => {
  ElMessage.info('取消按钮被点击');
};

const handleLoadingConfirm = async () => {
  isLoading.value = true;
  await new Promise((resolve) => setTimeout(resolve, 2000));
  ElMessage.success('操作完成');
  isLoading.value = false;
  showLoadingDialog.value = false;
};

const handleCustomConfirm = () => {
  ElMessage.success('自定义宽度对话框确认');
  showCustomDialog.value = false;
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
