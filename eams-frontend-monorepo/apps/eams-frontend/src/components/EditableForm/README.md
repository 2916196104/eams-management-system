# 可编辑表单组件 EditableForm

## 功能描述

一个支持查看/编辑模式切换的表单组件，自动根据数据类型渲染对应的输入组件。

## 特性

- ✅ 支持查看/编辑双模式切换
- ✅ 支持 v-model 双向绑定
- ✅ 自动识别数据类型（字符串、数字、布尔值）
- ✅ 支持长文本、日期等特殊字段类型
- ✅ 完善的 Props 和 Events

## 使用方法

### 基础用法

```vue
<template>
	<editable-form v-model="formData" :field-labels="labels" @save="handleSave" />
</template>

<script>
import EditableForm from "@/components/EditableForm";

export default {
	components: { EditableForm },
	data() {
		return {
			formData: {
				name: "张三",
				age: 25,
				active: true,
				remark: "这是一段备注",
			},
			labels: {
				name: "姓名",
				age: "年龄",
				active: "是否激活",
				remark: "备注",
			},
		};
	},
	methods: {
		handleSave(data) {
			console.log("保存的数据：", data);
			// 这里可以调用API保存数据
		},
	},
};
</script>

<template>
	<editable-form
		v-model="formData"
		:field-labels="labels"
		:long-text-fields="['remark', 'description']"
		:date-fields="['birthday', 'joinDate']"
		@save="handleSave"
	/>
</template>

<script>
export default {
	data() {
		return {
			formData: {
				name: "李四",
				birthday: "1990-01-01",
				remark: "这是一段很长的备注信息，会自动显示为textarea",
				score: 95,
			},
			labels: {
				name: "姓名",
				birthday: "出生日期",
				remark: "备注信息",
				score: "分数",
			},
		};
	},
};
</script>

<template>
	<editable-form
		v-model="formData"
		:field-labels="labels"
		:long-text-fields="['remark', 'description']"
		:date-fields="['birthday', 'joinDate']"
		@save="handleSave"
	/>
</template>

<script>
export default {
	data() {
		return {
			formData: {
				name: "李四",
				birthday: "1990-01-01",
				remark: "这是一段很长的备注信息，会自动显示为textarea",
				score: 95,
			},
			labels: {
				name: "姓名",
				birthday: "出生日期",
				remark: "备注信息",
				score: "分数",
			},
		};
	},
};
</script>

API Props 参数 说明 类型 默认值 value / v-model 表单数据 Object {} field-labels 字段标签映射 Object {}
long-text-field长文本字段列表 Array [] date-fields 日期字段列表 Array [] editable 是否可编辑 Boolean true Events 事件名
说明 回调参数 input v-model 事件 更新后的数据 save 点击保存按钮时触发 表单数据 cancel 点击取消按钮时触发 - edit-start
开始编辑时触发 - 数据类型自动识别规则 数据类型 查看模式显示 编辑模式组件 String 原样显示 el-input / el-textarea Number
数字 el-input-number Boolean 是/否 el-switch Date (在date-fields中) 日期字符串 el-date-picker Object JSON字符串
el-textarea
```
