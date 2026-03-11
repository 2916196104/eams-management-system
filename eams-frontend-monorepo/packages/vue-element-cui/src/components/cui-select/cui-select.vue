<template>
  <el-select
    :model-value="modelValue"
    :placeholder="placeholder"
    :disabled="disabled"
    :clearable="clearable"
    :filterable="filterable"
    :multiple="multiple"
    @update:model-value="handleChange"
  >
    <el-option
      v-for="option in options"
      :key="option.value"
      :label="option.label"
      :value="option.value"
    />
  </el-select>
</template>

<script setup lang="ts">
import { ref, defineProps, defineEmits } from 'vue';
import { ElSelect, ElOption } from 'element-plus';
import type { CuiSelectProps, CuiSelectEmits, CuiSelectOption } from './types';

const props = withDefaults(defineProps<CuiSelectProps>(), {
  placeholder: '请选择',
  disabled: false,
  clearable: true,
  filterable: true,
  multiple: false,
  options: () => [],
});

const emit = defineEmits<CuiSelectEmits>();

const handleChange = (value: any) => {
  emit('update:modelValue', value);
  emit('change', value);
};
</script>
