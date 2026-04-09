/**
 * 自定义BPMN组件导出属性
 */
export interface MyBpmnExport {
	/** modeler实例 */
	modeler: any;
	/** 自适应视口(实现居中显示有效区域) */
	zoomFitViewPort: () => void;
	/**
	 * @param name - 流程名称，可选，默认不指定
	 * @param key - 流程key，可选，默认不指定
	 */
	createNewDiagram: (name?: string, key?: string) => void;
	/** 加载XML */
	loadXML: (xml: string | undefined) => void;
}

/**
 * 流程引擎类型
 */
export enum ProcessEngineType {
	CAMUNDA,
	ACTIVITI,
	FLOWABLE,
	CUSTOM,
}
