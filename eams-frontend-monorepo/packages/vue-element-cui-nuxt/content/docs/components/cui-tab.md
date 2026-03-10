# CuiTab 组件文档

## 概述

CuiTab 是一个基于 Element Plus 的 Tab 组件，提供了简洁的 API 和灵活的配置选项。

## 基础用法

```vue
<template>
  <cui-tab
    :tabs="tabs"
    :active-tab="activeTab"
    @update:active-tab="activeTab = $event"
  />
</template>

<script setup>
import { ref } from 'vue';
import { CuiTab } from '@packages/vue-element-cui';

const activeTab = ref('tab1');
const tabs = [
  { label: 'Tab 1', name: 'tab1', content: '内容 1' },
  { label: 'Tab 2', name: 'tab2', content: '内容 2' },
  { label: 'Tab 3', name: 'tab3', content: '内容 3' },
];
</script>
```

## Props

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `tabs` | `CuiTabItem[]` | - | Tab 项列表（必需） |
| `activeTab` | `string` | - | 当前活跃的 Tab（必需） |
| `type` | `'card' \| 'border-card'` | `'card'` | Tab 类型 |
| `closable` | `boolean` | `false` | 是否可关闭 |
| `addable` | `boolean` | `false` | 是否可添加 |
| `editableType` | `'add' \| 'remove' \| 'both'` | `'add'` | 可编辑类型 |

## Tab 项配置

```typescript
interface CuiTabItem {
  /** Tab 标签 */
  label: string;
  /** Tab 名称（唯一标识） */
  name: string;
  /** Tab 内容 */
  content?: string;
  /** 是否禁用 */
  disabled?: boolean;
  /** 是否可关闭 */
  closable?: boolean;
}
```

## Events

| 事件名 | 参数 | 说明 |
|--------|------|------|
| `update:activeTab` | `value: string` | 活跃 Tab 更新 |
| `tab-change` | `value: string` | Tab 切换事件 |
| `add` | - | 添加 Tab 事件 |
| `remove` | `value: string` | 移除 Tab 事件 |

## 示例

### 可关闭的 Tab

```vue
<template>
  <cui-tab
    :tabs="tabs"
    :active-tab="activeTab"
    :closable="true"
    @update:active-tab="activeTab = $event"
    @remove="handleRemoveTab"
  />
</template>

<script setup>
const handleRemoveTab = (tabName) => {
  tabs.value = tabs.value.filter(tab => tab.name !== tabName);
};
</script>
```

### 带插槽的 Tab

```vue
<template>
  <cui-tab
    :tabs="tabs"
    :active-tab="activeTab"
  >
    <template #tab-tab1>
      <div>自定义内容 1</div>
    </template>
    <template #tab-tab2>
      <div>自定义内容 2</div>
    </template>
  </cui-tab>
</template>
```
