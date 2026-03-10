<template>
  <div class="demo-page">
    <h1>CuiDialogForm 组件演示</h1>

    <div class="demo-section">
      <h2>基础表单对话框</h2>
      <el-button @click="showBasicForm = true">打开表单对话框</el-button>

      <cui-dialog-form
        :visible="showBasicForm"
        title="用户信息表单"
        :fields="basicFormFields"
        :model-value="basicFormData"
        @update:visible="showBasicForm = $event"
        @update:model-value="basicFormData = $event"
        @submit="handleBasicSubmit"
        @cancel="handleBasicCancel"
      />
    </div>

    <div class="demo-section">
      <h2>带验证的表单对话框</h2>
      <el-button @click="showValidationForm = true">打开验证表单对话框</el-button>

      <cui-dialog-form
        :visible="showValidationForm"
        title="注册表单"
        :fields="validationFormFields"
        :model-value="validationFormData"
        @update:visible="showValidationForm = $event"
        @update:model-value="validationFormData = $event"
        @submit="handleValidationSubmit"
      />
    </div>

    <div class="demo-section">
      <h2>加载状态表单对话框</h2>
      <el-button @click="showLoadingForm = true">打开加载表单对话框</el-button>

      <cui-dialog-form
        :visible="showLoadingForm"
        title="提交表单"
        :fields="loadingFormFields"
        :model-value="loadingFormData"
        :loading="isSubmitting"
        @update:visible="showLoadingForm = $event"
        @update:model-value="loadingFormData = $event"
        @submit="handleLoadingSubmit"
      />
    </div>

    <div class="demo-section">
      <h2>自定义宽度和标签位置</h2>
      <el-button @click="showCustomForm = true">打开自定义表单对话框</el-button>

      <cui-dialog-form
        :visible="showCustomForm"
        title="自定义表单"
        width="70%"
        label-position="top"
        :fields="customFormFields"
        :model-value="customFormData"
        @update:visible="showCustomForm = $event"
        @update:model-value="customFormData = $event"
        @submit="handleCustomSubmit"
      />
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElMessage } from 'element-plus';
import { CuiDialogForm } from '@packages/vue-element-cui';
import type { CuiFormField } from '@packages/vue-element-cui';

const showBasicForm = ref(false);
const showValidationForm = ref(false);
const showLoadingForm = ref(false);
const showCustomForm = ref(false);
const isSubmitting = ref(false);

// 基础表单
const basicFormData = ref({ name: '', email: '' });
const basicFormFields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
  },
];

// 验证表单
const validationFormData = ref({ username: '', password: '', confirmPassword: '' });
const validationFormFields: CuiFormField[] = [
  {
    prop: 'username',
    label: '用户名',
    type: 'input',
    placeholder: '请输入用户名',
    required: true,
    rules: [{ required: true, message: '用户名不能为空' }],
  },
  {
    prop: 'password',
    label: '密码',
    type: 'input',
    placeholder: '请输入密码',
    required: true,
    rules: [{ required: true, message: '密码不能为空' }],
  },
  {
    prop: 'confirmPassword',
    label: '确认密码',
    type: 'input',
    placeholder: '请再次输入密码',
    required: true,
    rules: [{ required: true, message: '确认密码不能为空' }],
  },
];

// 加载状态表单
const loadingFormData = ref({ title: '', content: '' });
const loadingFormFields: CuiFormField[] = [
  {
    prop: 'title',
    label: '标题',
    type: 'input',
    placeholder: '请输入标题',
  },
  {
    prop: 'content',
    label: '内容',
    type: 'textarea',
    placeholder: '请输入内容',
  },
];

// 自定义表单
const customFormData = ref({ category: '', description: '', date: '' });
const customFormFields: CuiFormField[] = [
  {
    prop: 'category',
    label: '分类',
    type: 'select',
    options: [
      { label: '技术', value: 'tech' },
      { label: '生活', value: 'life' },
      { label: '其他', value: 'other' },
    ],
  },
  {
    prop: 'description',
    label: '描述',
    type: 'textarea',
    placeholder: '请输入描述',
  },
  {
    prop: 'date',
    label: '日期',
    type: 'date',
  },
];

const handleBasicSubmit = (data: any) => {
  ElMessage.success(`提交成功: ${JSON.stringify(data)}`);
};

const handleBasicCancel = () => {
  ElMessage.info('取消操作');
};

const handleValidationSubmit = (data: any) => {
  ElMessage.success('注册成功');
};

const handleLoadingSubmit = async (data: any) => {
  isSubmitting.value = true;
  await new Promise((resolve) => setTimeout(resolve, 2000));
  ElMessage.success('提交成功');
  isSubmitting.value = false;
  showLoadingForm.value = false;
};

const handleCustomSubmit = (data: any) => {
  ElMessage.success('自定义表单提交成功');
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

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElMessage } from 'element-plus';
import { CuiDialogForm } from '@packages/vue-element-cui';
import type { CuiFormField } from '@packages/vue-element-cui';

const showBasicForm = ref(false);
const showValidationForm = ref(false);
const showLoadingForm = ref(false);
const showCustomForm = ref(false);
const isSubmitting = ref(false);

// 基础表单
const basicFormData = ref({ name: '', email: '' });
const basicFormFields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
  },
];

// 验证表单
const validationFormData = ref({ username: '', password: '', confirmPassword: '' });
const validationFormFields: CuiFormField[] = [
  {
    prop: 'username',
    label: '用户名',
    type: 'input',
    placeholder: '请输入用户名',
    required: true,
    rules: [{ required: true, message: '用户名不能为空' }],
  },
  {
    prop: 'password',
    label: '密码',
    type: 'input',
    placeholder: '请输入密码',
    required: true,
    rules: [{ required: true, message: '密码不能为空' }],
  },
  {
    prop: 'confirmPassword',
    label: '确认密码',
    type: 'input',
    placeholder: '请再次输入密码',
    required: true,
    rules: [{ required: true, message: '确认密码不能为空' }],
  },
];

// 加载状态表单
const loadingFormData = ref({ title: '', content: '' });
const loadingFormFields: CuiFormField[] = [
  {
    prop: 'title',
    label: '标题',
    type: 'input',
    placeholder: '请输入标题',
  },
  {
    prop: 'content',
    label: '内容',
    type: 'textarea',
    placeholder: '请输入内容',
  },
];

// 自定义表单
const customFormData = ref({ category: '', description: '', date: '' });
const customFormFields: CuiFormField[] = [
  {
    prop: 'category',
    label: '分类',
    type: 'select',
    options: [
      { label: '技术', value: 'tech' },
      { label: '生活', value: 'life' },
      { label: '其他', value: 'other' },
    ],
  },
  {
    prop: 'description',
    label: '描述',
    type: 'textarea',
    placeholder: '请输入描述',
  },
  {
    prop: 'date',
    label: '日期',
    type: 'date',
  },
];

const handleBasicSubmit = (data: any) => {
  ElMessage.success(`提交成功: ${JSON.stringify(data)}`);
};

const handleBasicCancel = () => {
  ElMessage.info('取消操作');
};

const handleValidationSubmit = (data: any) => {
  ElMessage.success('注册成功');
};

const handleLoadingSubmit = async (data: any) => {
  isSubmitting.value = true;
  await new Promise((resolve) => setTimeout(resolve, 2000));
  ElMessage.success('提交成功');
  isSubmitting.value = false;
  showLoadingForm.value = false;
};

const handleCustomSubmit = (data: any) => {
  ElMessage.success('自定义表单提交成功');
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
