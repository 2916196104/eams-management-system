export interface CuiCheckboxEnumOption {
  label: string;
  value: any;
}

export interface CuiCheckboxEnumProps {
  modelValue: any[];
  enumCode: string;
  disabled?: boolean;
}

export interface CuiCheckboxEnumEmits {
  'update:modelValue': [value: any[]];
  'change': [value: any[]];
}
