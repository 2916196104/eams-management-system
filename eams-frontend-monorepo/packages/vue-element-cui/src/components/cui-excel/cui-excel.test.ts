import { describe, test, expect } from 'vitest';
import { mount } from '@vue/test-utils';
import { ElUpload, ElButton, ElIcon } from 'element-plus';
import CuiExcel from '../cui-excel.vue';
import { CuiDialog } from '../../cui-dialog';

describe('CuiExcel', () => {
  const defaultProps = {
    modelValue: true,
    uploadUrl: 'http://example.com/upload',
  };

  test('renders excel upload dialog', () => {
    const wrapper = mount(CuiExcel, {
      props: defaultProps,
      global: {
        components: {
          CuiDialog,
          ElUpload,
          ElButton,
          ElIcon,
        },
      },
    });

    expect(wrapper.find('.el-upload').exists()).toBe(true);
  });

  test('emits update:modelValue when dialog closes', async () => {
    const wrapper = mount(CuiExcel, {
      props: defaultProps,
      global: {
        components: {
          CuiDialog,
          ElUpload,
          ElButton,
          ElIcon,
        },
      },
    });

    await wrapper.vm.$emit('update:modelValue', false);
    expect(wrapper.emitted('update:modelValue')).toBeTruthy();
  });

  test('shows template download link when templateUrl provided', () => {
    const wrapper = mount(CuiExcel, {
      props: {
        ...defaultProps,
        templateUrl: 'http://example.com/template.xlsx',
      },
      global: {
        components: {
          CuiDialog,
          ElUpload,
          ElButton,
          ElIcon,
        },
      },
    });

    expect(wrapper.find('.template-download').exists()).toBe(true);
  });

  test('respects custom title', () => {
    const wrapper = mount(CuiExcel, {
      props: {
        ...defaultProps,
        title: '导入数据',
      },
      global: {
        components: {
          CuiDialog,
          ElUpload,
          ElButton,
          ElIcon,
        },
      },
    });

    expect(wrapper.vm.$props.title).toBe('导入数据');
  });

  test('handles upload success', async () => {
    const wrapper = mount(CuiExcel, {
      props: defaultProps,
      global: {
        components: {
          CuiDialog,
          ElUpload,
          ElButton,
          ElIcon,
        },
      },
    });

    const response = { code: 0, message: 'success' };
    await wrapper.vm.handleSuccess(response, {}, []);

    expect(wrapper.emitted('success')).toBeTruthy();
  });
});
