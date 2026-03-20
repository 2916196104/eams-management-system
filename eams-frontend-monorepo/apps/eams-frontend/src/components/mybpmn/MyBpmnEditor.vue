<template>
	<div class="editor-container">
		<div class="canvas" ref="modeler_container"></div>
		<div class="properties-panel-parent" ref="proppnl_container"></div>
	</div>
</template>
<script setup lang="ts">
/**
 * 导入 bpmn-js 和 bpmn-js-properties-panel 所需的样式文件。
 * 样式文件说明：
 * diagram-js.css: 提供基础的流程图渲染样式。
 * bpmn-js.css: 包含BPMN图形元素的基本样式。
 * bpmn-codes.css: 定义BPMN图形中使用的编码样式。
 * bpmn-embedded.css: 针对嵌入式BPMN图形的样式优化。
 * properties-panel.css: 提供属性面板的样式支持。
 * diagram-js-minimap.css: 提供最小化视图的样式。
 */
import "bpmn-js/dist/assets/diagram-js.css";
import "bpmn-js/dist/assets/bpmn-js.css";
import "bpmn-js/dist/assets/bpmn-font/css/bpmn-codes.css";
import "bpmn-js/dist/assets/bpmn-font/css/bpmn-embedded.css";
import "@bpmn-io/properties-panel/assets/properties-panel.css";
import "diagram-js-minimap/assets/diagram-js-minimap.css";
import { ProcessEngineType, type MyBpmnExport } from "./type";
// 从Vue中引入生命周期钩子和响应式引用
import { ref, onMounted, onBeforeUnmount } from "vue";
// 引入modeler, 用于创建和操作BPMN图表
import BpmnModeler from "bpmn-js/lib/Modeler";
// 引入国际化
import TranslateModule from "./i18n/translate";
// 引入最小化视图
import minimapModule from "diagram-js-minimap";
// 引入属性面板支持
import { BpmnPropertiesPanelModule, BpmnPropertiesProviderModule } from "bpmn-js-properties-panel";
import type { ModdleExtensions } from "bpmn-js/lib/BaseViewer";

// 引入Camunda扩展
import CamundaBpmnModdleDescriptor from "camunda-bpmn-moddle/resources/camunda.json";
import { CamundaPlatformPropertiesProviderModule } from "bpmn-js-properties-panel";

// 引入Flowable扩展属性
import FlowableModdleDescriptor from "./extension-moddle/flowable/descriptor/flowable.json";
import FlowablePropertiesProviderModule from "./extension-moddle/flowable/provider/";

// 引入Activiti扩展属性
import ActivitiModdleDescriptor from "./extension-moddle/activiti/descriptor/activiti.json";
import ActivitiPropertiesProviderModule from "./extension-moddle/activiti/provider/ActivitiPropertiesProvider";

// 定义modeler_container，用于引用BPMN图表的容器DOM元素
const modeler_container = ref<HTMLDivElement>();
// 定义proppnl_container，用于引用属性面板的容器DOM元素
const proppnl_container = ref<HTMLDivElement>();
// 定义BpmnModeler实例
const modeler_instance = ref<BpmnModeler>();

// 组件属性定义
const props = withDefaults(
	defineProps<{
		/** 使用的流程引擎类型 */
		usePeType?: ProcessEngineType;
	}>(),
	{
		// 默认使用CAMUNDA流程引擎
		usePeType: ProcessEngineType.CAMUNDA,
	},
);

// 初始化modeler
onMounted(() => {
	// 附加模块
	const additionalModules = [
		TranslateModule.zn,
		minimapModule,
		BpmnPropertiesPanelModule,
		BpmnPropertiesProviderModule,
	];
	// moddle扩展属性
	const moddleExtensions: ModdleExtensions = {};

	// 根据流程引擎类型添加模块
	if (props.usePeType == ProcessEngineType.CAMUNDA) {
		additionalModules.push(CamundaPlatformPropertiesProviderModule);
		moddleExtensions.camunda = CamundaBpmnModdleDescriptor;
	} else if (props.usePeType == ProcessEngineType.FLOWABLE) {
		additionalModules.push(FlowablePropertiesProviderModule);
		moddleExtensions.flowable = FlowableModdleDescriptor;
	} else if (props.usePeType == ProcessEngineType.ACTIVITI) {
		additionalModules.push(ActivitiPropertiesProviderModule);
		moddleExtensions.activiti = ActivitiModdleDescriptor;
	} else if (props.usePeType == ProcessEngineType.CUSTOM) {
		// FIXME: 添加自定义扩展属性
	}
	// 创建modeler实例
	modeler_instance.value = new BpmnModeler({
		container: modeler_container.value,
		propertiesPanel: {
			parent: proppnl_container.value,
		},
		additionalModules: additionalModules,
		moddleExtensions: moddleExtensions,
	});
	// 创建新面板
	createNewDiagram();
});

// 销毁modeler
onBeforeUnmount(() => {
	modeler_instance.value?.destroy();
});

// 自适应视口
function zoomFitViewPort() {
	const canvas = modeler_instance.value?.get("canvas") as any;
	canvas.zoom("fit-viewport", true);
}

/**
 * 创建新面板
 * @param name - 流程名称，可选，默认不指定
 * @param key - 流程key，可选，默认不指定
 */
function createNewDiagram(name?: string, key?: string) {
	modeler_instance.value
		?.createDiagram()
		.then(() => {
			zoomFitViewPort();
			// 设置流程名称和流程key
			const regstry = modeler_instance.value?.get("elementRegistry") as any;
			if (regstry) {
				//const process = regstry.filter((element: any) => element.type === "bpmn:Process")[0];
				const process = regstry.get("Process_1");
				if (process) {
					if (name) process.businessObject.name = name;
					if (key) process.businessObject.id = key;
				}
			}
		})
		.catch((err: any) => {
			console.log(err);
		});
}

// 加载XML
function loadXML(xml: string | undefined) {
	if (!xml) return;
	modeler_instance.value
		?.importXML(xml)
		.then(() => {
			zoomFitViewPort();
		})
		.catch((err: any) => {
			console.log(err);
		});
}

// 定义暴露给父组件的属性和方法
defineExpose<MyBpmnExport>({
	modeler: modeler_instance,
	zoomFitViewPort,
	createNewDiagram,
	loadXML,
});
</script>

<style scoped>
.editor-container {
	position: relative;
	display: flex;
	width: 100%;
	min-height: 100%;
	border-top: 1px solid #ccc;

	.canvas {
		width: 80%;
	}

	.properties-panel-parent {
		width: 20%;
		border-left: 1px solid #ccc;
		overflow: auto;

		&:empty {
			display: none;
		}

		> .djs-properties-panel {
			padding-bottom: 70px;
			min-height: 100%;
		}
	}
}
</style>

<style>
/* 调整工具栏位置 */
.djs-palette {
	top: 10px;
	left: 10px;
}

/* 修正点击节点后弹出的菜单位置错误问题 */
.djs-context-pad-parent {
	position: unset;
}

/** 修改节点点击菜单样式 */
.djs-context-pad.open {
	background-color: white;
	/* 描边效果 */
	box-shadow: 0 0 5px rgba(0, 0, 0, 0.2);
}

/* 隐藏bpmn-js版权信息 */
.bjs-powered-by {
	display: none !important;
}

/* 移除获得焦点后显示边框 */
.djs-container svg:focus {
	outline: none;
}
</style>
