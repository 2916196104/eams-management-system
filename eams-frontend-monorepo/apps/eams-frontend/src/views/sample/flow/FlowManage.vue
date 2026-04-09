<template>
	<!-- 流程元数据列表 -->
	<my-table
		tabtitle="流程元数据"
		:tabdatacolumns
		:tabdata
		:taboperbtns
		@taboper-click="handleOperation"
		@page-change="handlePageChange"
	>
		<template #header>
			<el-button type="primary" @click="createNew">添加</el-button>
		</template>
		<!-- 单元格插槽 -->
		<template #customercell="{ prop, row }">
			<!-- 对状态列特殊显示处理 -->
			<template v-if="prop === 'processStatus'">
				<el-tag v-if="row[prop] === 0">草稿</el-tag>
				<el-tag v-else-if="row[prop] === 1">发布</el-tag>
				<el-tag v-else-if="row[prop] === 2">停用</el-tag>
				<el-tag v-else>未知</el-tag>
			</template>
		</template>
	</my-table>
	<!-- 流程元数据表单对话框 -->
	<my-form-dialog ref="formDialog" :="formDialogProps" @confirm="onSubmit" />
	<!-- 流程设计对话框 -->
	<my-dialog ref="cusdialog" :="cusprops" @opened="loadDesign">
		<!-- 定义内容区 -->
		<template #default>
			<!-- 流程图设计器 -->
			<my-bpmn-editor ref="myBpmnEditorRef" class="flow-designer" />
		</template>
		<!-- 定义底部栏 -->
		<template #footer>
			<el-button @click="saveFlowDesign" type="primary">保存</el-button>
			<el-button @click="cusdialog.closeDialog()" type="primary">关闭</el-button>
		</template>
	</my-dialog>
</template>

<script setup lang="ts">
// #region 导入相关

import { ref, reactive, onMounted } from "vue";
import { ElMessage } from "element-plus";
// 表格组件相关导入
import MyTable from "@/components/mytable/MyTable.vue";
import {
	createPageDTO,
	type PageDTO,
	type MyTableColumn,
	type MyTableOperationsBtn,
	createMyTableOperationsColumn,
} from "@/components/mytable/type";
// 流程图编辑器相关导入
import MyBpmnEditor from "@/components/mybpmn/MyBpmnEditor.vue";
import type { MyBpmnExport } from "@/components/mybpmn/type";
// 表单对话框相关导入
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type {
	MyFormInputNumberProps,
	MyFormInputProps,
	MyFormItemAttr,
	MyFormRadioBoxGroupProps,
	MyFormSelectProps,
} from "@/components/myform/type";
// 对话框相关导入
import MyDialog from "@/components/mydialog/MyDialog.vue";
import type { MyDialogProps } from "@/components/mydialog/type";
// 流程定义相关导入
import type { ProcessDefinitionAddDTO, ProcessDefinitionVO } from "@/apis/sample/flow/type";
import { addFlowDefine, deployProcess, getFlowDefine, listallFlow, modifyFlowDefine } from "@/apis/sample/flow";
import { assignOnlyExisting } from "@/utils/object";

// #endregion

// #region 变量定义

// 定义表格列数据
const tabdatacolumns: MyTableColumn[] = [
	{
		prop: "id",
		label: "ID",
	},
	{
		prop: "processName",
		label: "流程名称",
	},
	{
		prop: "processKey",
		label: "流程唯一标识",
	},
	{
		prop: "processVersion",
		label: "流程版本号",
	},
	{
		prop: "processStatus",
		label: "流程状态",
	},
	{
		prop: "description",
		label: "流程描述",
		width: "150px",
		"show-overflow-tooltip": true,
	},
	// 操作列
	createMyTableOperationsColumn({
		"min-width": 210,
		align: "center",
	}),
];
// 定义表格操作按钮数据
const taboperbtns: MyTableOperationsBtn[] = [
	{
		evtname: "edit",
		text: "修改",
		attr: {
			type: "primary",
			icon: "icon-edit",
		},
	},
	{
		evtname: "design",
		text: "设计",
		attr: {
			type: "primary",
		},
	},
	{
		evtname: "publish",
		text: "发布",
		attr: {
			type: "success",
		},
	},
];
// 定义表格数据
const tabdata = ref<PageDTO<ProcessDefinitionVO>>(createPageDTO());

