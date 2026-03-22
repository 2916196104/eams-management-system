# 课程表 / 日历组件

用于课程表、预约管理等场景的日历视图组件，支持月/周/日视图切换与日期选择。

## 文件说明

- `MyCalendar.vue`：主组件，提供标题栏、视图切换（月/周/日）、年月导航与月视图日历网格
- `type.ts`：类型定义（视图模式、单元格数据、组件 props）

## 基础使用

```vue
<template>
	<my-calendar title="2.课程表(预约管理、预约管理)" v-model:selected-date="selectedDate" @date-select="onDateSelect" />
</template>

<script setup lang="ts">
import MyCalendar from "@/components/mycalendar/MyCalendar.vue";
import { ref } from "vue";

const selectedDate = ref<Date | null>(null);
function onDateSelect(date: Date) {
	console.log("选中日期", date);
}
</script>
```

## Props

| 属性         | 类型                       | 默认值       | 说明         |
| ------------ | -------------------------- | ------------ | ------------ |
| title        | string                     | ''           | 顶部标题     |
| year         | number                     | 当前年       | 展示年份     |
| month        | number                     | 当前月(0-11) | 展示月份     |
| selectedDate | Date \| null               | null         | 当前选中日期 |
| viewMode     | 'month' \| 'week' \| 'day' | 'month'      | 视图模式     |

## 事件

- `update:selectedDate`：选中日期变化（v-model）
- `date-select`：用户点击某日期时触发，参数为 Date
- `update:year` / `update:month` / `update:viewMode`：对应状态变化

## 插槽

- `header`：标题右侧区域，作用域：`currentDate`、`viewMode`
- `cell`：月视图每个日期格子内容，作用域：`cell`（CalendarCell）

## 示例页

在 `views/sample/mycalendar/Index.vue` 中可查看完整示例与效果。
