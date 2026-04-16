# EditableForm 可编辑表单组件

此可编辑表单组件是对 Element Plus 表单组件的封装，主要实现了查看/编辑模式切换、字段类型自动识别、多种输入控件渲染等功能的配置化开发，**封装的主要思路是通过配置驱动表单渲染，减少重复的界面代码**，组件演示代码在 sample 中已经书写，可以自己运行观察效果。

## 1 整体使用步骤

### 1.1 导入组件

导入组件关键代码如下

```html
<script setup lang="ts">
	import EditableForm from "@/components/EditableForm.vue";
	import type { FormConfig } from "@/components/EditableForm/type";
	import { FieldType } from "@/components/EditableForm/type";
</script>
1.2 类型定义
组件依赖的类型定义在 type.ts 中，主要包括以下类型：

1.2.1 FieldType 枚举
js
export enum FieldType {
	string = "string", // 普通文本
	longText = "longText", // 长文本（textarea）
	number = "number", // 数字
	boolean = "boolean", // 布尔值（开关）
	date = "date", // 日期
	datetime = "datetime", // 日期时间
}
1.2.2 FormField 接口
js
export interface FormField {
	prop: string // 字段名
	label: string // 字段标签
	type?: FieldType // 字段类型，不指定则自动识别
	placeholder?: string // 输入框占位符
	width?: string // 标签宽度
	span?: number // 栅格占位（支持多列布局）
	required?: boolean // 是否必填
	rules?: any[] // 表单校验规则
	disabled?: boolean // 是否禁用
	[key: string]: any // 允许任意其他属性
}
1.2.3 FormConfig 接口
js
export interface FormConfig {
	fields: FormField[] // 表单字段配置
	labelWidth?: string // 标签宽度，默认100px
	labelPosition?: "left" | "right" | "top" // 标签位置
	size?: "large" | "default" | "small" // 表单尺寸
	disabled?: boolean // 全局禁用
	editable?: boolean // 是否可编辑，默认true
	viewStyle?: object // 查看模式样式
	editStyle?: object // 编辑模式样式
}
1.2.4 FormData 类型
js
export type FormData = Record<string, any>
1.3 定义表单配置
使用表单组件需要定义 FormConfig 配置对象，包括字段列表、样式配置等。

html
<script setup lang="ts">
	import { ref, reactive } from "vue";
	import EditableForm from "@/components/EditableForm.vue";
	import type { FormConfig } from "@/components/EditableForm/type";
	import { FieldType } from "@/components/EditableForm/type";

	// 定义表单数据
	const formData = ref<any>({
		username: "",
		age: 0,
		email: "",
		bio: "",
		birthday: "",
		isActive: false,
	});

	// 定义表单配置
	const formConfig = reactive<FormConfig>({
		// 全局配置
		labelWidth: "100px",
		labelPosition: "right",
		size: "default",
		editable: true,

		// 字段配置
		fields: [
			{
				prop: "username",
				label: "用户名",
				type: FieldType.string,
				placeholder: "请输入用户名",
				required: true,
				width: "120px",
			},
			{
				prop: "age",
				label: "年龄",
				type: FieldType.number,
				placeholder: "请输入年龄",
			},
			{
				prop: "email",
				label: "邮箱",
				type: FieldType.string,
				placeholder: "请输入邮箱",
			},
			{
				prop: "bio",
				label: "个人简介",
				type: FieldType.longText,
				placeholder: "请输入个人简介",
				span: 24, // 占满整行
			},
			{
				prop: "birthday",
				label: "生日",
				type: FieldType.date,
				placeholder: "请选择生日",
			},
			{
				prop: "isActive",
				label: "是否启用",
				type: FieldType.boolean,
			},
		],

		// 样式配置
		viewStyle: {
			backgroundColor: "#f5f7fa",
		},
	});
</script>
1.4 绑定事件
表单组件支持以下事件：

html
<script setup lang="ts">
	// 开始编辑事件
	function handleEditStart() {
		console.log("开始编辑");
	}

	// 保存事件
	function handleSave(data: any) {
		console.log("保存数据:", data);
		// 调用保存接口
	}

	// 取消编辑事件
	function handleCancel() {
		console.log("取消编辑");
	}

	// 字段变化事件
	function handleFieldChange(prop: string, value: any) {
		console.log(`字段 ${prop} 变化:`, value);
	}
</script>
1.5 编写组件标签
在 template 中编写组件标签，并绑定配置、数据和事件：

html
<template>
	<EditableForm
		v-model="formData"
		:config="formConfig"
		@edit-start="handleEditStart"
		@save="handleSave"
		@cancel="handleCancel"
		@field-change="handleFieldChange"
	/>
</template>
2 高级用法
2.1 混合布局（多列布局）
通过配置 span 属性实现多列布局：

js
const formConfig = reactive<FormConfig>({
	fields: [
		{ prop: "name", label: "姓名", span: 12 }, // 占半行
		{ prop: "age", label: "年龄", span: 12 }, // 占半行
		{ prop: "email", label: "邮箱", span: 24 }, // 占整行
	],
});
2.2 自定义插槽
对于特殊需求的字段，可以使用自定义插槽：

html
<template>
	<EditableForm v-model="formData" :config="formConfig">
		<!-- 自定义字段插槽，slotName 为字段名 -->
		<template #customField="{ value, updateValue }">
			<el-rate v-model="value" @change="updateValue" />
		</template>

		<!-- 自定义整个表单的插槽 -->
		<template #footer>
			<el-button type="primary" @click="customSave">自定义保存</el-button>
		</template>
	</EditableForm>
</template>
2.3 表单校验
支持 Element Plus 表单校验规则：

js
const formConfig = reactive<FormConfig>({
	fields: [
		{
			prop: "email",
			label: "邮箱",
			required: true,
			rules: [
				{ required: true, message: "请输入邮箱", trigger: "blur" },
				{ type: "email", message: "请输入正确的邮箱格式", trigger: "blur" },
			],
		},
	],
});
2.4 动态控制字段显示
通过 v-if 或计算属性动态控制字段：

html
<script setup>
const showExtraFields = ref(false)

const dynamicFields = computed(() => {
	const baseFields = [
		{ prop: "name", label: "姓名" },
		{ prop: "age", label: "年龄" },
	]

	if (showExtraFields.value) {
		baseFields.push(
			{ prop: "phone", label: "手机号" },
			{ prop: "address", label: "地址" }
		)
	}

	return baseFields
})
</script>

<template>
	<el-button @click="showExtraFields = !showExtraFields">
		切换显示额外字段
	</el-button>
	<EditableForm
		v-model="formData"
		:config="{ fields: dynamicFields }"
	/>
</template>
2.5 手动控制编辑状态
通过 ref 调用组件方法手动控制编辑模式：

html
<script setup>
import { ref } from 'vue'

const formRef = ref()
const formData = ref({ name: '张三' })

const handleStartEdit = () => {
	formRef.value?.startEdit()
}

const handleSaveEdit = () => {
	formRef.value?.save()
}

const handleCancelEdit = () => {
	formRef.value?.cancel()
}

const handleGetData = () => {
	const data = formRef.value?.getFormData()
	console.log('当前数据:', data)
}
</script>

<template>
	<EditableForm ref="formRef" v-model="formData" :config="formConfig" />
	<div>
		<el-button @click="handleStartEdit">开始编辑</el-button>
		<el-button @click="handleSaveEdit">保存</el-button>
		<el-button @click="handleCancelEdit">取消</el-button>
		<el-button @click="handleGetData">获取数据</el-button>
	</div>
</template>
3 完整示例
以下是一个完整的用户信息管理示例：

html
<template>
	<div class="user-info-container">
		<h3>用户信息管理</h3>

		<EditableForm
			ref="userFormRef"
			v-model="userInfo"
			:config="userFormConfig"
			@edit-start="handleEditStart"
			@save="handleSave"
			@cancel="handleCancel"
			@field-change="handleFieldChange"
		>
			<!-- 自定义状态字段显示 -->
			<template #status="{ value, updateValue }">
				<el-select v-model="value" @change="updateValue" placeholder="请选择状态">
					<el-option label="正常" value="active" />
					<el-option label="禁用" value="disabled" />
					<el-option label="待审核" value="pending" />
				</el-select>
			</template>

			<!-- 自定义底部按钮 -->
			<template #footer>
				<el-button type="info" @click="resetForm">重置</el-button>
				<el-button type="danger" @click="deleteUser">删除用户</el-button>
			</template>
		</EditableForm>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import EditableForm from '@/components/EditableForm.vue'
import type { FormConfig } from '@/components/EditableForm/type'
import { FieldType } from '@/components/EditableForm/type'

// 表单数据
const userInfo = ref({
	username: 'zhangsan',
	realname: '张三',
	age: 25,
	email: 'zhangsan@example.com',
	phone: '13800138000',
	birthday: '1998-05-15',
	bio: '前端开发工程师，热爱技术，喜欢分享',
	status: 'active',
	isVip: true,
	joinDate: '2023-01-01',
})

// 表单配置
const userFormConfig = reactive<FormConfig>({
	labelWidth: '100px',
	labelPosition: 'right',
	size: 'default',
	editable: true,

	fields: [
		{
			prop: 'username',
			label: '用户名',
			type: FieldType.string,
			placeholder: '请输入用户名',
			required: true,
			span: 12,
			rules: [
				{ required: true, message: '请输入用户名', trigger: 'blur' },
				{ min: 3, max: 20, message: '长度在 3 到 20 个字符', trigger: 'blur' }
			]
		},
		{
			prop: 'realname',
			label: '真实姓名',
			type: FieldType.string,
			placeholder: '请输入真实姓名',
			span: 12,
		},
		{
			prop: 'age',
			label: '年龄',
			type: FieldType.number,
			placeholder: '请输入年龄',
			span: 8,
		},
		{
			prop: 'email',
			label: '邮箱',
			type: FieldType.string,
			placeholder: '请输入邮箱',
			span: 8,
			rules: [
				{ type: 'email', message: '请输入正确的邮箱格式', trigger: 'blur' }
			]
		},
		{
			prop: 'phone',
			label: '手机号',
			type: FieldType.string,
			placeholder: '请输入手机号',
			span: 8,
		},
		{
			prop: 'birthday',
			label: '生日',
			type: FieldType.date,
			placeholder: '请选择生日',
			span: 12,
		},
		{
			prop: 'joinDate',
			label: '入职日期',
			type: FieldType.date,
			placeholder: '请选择入职日期',
			span: 12,
		},
		{
			prop: 'bio',
			label: '个人简介',
			type: FieldType.longText,
			placeholder: '请输入个人简介',
			span: 24,
		},
		{
			prop: 'status',
			label: '账户状态',
			type: FieldType.custom, // 自定义类型，使用插槽
			slotName: 'status',
			span: 12,
		},
		{
			prop: 'isVip',
			label: 'VIP会员',
			type: FieldType.boolean,
			span: 12,
		},
	],
})

const userFormRef = ref()

// 事件处理
const handleEditStart = () => {
	ElMessage.info('开始编辑用户信息')
}

const handleSave = (data: any) => {
	console.log('保存的用户信息:', data)
	ElMessage.success('保存成功')
	// 这里可以调用保存接口
}

const handleCancel = () => {
	ElMessage.info('已取消编辑')
}

const handleFieldChange = (prop: string, value: any) => {
	console.log(`字段 ${prop} 变更为:`, value)
	if (prop === 'username') {
		// 实时校验用户名
	}
}

const resetForm = () => {
	ElMessageBox.confirm('确认重置所有修改吗？', '提示', {
		confirmButtonText: '确认',
		cancelButtonText: '取消',
		type: 'warning',
	}).then(() => {
		userFormRef.value?.cancel()
		ElMessage.success('已重置')
	})
}

const deleteUser = () => {
	ElMessageBox.confirm('确认删除该用户吗？', '警告', {
		confirmButtonText: '确认删除',
		cancelButtonText: '取消',
		type: 'error',
	}).then(() => {
		ElMessage.success('删除成功')
		// 删除逻辑
	})
}
</script>

<style scoped>
.user-info-container {
	padding: 20px;
}
</style>
4 注意事项
组件内部会对传入的 modelValue 进行深拷贝，避免直接修改 props

取消编辑时会自动恢复原始数据

日期字段的值为字符串格式 yyyy-MM-dd

布尔值在查看模式下显示为"是"/"否"

对象类型在查看模式下会显示为 JSON 字符串

自定义插槽的 updateValue 方法需要调用以更新表单数据

字段配置支持动态添加/删除，组件会自动响应变化
