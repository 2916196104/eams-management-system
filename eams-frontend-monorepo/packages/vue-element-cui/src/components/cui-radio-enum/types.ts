export interface CuiRadioEnumOption {
  label: string;
  value: any;
}

export interface CuiRadioEnumProps {
  modelValue: any;
  enumCode: string;
  disabled?: boolean;
}

export interface CuiRadioEnumEmits {
  'update:modelValue': [value: any];
  'change': [value: any];
}
