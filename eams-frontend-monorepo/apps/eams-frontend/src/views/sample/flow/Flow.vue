<template>
	<!-- 工具栏 -->
	<input type="file" ref="fileInput" accept=".xml" hidden @change="handleFileChange" :key="fileKey" />
	<div class="tools">
		<el-button type="primary" @click="importFile">本地导入</el-button>
		<el-button type="primary" @click="recreate">重新创建</el-button>
		<el-button type="primary" @click="saveXml">另存为XML</el-button>
		<el-button type="primary" @click="saveSvg">另存为SVG</el-button>
	</div>
	<!-- 流程图设计器 -->
	<div class="content">
		<my-bpmn-editor ref="myBpmnEditorRef" :usePeType="ProcessEngineType.FLOWABLE" />
	</div>
</template>
<script setup lang="ts">
import { ref } from "vue";
import { ElMessage } from "element-plus";
import MyBpmnEditor from "@/components/mybpmn/MyBpmnEditor.vue";
import { ProcessEngineType, type MyBpmnExport } from "@/components/mybpmn/type";

// myBpmnEditor实例引用
const myBpmnEditorRef = ref<MyBpmnExport>();

// 文件选择框
const fileInput = ref<HTMLInputElement>();
const fileKey = ref(0);
// 处理文件框文件选择事件
function handleFileChange(e: any) {
	const file = e.target.files[0];
	if (file) {
		const reader = new FileReader();
		reader.onload = (e) => {
			// 获取XML
			const xml = e.target?.result as string;
			// 加载XML
			myBpmnEditorRef.value?.loadXML(xml);
			// 重新渲染文件选择框
			fileKey.value = fileKey.value === 0 ? 1 : 0;
		};
		reader.readAsText(file);
	}
}

// 导入文件
function importFile() {
	fileInput.value?.click();
}

// 重新创建
function recreate() {
	myBpmnEditorRef.value?.createNewDiagram();
}

// 下载文件
function downFile(blob: any, filename: string) {
	const link = document.createElement("a");
	link.href = window.URL.createObjectURL(blob);
	link.download = filename;
	link.style.display = "none";
	document.body.appendChild(link);
	link.click();
	window.URL.revokeObjectURL(link.href);
	document.body.removeChild(link);
	ElMessage.success("下载成功");
}

// 保存为xml文件
function saveXml() {
	myBpmnEditorRef.value?.modeler
		.saveXML({ format: true })
		.then((res: any) => {
			const xml = res.xml as string;
			const blob = new Blob([xml], { type: "application/xml" });
			downFile(blob, "bpmn-" + Date.now() + ".xml");
		})
		.catch((error: any) => console.log(error));
}

// 保存SVG文件
function saveSvg() {
	myBpmnEditorRef.value?.modeler
		.saveSVG()
		.then((res: any) => {
			const svg = res.svg as string;
			const blob = new Blob([svg], { type: "image/svg+xml" });
			downFile(blob, "bpmn-" + Date.now() + ".svg");
		})
		.catch((error: any) => console.log(error));
}
</script>

<style scoped>
.tools {
	display: flex;
	justify-content: flex-end;
	padding-bottom: 8px;
}

.content {
	width: 100%;
	height: 85.41vh;
}
</style>
