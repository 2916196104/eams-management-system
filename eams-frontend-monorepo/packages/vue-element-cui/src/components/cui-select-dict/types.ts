export interface CuiSelectDictOption {
  label: string;
  value: any;
}

export interface CuiSelectDictProps {
  modelValue: any;
  dictCode: string;
  placeholder?: string;
  disabled?: boolean;
  clearable?: boolean;
  filterable?: boolean;
}

export interface CuiSelectDictEmits {
  'update:modelValue': [value: any];
  'change': [value: any];
}
