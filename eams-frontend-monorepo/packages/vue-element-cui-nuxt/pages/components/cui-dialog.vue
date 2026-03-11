<template>
  <div class="demo-page">
    <h1>CuiDialog 组件演示</h1>

    <!-- 基础对话框 -->
    <div class="demo-section">
      <h2>基础对话框</h2>
      <el-button type="primary" @click="showBasicDialog = true">打开对话框</el-button>

      <cui-dialog
        v-model="showBasicDialog"
        title="基础对话框"
        @confirm="handleBasicConfirm"
        @cancel="handleBasicCancel"
      >
        <p>这是一个基础对话框示例。</p>
        <p>点击确认或取消按钮来关闭对话框。</p>
      </cui-dialog>
    </div>

    <!-- 不同尺寸的对话框 -->
    <div class="demo-section">
      <h2>不同尺寸的对话框</h2>
      <div class="demo-actions">
        <el-button @click="openSizeDialog('30%')">小尺寸 (30%)</el-button>
        <el-button @click="openSizeDialog('50%')">中等尺寸 (50%)</el-button>
        <el-button @click="openSizeDialog('70%')">大尺寸 (70%)</el-button>
        <el-button @click="openSizeDialog('800px')">固定宽度 (800px)</el-button>
      </div>

      <cui-dialog
        v-model="showSizeDialog"
        :title="`对话框 - 宽度: ${currentWidth}`"
        :width="currentWidth"
        @confirm="showSizeDialog = false"
      >
        <p>当前对话框宽度为: {{ currentWidth }}</p>
        <p>您可以根据需要设置不同的宽度。</p>
      </cui-dialog>
    </div>

    <!-- 自定义内容和插槽 -->
    <div class="demo-section">
      <h2>自定义内容和插槽</h2>
      <el-button type="primary" @click="showCustomDialog = true">打开自定义对话框</el-button>

      <cui-dialog
        v-model="showCustomDialog"
        title="自定义内容对话框"
        width="600px"
        @confirm="handleCustomConfirm"
      >
        <div class="custom-content">
          <el-form :model="customForm" label-width="80px">
            <el-form-item label="用户名">
              <el-input v-model="customForm.username" placeholder="请输入用户名" />
            </el-form-item>
            <el-form-item label="邮箱">
              <el-input v-model="customForm.email" placeholder="请输入邮箱" />
            </el-form-item>
            <el-form-item label="角色">
              <el-select v-model="customForm.role" placeholder="请选择角色">
                <el-option label="管理员" value="admin" />
                <el-option label="普通用户" value="user" />
                <el-option label="访客" value="guest" />
              </el-select>
            </el-form-item>
          </el-form>
        </div>
        <template #footer-left>
          <el-button type="info" @click="resetCustomForm">重置</el-button>
        </template>
      </cui-dialog>
    </div>

    <!-- 确认/取消操作 -->
    <div class="demo-section">
      <h2>确认/取消操作</h2>
      <el-button type="danger" @click="showDeleteDialog = true">删除操作</el-button>

      <cui-dialog
        v-model="showDeleteDialog"
        title="确认删除"
        width="400px"
        confirm-text="删除"
        cancel-text="取消"
        @confirm="handleDelete"
        @cancel="handleDeleteCancel"
      >
        <div class="delete-content">
          <el-icon :size="48" color="#f56c6c" style="margin-bottom: 16px">
            <WarningFilled />
          </el-icon>
          <p>确定要删除这条记录吗？</p>
          <p style="color: #909399; font-size: 14px">此操作不可撤销，请谨慎操作。</p>
        </div>
      </cui-dialog>
    </div>

    <!-- 加载状态 -->
    <div class="demo-section">
      <h2>加载状态</h2>
      <el-button type="primary" @click="showLoadingDialog = true">打开加载对话框</el-button>

      <cui-dialog
        v-model="showLoadingDialog"
        title="提交数据"
        :loading="isLoading"
        @confirm="handleLoadingConfirm"
      >
        <p>点击确认按钮将模拟一个异步操作。</p>
        <p>按钮将显示加载状态，3秒后完成。</p>
      </cui-dialog>
    </div>

    <!-- 禁用确认按钮 -->
    <div class="demo-section">
      <h2>禁用确认按钮</h2>
      <el-button type="primary" @click="showDisabledDialog = true">打开对话框</el-button>

      <cui-dialog
        v-model="showDisabledDialog"
        title="同意协议"
        :confirm-disabled="!agreed"
        @confirm="handleAgree"
      >
        <div class="agreement-content">
          <p>请阅读并同意以下协议：</p>
          <div class="agreement-text">
            <p>1. 用户协议条款一</p>
            <p>2. 用户协议条款二</p>
            <p>3. 用户协议条款三</p>
          </div>
          <el-checkbox v-model="agreed" style="margin-top: 16px">
            我已阅读并同意以上协议
          </el-checkbox>
        </div>
      </cui-dialog>
    </div>

    <!-- 无底部按钮 -->
    <div class="demo-section">
      <h2>无底部按钮</h2>
      <el-button @click="showNoFooterDialog = true">打开无底部对话框</el-button>

      <cui-dialog
        v-model="showNoFooterDialog"
        title="信息提示"
        :show-footer="false"
        width="400px"
      >
        <div class="info-content">
          <p>这是一个没有底部按钮的对话框。</p>
          <p>您可以点击右上角的关闭按钮来关闭它。</p>
          <el-button type="primary" style="margin-top: 16px" @click="showNoFooterDialog = false">
            知道了
          </el-button>
        </div>
      </cui-dialog>
    </div>

    <!-- 自定义按钮文本 -->
    <div class="demo-section">
      <h2>自定义按钮文本</h2>
      <el-button type="primary" @click="showCustomButtonDialog = true">打开对话框</el-button>

      <cui-dialog
        v-model="showCustomButtonDialog"
        title="保存更改"
        confirm-text="保存"
        cancel-text="放弃"
        @confirm="handleSave"
      >
        <p>您有未保存的更改。</p>
        <p>是否要保存这些更改？</p>
      </cui-dialog>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElForm, ElFormItem, ElInput, ElSelect, ElOption, ElCheckbox, ElIcon, ElMessage } from 'element-plus';
