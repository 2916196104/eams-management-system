// Vue Element CUI - 主入口文件
import type { App, Plugin } from 'vue';
import { CuiTable } from './components/cui-table';
import { CuiForm } from './components/cui-form';
import { CuiSearch } from './components/cui-search';

// 导出版本号
export const version: string = '1.0.0';

// 导出安装函数
export function install(app: App): void {
  // 注册组件
  app.component('CuiTable', CuiTable);
  app.component('CuiForm', CuiForm);
  app.component('CuiSearch', CuiSearch);
  console.log(`@eams/vue-element-cui v${version} installed`);
}

// 默认导出
const plugin: Plugin & { version: string } = {
  version: version,
  install: install,
};

export default plugin;

// 组件导出
export * from './components';
