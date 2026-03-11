export interface CuiRadioDictOption {
  label: string;
  value: any;
}

export interface CuiRadioDictProps {
  modelValue: any;
  dictCode: string;
  disabled?: boolean;
}

export interface CuiRadioDictEmits {
  'update:modelValue': [value: any];
  'change': [value: any];
}
