# 流程编辑器组件使用说明

基于`bpmn.js`封装流程图编辑器，集成常用的插件以及显示属性面板。

`bpmn.js`使用参考：https://github.com/bpmn-io/bpmn-js-examples

组件会暴露如下属性

```js
/**
 * 自定义BPMN组件导出属性
 */
export interface MyBpmnExport {
  /** modeler实例 */
  modeler: any
  /** 自适应视口(实现居中显示有效区域) */
  zoomFitViewPort: () => void
  /**
   * @param name - 流程名称，可选，默认不指定
   * @param key - 流程key，可选，默认不指定
   */
  createNewDiagram: (name?: string, key?: string) => void
  /** 加载XML */
  loadXML: (xml: string | undefined) => void
}
```

组件演示代码在`sample/flow`中已经书写，可以自己运行观察效果。

## 组件目录结构

- `extension-moddle`：moddle 扩展支持目录，这里是大家需要根据业务需求调整的，主要是扩展属性面板中属性设置
- `i18n`：国际化支持，开发过程中根据需要完善语言包即可
- `MyBpmnEditor.vue`：vue 组件实现代码
- `type.ts`：类型定义文件

## 使用说明

### 导入组件

导入组件示例代码如下

```html
<script setup lang="ts">
	import { ref } from "vue";
	import MyBpmnEditor from "@/components/mybpmn/MyBpmnEditor.vue";
	import type { MyBpmnExport } from "@/components/mybpmn/type";

	// myBpmnEditor实例引用
	const myBpmnEditorRef = ref<MyBpmnExport>();
</script>
```

### 编写组件标签

在 template 中编写组件标签，示例代码如下

```html
<template>
	<my-bpmn-editor ref="myBpmnEditorRef" />
</template>
```

到此组件导入成功，如果要使用`BpmnModeler`实例完成更多的操作，可以参看 sample 示例，示例中演示了导入导出功能

## 属性扩展注意事项

### 如何切换流程引擎

可以通过`usePeType`属性来设置属性扩展使用的流程引擎类型，默认使用的是`Camunda`（这个是官方支持比较完善的属性扩展）

下面的是指定流程引擎的示例代码，切换为`Flowable`流程引擎

```html
<template>
	<my-bpmn-editor ref="myBpmnEditorRef" :usePeType="ProcessEngineType.FLOWABLE" />
</template>

<script setup lang="ts">
	import { ref } from "vue";
	import MyBpmnEditor from "@/components/mybpmn/MyBpmnEditor.vue";
	import { ProcessEngineType, type MyBpmnExport } from "@/components/mybpmn/type";

	// myBpmnEditor实例引用
	const myBpmnEditorRef = ref<MyBpmnExport>();
</script>
```

### `Flowable`属性扩展

官方是不支持`Flowable`流程引擎的，需要我们根据业务需求去完善`Flowable`流程引擎支持，扩展的整体框架已经规划好了，并且写了几个扩展示例，后期根据业务需求在扩展属性即可

### 其他属性扩展支持

为了规范扩展代码书写，我默认创建了一个`activi`支持目录，但是代码是空的，如果你要扩展`activi`，修改并完善代码即可。

如果要扩展其他流程引擎，创建对应的目录结构书写代码即可。
