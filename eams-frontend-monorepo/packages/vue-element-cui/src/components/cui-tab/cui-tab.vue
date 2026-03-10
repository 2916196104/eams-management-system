<template>
  <el-tabs
    :model-value="activeTab"
    :type="type"
    :closable="closable"
    :addable="addable"
    :editable-type="editableType"
    @update:model-value="$emit('update:activeTab', $event)"
    @tab-add="$emit('add')"
    @tab-remove="$emit('remove', $event)"
    @tab-change="handleTabChange"
  >
    <el-tab-pane
      v-for="tab in tabs"
      :key="tab.name"
      :label="tab.label"
      :name="tab.name"
      :disabled="tab.disabled"
      :closable="tab.closable"
    >
      <slot :name="`tab-${tab.name}`" :tab="tab">
        {{ tab.content }}
      </slot>
    </el-tab-pane>
  </el-tabs>
</template>

<script setup lang="ts">
import { defineProps, defineEmits } from 'vue';
import { ElTabs, ElTabPane } from 'element-plus';
import type { CuiTabProps } from './types';

const props = withDefaults(defineProps<CuiTabProps>(), {
  type: 'card',
  closable: false,
  addable: false,
  editableType: 'add',
});

const emit = defineEmits<{
  'update:activeTab': [value: string];
  'tab-change': [value: string];
  'add': [];
  'remove': [value: string];
}>();

const handleTabChange = (tabName: string) => {
  emit('tab-change', tabName);
};
</script>

