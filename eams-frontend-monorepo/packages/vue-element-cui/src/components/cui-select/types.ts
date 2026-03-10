export interface CuiSelectOption {
  label: string;
  value: any;
  disabled?: boolean;
}

export interface CuiSelectProps {
  modelValue: any;
  options: CuiSelectOption[];
  placeholder?: string;
  disabled?: boolean;
  clearable?: boolean;
  filterable?: boolean;
  multiple?: boolean;
}

export interface CuiSelectEmits {
  'update:modelValue': [value: any];
  'change': [value: any];
}