// 定义表单对话框属性
const formDialogProps = reactive<MyFormDialogProps<ProcessDefinitionAddDTO>>({
	// 表单数据
	data: reactive<ProcessDefinitionAddDTO>({
		processKey: "",
		processName: "",
		processVersion: 1,
		processStatus: 0,
		description: "",
		deleted: 0,
	}),
	// 表单域数据
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "processName",
			label: "流程名称",
			rules: [{ required: true, message: "请输入流程名称", trigger: "change" }],
			fprops: {
				placeholder: "请输入流程名称",
				clearable: true,
			} as MyFormInputProps,
		},
		{
			type: "input",
			prop: "processKey",
			label: "流程标识",
			rules: [{ required: true, message: "请输入流程唯一标识", trigger: "change" }],
			fprops: {
				placeholder: "流程唯一标识",
				clearable: true,
			} as MyFormInputProps,
		},
		{
			type: "number",
			prop: "processVersion",
			label: "流程版本",
			rules: [{ required: true, message: "请输入流程版本", trigger: "change" }],
			fprops: {
				placeholder: "请输入流程版本",
				clearable: true,
				min: 1,
			} as MyFormInputNumberProps,
		},
		{
			type: "select",
			prop: "processStatus",
			label: "流程状态",
			rules: [{ required: true, message: "请选择状态", trigger: "change" }],
			fprops: {
				placeholder: "请选择状态",
				options: [
					{
						label: "草稿",
						value: 0,
					},
					{
						label: "发布",
						value: 1,
					},
					{
						label: "停用",
						value: 2,
					},
				],
			} as MyFormSelectProps,
		},
		{
			type: "input",
			prop: "description",
			label: "流程描述",
			fprops: {
				placeholder: "请输入流程描述",
			},
		},
		{
			type: "radio-group",
			prop: "deleted",
			label: "删除状态",
			fprops: {
				radioboxes: [
					{
						label: "否",
						value: 0,
					},
					{
						label: "是",
						value: 1,
					},
				],
			} as MyFormRadioBoxGroupProps,
		},
	]),
	// 表单属性
	formattr: {
		// 当这个值为true时表单元素全部禁止修改,对话框也不在显示提交和重置按钮
		disabled: false,
		"label-width": "80px",
	},
	title: "流程元数据编辑",
	width: "35vw",
	reset: true,
});
// 定义表单对话框引用
const formDialog = ref();

// 定义对话框属性
const cusprops = reactive<MyDialogProps<ProcessDefinitionVO>>({
	data: {} as ProcessDefinitionVO,
	title: "流程设计",
	fullscreen: true,
});
// 定义对话框引用
const cusdialog = ref();

// myBpmnEditor实例引用
const myBpmnEditorRef = ref<MyBpmnExport>();
// 当前操作流程定义数据对象
const flowDefine = ref<ProcessDefinitionVO | null>();
// 定义一个编辑项索引，用于编辑回调处理数据更新
const editIndex = ref<number>(-1);
// #endregion

// 组件挂载钩子函数
onMounted(() => {
	loadData();
});

// 添加流程定义
function createNew() {
	// 重置表单数据
	Object.assign(formDialogProps.data, {
		processKey: "",
		processName: "",
		processVersion: 1,
		processStatus: 0,
		description: "",
		deleted: 0,
	});
	flowDefine.value = null;
	// 打开对话框
	formDialog.value.openDialog(true);
}

