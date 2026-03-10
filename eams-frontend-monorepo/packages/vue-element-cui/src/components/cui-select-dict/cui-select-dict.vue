<template>
  <el-select
    :model-value="modelValue"
    :placeholder="placeholder"
    :disabled="disabled"
    :clearable="clearable"
    :filterable="filterable"
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
import { ref, onMounted, defineProps, defineEmits } from 'vue';
import { ElSelect, ElOption } from 'element-plus';
import type { CuiSelectDictProps, CuiSelectDictEmits, CuiSelectDictOption } from './types';

const props = withDefaults(defineProps<CuiSelectDictProps>(), {
  placeholder: '请选择',
  disabled: false,
  clearable: true,
  filterable: true,
});

const emit = defineEmits<CuiSelectDictEmits>();
const options = ref<CuiSelectDictOption[]>([]);

const loadDictOptions = () => {
  options.value = [
    { label: '选项 1', value: '1' },
    { label: '选项 2', value: '2' },
    { label: '选项 3', value: '3' },
  ];
};

const handleChange = (value: any) => {
  emit('update:modelValue', value);
  emit('change', value);
};

onMounted(() => {
  loadDictOptions();
});
</script>
