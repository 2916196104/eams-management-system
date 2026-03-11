<template>
  <el-autocomplete
    :model-value="modelValue"
    :fetch-suggestions="fetchSuggestions"
    :placeholder="placeholder"
    :disabled="disabled"
    :clearable="clearable"
    @update:model-value="handleChange"
    @select="handleSelect"
  />
</template>

<script setup lang="ts">
import { defineProps, defineEmits } from 'vue';
import { ElAutocomplete } from 'element-plus';
import type { CuiAutocompleteProps, CuiAutocompleteEmits } from './types';

const props = withDefaults(defineProps<CuiAutocompleteProps>(), {
  placeholder: '请输入',
  disabled: false,
  clearable: true,
});

const emit = defineEmits<CuiAutocompleteEmits>();

const fetchSuggestions = (queryString: string, callback: any) => {
  const suggestions = props.suggestions
    .filter((item) => item.value.toLowerCase().includes(queryString.toLowerCase()))
    .map((item) => ({ value: item.value, label: item.label }));
  callback(suggestions);
};

const handleChange = (value: string) => {
  emit('update:modelValue', value);
};

const handleSelect = (item: any) => {
  emit('select', item);
};
</script>