// 加载数据
function loadData() {
	listallFlow(
		{
			pageIndex: tabdata.value.pageIndex,
			pageSize: tabdata.value.pageSize,
		},
		(data) => {
			tabdata.value = data;
		},
		(err) => {
			ElMessage.error(err.data?.message || "加载数据失败");
		},
	);
}

// 表格分页组件改变触发数据刷新
function handlePageChange(data: PageDTO<ProcessDefinitionVO>) {
	tabdata.value.pageIndex = data.pageIndex;
	tabdata.value.pageSize = data.pageSize;
	loadData();
}

// 表格操作按钮点击事件处理
function handleOperation(index: number, row: ProcessDefinitionVO, evtname: string) {
	// 当前操作流程定义数据对象
	flowDefine.value = row;
	switch (evtname) {
		case "edit":
			editIndex.value = index;
			assignOnlyExisting(formDialogProps.data, row);
			formDialog.value.openDialog(true);
			break;
		case "design":
			cusprops.data = row;
			cusdialog.value.openDialog();
			break;
		case "publish":
			deployProcess({
				processKey: row.processKey,
				processVersion: row.processVersion,
			})
				.then(() => {
					row.processStatus = 1;
					ElMessage.success("发布成功");
				})
				.catch((err) => {
					ElMessage.error(err.data?.message || "发布失败");
				});
			break;
	}
}

// 对话框提交表单
function onSubmit(fdata: ProcessDefinitionAddDTO) {
	// 新增流程定义
	if (!flowDefine.value) {
		addFlowDefine({ ...fdata })
			.then(() => {
				// 关闭对话框
				formDialog.value.closeDialog();
				// 刷新显示
				loadData();
				ElMessage.success("添加成功");
			})
			.catch((err) => {
				ElMessage.error(err.data?.message || "添加失败");
			});
	}
	// 修改流程
	else {
		modifyFlowDefine({ ...fdata, id: flowDefine.value.id })
			.then((res) => {
				// 刷新表格中对应行的数据显示
				if (tabdata.value?.rows) Object.assign(tabdata.value?.rows[editIndex.value], res.data);
				flowDefine.value = null;
				// 关闭对话框
				formDialog.value.closeDialog();
				ElMessage.success("保存成功");
			})
			.catch((err) => {
				ElMessage.error(err.data?.message || "保存失败");
			});
	}
}

// 加载指定流程定义
function loadDesign() {
	if (!flowDefine.value) {
		ElMessage.error("没有选择流程定义");
		return;
	}
	getFlowDefine(flowDefine.value.id)
		.then((res) => {
			flowDefine.value = res.data;
			if (!res.data?.xml) {
				// 创建新面板
				myBpmnEditorRef.value?.createNewDiagram(flowDefine.value?.processName, flowDefine.value?.processKey);
			} else {
				// 加载流程定义
				myBpmnEditorRef.value?.loadXML(res.data?.xml);
			}
		})
		.catch((err) => {
			ElMessage.error(err.data?.message || "加载流程失败");
			flowDefine.value = null;
			cusdialog.value.closeDialog();
		});
}

// 保存流程设计
async function saveFlowDesign() {
	if (!flowDefine.value) {
		ElMessage.error("请重新选择要修改的流程定义");
		return;
	}
	// 提取设计器中的xml数据
	const { xml } = await myBpmnEditorRef.value?.modeler.saveXML({ format: true });
	modifyFlowDefine({
		id: flowDefine.value.id,
		processName: flowDefine.value.processName,
		processKey: flowDefine.value.processKey,
		processVersion: flowDefine.value.processVersion,
		processStatus: flowDefine.value.processStatus,
		deleted: flowDefine.value.deleted,
		xml,
		xmlMongoId: flowDefine.value.xmlMongoId,
	})
		.then(() => {
			ElMessage.success("保存成功");
		})
		.catch((err) => {
			ElMessage.error(err.data?.message || "保存失败");
		});
}
</script>

<style scoped>
.flow-designer {
	width: 100%;
	height: 89vh;
}
</style>
