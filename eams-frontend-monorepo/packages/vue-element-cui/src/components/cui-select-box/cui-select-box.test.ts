import { describe, test, expect } from 'vitest';
import { mount } from '@vue/test-utils';
import { ElPopover, ElInput } from 'element-plus';
import CuiSelectBox from '../cui-select-box.vue';

describe('CuiSelectBox', () => {
  const defaultProps = {
    modelValue: '',
    type: 'course',
  };

  test('renders select box', () => {
    const wrapper = mount(CuiSelectBox, {
      props: defaultProps,
      global: {
        components: {
          ElPopover,
          ElInput,
        },
      },
    });

    expect(wrapper.find('.el-input').exists()).toBe(true);
  });

  test('emits update:modelValue on submit', async () => {
    const wrapper = mount(CuiSelectBox, {
      props: defaultProps,
      global: {
        components: {
          ElPopover,
          ElInput,
        },
      },
    });

    const selectedItems = [
      { id: '1', label: 'Item 1' },
      { id: '2', label: 'Item 2' },
    ];

    await wrapper.vm.handleSubmit(selectedItems);

    expect(wrapper.emitted('update:modelValue')).toBeTruthy();
    expect(wrapper.emitted('submit')).toBeTruthy();
  });

  test('respects limit of 1', async () => {
    const wrapper = mount(CuiSelectBox, {
      props: {
        ...defaultProps,
        limit: 1,
      },
      global: {
        components: {
          ElPopover,
          ElInput,
        },
      },
    });

    const selectedItems = [{ id: '1', label: 'Item 1' }];
    await wrapper.vm.handleSubmit(selectedItems);

    const emitted = wrapper.emitted('update:modelValue');
    expect(emitted?.[0]?.[0]).toBe('1');
  });

  test('handles clear', async () => {
    const wrapper = mount(CuiSelectBox, {
      props: defaultProps,
      global: {
        components: {
          ElPopover,
          ElInput,
        },
      },
    });

    await wrapper.vm.handleClear();

    expect(wrapper.emitted('update:modelValue')).toBeTruthy();
    expect(wrapper.vm.displayLabel).toBe('');
  });

  test('respects disabled prop', () => {
    const wrapper = mount(CuiSelectBox, {
      props: {
        ...defaultProps,
        disabled: true,
      },
      global: {
        components: {
          ElPopover,
          ElInput,
        },
      },
    });

    expect(wrapper.vm.$props.disabled).toBe(true);
  });
});