import { WarningFilled } from '@element-plus/icons-vue';
import { CuiDialog } from '@eams/vue-element-cui';

// 基础对话框
const showBasicDialog = ref(false);

const handleBasicConfirm = () => {
  ElMessage.success('确认操作');
  showBasicDialog.value = false;
};

const handleBasicCancel = () => {
  ElMessage.info('取消操作');
};

// 不同尺寸的对话框
const showSizeDialog = ref(false);
const currentWidth = ref('50%');

const openSizeDialog = (width: string) => {
  currentWidth.value = width;
  showSizeDialog.value = true;
};

// 自定义内容和插槽
const showCustomDialog = ref(false);
const customForm = ref({
  username: '',
  email: '',
  role: '',
});

const handleCustomConfirm = () => {
  console.log('提交表单:', customForm.value);
  ElMessage.success('表单提交成功');
  showCustomDialog.value = false;
};

const resetCustomForm = () => {
  customForm.value = {
    username: '',
    email: '',
    role: '',
  };
  ElMessage.info('表单已重置');
};

// 确认/取消操作
const showDeleteDialog = ref(false);

const handleDelete = () => {
  ElMessage.success('删除成功');
  showDeleteDialog.value = false;
};

const handleDeleteCancel = () => {
  ElMessage.info('已取消删除');
};

// 加载状态
const showLoadingDialog = ref(false);
const isLoading = ref(false);

const handleLoadingConfirm = () => {
  isLoading.value = true;
  setTimeout(() => {
    isLoading.value = false;
    showLoadingDialog.value = false;
    ElMessage.success('操作完成');
  }, 3000);
};

// 禁用确认按钮
const showDisabledDialog = ref(false);
const agreed = ref(false);

const handleAgree = () => {
  ElMessage.success('感谢您的同意');
  showDisabledDialog.value = false;
  agreed.value = false;
};

// 无底部按钮
const showNoFooterDialog = ref(false);

// 自定义按钮文本
const showCustomButtonDialog = ref(false);

const handleSave = () => {
  ElMessage.success('更改已保存');
  showCustomButtonDialog.value = false;
};
</script>

<style scoped lang="scss">
.demo-page {
  padding: 20px;
}

.demo-section {
  margin-bottom: 40px;
  padding: 20px;
  background: #f5f7fa;
  border-radius: 4px;

  h2 {
    margin-top: 0;
    margin-bottom: 16px;
    font-size: 18px;
    font-weight: 600;
  }
}

.demo-actions {
  display: flex;
  gap: 12px;
  flex-wrap: wrap;
}

.custom-content {
  padding: 12px 0;
}

.delete-content {
  display: flex;
  flex-direction: column;
  align-items: center;
  text-align: center;
  padding: 20px 0;

  p {
    margin: 8px 0;
  }
}

.agreement-content {
  padding: 12px 0;
}

.agreement-text {
  padding: 16px;
  background: #f5f7fa;
  border-radius: 4px;
  margin-top: 12px;

  p {
    margin: 8px 0;
    color: #606266;
  }
}

.info-content {
  text-align: center;
  padding: 20px 0;

  p {
    margin: 8px 0;
  }
}
</style>
