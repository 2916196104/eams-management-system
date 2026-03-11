<template>
  <div class="cui-form-demo">
    <h1>CuiForm 组件演示</h1>

    <!-- 基础表单 -->
    <section class="demo-section">
      <h2>基础表单</h2>
      <CuiForm
        ref="basicFormRef"
        v-model="basicFormData"
        :fields="basicFields"
      />
      <div class="demo-actions">
        <el-button type="primary" @click="handleBasicSubmit">提交</el-button>
        <el-button @click="handleBasicReset">重置</el-button>
      </div>
      <div v-if="basicFormResult" class="demo-result">
        <p>表单数据：</p>
        <pre>{{ JSON.stringify(basicFormData, null, 2) }}</pre>
      </div>
    </section>

    <!-- 行内表单 -->
    <section class="demo-section">
      <h2>行内表单</h2>
      <CuiForm
        ref="inlineFormRef"
        v-model="inlineFormData"
        :fields="inlineFields"
        inline
      />
      <div class="demo-actions">
        <el-button type="primary" @click="handleInlineSubmit">搜索</el-button>
        <el-button @click="handleInlineReset">重置</el-button>
      </div>
    </section>

    <!-- 带验证的表单 -->
    <section class="demo-section">
      <h2>带验证的表单</h2>
      <CuiForm
        ref="validationFormRef"
        v-model="validationFormData"
        :fields="validationFields"
        label-width="120px"
      />
      <div class="demo-actions">
        <el-button type="primary" @click="handleValidationSubmit">提交</el-button>
        <el-button @click="handleValidationReset">重置</el-button>
      </div>
    </section>

    <!-- 所有字段类型演示 -->
    <section class="demo-section">
      <h2>所有字段类型演示</h2>
      <CuiForm
        ref="allTypesFormRef"
        v-model="allTypesFormData"
        :fields="allTypesFields"
        label-width="120px"
      />
      <div class="demo-actions">
        <el-button type="primary" @click="handleAllTypesSubmit">提交</el-button>
        <el-button @click="handleAllTypesReset">重置</el-button>
      </div>
      <div v-if="allTypesFormResult" class="demo-result">
        <p>表单数据：</p>
        <pre>{{ JSON.stringify(allTypesFormData, null, 2) }}</pre>
      </div>
    </section>

    <!-- 自定义字段表单 -->
    <section class="demo-section">
      <h2>自定义字段表单</h2>
      <CuiForm
        ref="customFormRef"
        v-model="customFormData"
        :fields="customFields"
        label-width="120px"
      >
        <template #customField="{ value, updateValue }">
          <div class="custom-field">
            <el-slider
              :model-value="value"
              :min="0"
              :max="100"
              show-input
              @update:model-value="updateValue"
            />
          </div>
        </template>
      </CuiForm>
      <div class="demo-actions">
        <el-button type="primary" @click="handleCustomSubmit">提交</el-button>
        <el-button @click="handleCustomReset">重置</el-button>
      </div>
    </section>

    <!-- 禁用状态表单 -->
    <section class="demo-section">
      <h2>禁用状态表单</h2>
      <el-button @click="toggleDisabled">切换禁用状态</el-button>
      <CuiForm
        ref="disabledFormRef"
        v-model="disabledFormData"
        :fields="basicFields"
        :disabled="isDisabled"
        label-width="120px"
      />
    </section>

    <!-- 顶部标签表单 -->
    <section class="demo-section">
      <h2>顶部标签表单</h2>
      <CuiForm
        ref="topLabelFormRef"
        v-model="topLabelFormData"
        :fields="basicFields"
        label-position="top"
      />
      <div class="demo-actions">
        <el-button type="primary" @click="handleTopLabelSubmit">提交</el-button>
        <el-button @click="handleTopLabelReset">重置</el-button>
      </div>
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { CuiForm } from '@eams/vue-element-cui';
import type { CuiFormField } from '@eams/vue-element-cui';
import { ElButton, ElSlider, ElMessage } from 'element-plus';

// 基础表单
const basicFormRef = ref();
const basicFormData = ref({
  name: '',
  email: '',
  age: 0,
});
const basicFormResult = ref(false);

const basicFields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
    required: true,
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
    required: true,
  },
  {
    prop: 'age',
    label: '年龄',
    type: 'number',
    placeholder: '请输入年龄',
  },
];

const handleBasicSubmit = async () => {
  const result = await basicFormRef.value?.submit();
  if (result?.valid) {
    basicFormResult.value = true;
    ElMessage.success('提交成功');
  } else {
    ElMessage.error('请填写必填项');
  }
};

const handleBasicReset = () => {
  basicFormRef.value?.resetFields();
  basicFormResult.value = false;
};

// 行内表单
const inlineFormRef = ref();
const inlineFormData = ref({
  keyword: '',
  status: '',
});

const inlineFields: CuiFormField[] = [
  {
    prop: 'keyword',
    label: '关键词',
    type: 'input',
    placeholder: '请输入关键词',
  },
  {
    prop: 'status',
    label: '状态',
    type: 'select',
    placeholder: '请选择状态',
    options: [
      { label: '全部', value: '' },
      { label: '活跃', value: 'active' },
      { label: '非活跃', value: 'inactive' },
    ],
  },
];

