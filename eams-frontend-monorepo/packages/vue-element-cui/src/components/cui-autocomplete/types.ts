export interface CuiAutocompleteSuggestion {
  value: string;
  label: string;
}

export interface CuiAutocompleteProps {
  modelValue: string;
  suggestions: CuiAutocompleteSuggestion[];
  placeholder?: string;
  disabled?: boolean;
  clearable?: boolean;
}

export interface CuiAutocompleteEmits {
  'update:modelValue': [value: string];
  'select': [item: any];
}
