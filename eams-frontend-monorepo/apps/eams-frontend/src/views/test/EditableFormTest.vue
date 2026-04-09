<template>
	<div class="test-container">
		<el-card>
			<template #header>
				<h2>可修改表单组件测试</h2>
			</template>

			<!-- 使用 EditableForm 组件 -->
			<EditableForm
				v-model="formData"
				:field-labels="fieldLabels"
				:long-text-fields="longTextFields"
				:date-fields="dateFields"
				:editable="true"
				@save="handleSave"
				@edit-start="handleEditStart"
				@cancel="handleCancel"
			/>

			<!-- 调试信息 -->
			<el-divider />
			<el-alert title="调试信息" type="info" :closable="false" />
			<pre style="background: #f5f5f5; padding: 10px; margin-top: 10px">{{ formData }}</pre>
		</el-card>
	</div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import { ElMessage } from "element-plus";
import EditableForm from "@/components/EditableForm/index.vue";

// 表单数据
const formData = ref({
	name: "张三",
	age: 25,
	email: "zhangsan@example.com",
	description: "这是一个描述信息，用于测试长文本输入",
	birthday: "1999-01-01",
	isActive: true,
	remark: "备注信息",
});

// 字段标签映射（用于显示中文）
const fieldLabels = {
	name: "姓名",
	age: "年龄",
	email: "邮箱",
	description: "描述",
	birthday: "生日",
	isActive: "是否激活",
	remark: "备注",
};

// 长文本字段（这些字段会显示为 textarea）
const longTextFields = ["description", "remark"];

// 日期字段
const dateFields = ["birthday"];

// 保存事件
const handleSave = (data: any) => {
	console.log("保存数据:", data);
	ElMessage.success("保存成功");
};

// 编辑开始事件
const handleEditStart = () => {
	console.log("开始编辑");
};

// 取消事件
const handleCancel = () => {
	console.log("取消编辑");
};
</script>

<style scoped>
.test-container {
	padding: 20px;
	max-width: 800px;
	margin: 0 auto;
}
</style>