const handleInlineSubmit = async () => {
  const result = await inlineFormRef.value?.submit();
  if (result?.valid) {
    ElMessage.success('搜索成功');
    console.log('搜索条件:', inlineFormData.value);
  }
};

const handleInlineReset = () => {
  inlineFormRef.value?.resetFields();
};

// 带验证的表单
const validationFormRef = ref();
const validationFormData = ref({
  username: '',
  email: '',
  phone: '',
  password: '',
});

const validationFields: CuiFormField[] = [
  {
    prop: 'username',
    label: '用户名',
    type: 'input',
    placeholder: '请输入用户名',
    required: true,
    rules: [
      { min: 3, max: 20, message: '用户名长度在 3 到 20 个字符', trigger: 'blur' },
    ],
  },
  {
    prop: 'email',
    label: '邮箱',
    type: 'input',
    placeholder: '请输入邮箱',
    required: true,
    rules: [
      { type: 'email', message: '请输入正确的邮箱格式', trigger: 'blur' },
    ],
  },
  {
    prop: 'phone',
    label: '手机号',
    type: 'input',
    placeholder: '请输入手机号',
    rules: [
      { pattern: /^1[3-9]\d{9}$/, message: '请输入正确的手机号', trigger: 'blur' },
    ],
  },
  {
    prop: 'password',
    label: '密码',
    type: 'input',
    placeholder: '请输入密码',
    required: true,
    rules: [
      { min: 6, message: '密码长度不能少于 6 个字符', trigger: 'blur' },
    ],
  },
];

const handleValidationSubmit = async () => {
  const result = await validationFormRef.value?.submit();
  if (result?.valid) {
    ElMessage.success('验证通过，提交成功');
  } else {
    ElMessage.error('请检查表单填写');
  }
};

const handleValidationReset = () => {
  validationFormRef.value?.resetFields();
};

// 所有字段类型演示
const allTypesFormRef = ref();
const allTypesFormData = ref({
  input: '',
  textarea: '',
  number: 0,
  select: '',
  date: '',
});
const allTypesFormResult = ref(false);

const allTypesFields: CuiFormField[] = [
  {
    prop: 'input',
    label: '文本输入',
    type: 'input',
    placeholder: '请输入文本',
  },
  {
    prop: 'textarea',
    label: '多行文本',
    type: 'textarea',
    placeholder: '请输入多行文本',
  },
  {
    prop: 'number',
    label: '数字输入',
    type: 'number',
    placeholder: '请输入数字',
  },
  {
    prop: 'select',
    label: '选择框',
    type: 'select',
    placeholder: '请选择',
    options: [
      { label: '选项1', value: 'option1' },
      { label: '选项2', value: 'option2' },
      { label: '选项3', value: 'option3' },
    ],
  },
  {
    prop: 'date',
    label: '日期选择',
    type: 'date',
    placeholder: '请选择日期',
  },
];

const handleAllTypesSubmit = async () => {
  const result = await allTypesFormRef.value?.submit();
  if (result?.valid) {
    allTypesFormResult.value = true;
    ElMessage.success('提交成功');
  }
};

const handleAllTypesReset = () => {
  allTypesFormRef.value?.resetFields();
  allTypesFormResult.value = false;
};

// 自定义字段表单
const customFormRef = ref();
const customFormData = ref({
  name: '',
  score: 50,
});

const customFields: CuiFormField[] = [
  {
    prop: 'name',
    label: '姓名',
    type: 'input',
    placeholder: '请输入姓名',
  },
  {
    prop: 'score',
    label: '评分',
    type: 'input', // 类型不重要，因为使用了自定义插槽
    slot: 'customField',
  },
];

const handleCustomSubmit = async () => {
  const result = await customFormRef.value?.submit();
  if (result?.valid) {
    ElMessage.success('提交成功');
    console.log('自定义表单数据:', customFormData.value);
  }
};

const handleCustomReset = () => {
  customFormRef.value?.resetFields();
};

// 禁用状态表单
const disabledFormRef = ref();
const disabledFormData = ref({
  name: 'John Doe',
  email: 'john@example.com',
  age: 30,
});
const isDisabled = ref(false);

const toggleDisabled = () => {
  isDisabled.value = !isDisabled.value;
};

// 顶部标签表单
const topLabelFormRef = ref();
const topLabelFormData = ref({
  name: '',
  email: '',
  age: 0,
});

const handleTopLabelSubmit = async () => {
  const result = await topLabelFormRef.value?.submit();
  if (result?.valid) {
    ElMessage.success('提交成功');
  }
};

const handleTopLabelReset = () => {
  topLabelFormRef.value?.resetFields();
};
</script>

<style scoped>
.cui-form-demo {
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

.demo-actions {
  margin-top: 16px;
}

.demo-result {
  margin-top: 16px;
  padding: 12px;
  background: #fff;
  border-radius: 4px;
}

.demo-result p {
  margin-bottom: 8px;
  font-weight: 600;
}

.demo-result pre {
  margin: 0;
  padding: 12px;
  background: #f5f7fa;
  border-radius: 4px;
  font-size: 12px;
  overflow-x: auto;
}

.custom-field {
  width: 100%;
}
</style>
