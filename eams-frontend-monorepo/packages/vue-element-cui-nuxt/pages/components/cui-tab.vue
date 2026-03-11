<template>
  <div class="demo-page">
    <h1>CuiTab 组件演示</h1>

    <div class="demo-section">
      <h2>基础 Tab</h2>
      <cui-tab
        :tabs="basicTabs"
        :active-tab="activeTab1"
        @update:active-tab="activeTab1 = $event"
      />
    </div>

    <div class="demo-section">
      <h2>卡片类型 Tab</h2>
      <cui-tab
        :tabs="basicTabs"
        :active-tab="activeTab2"
        type="card"
        @update:active-tab="activeTab2 = $event"
      />
    </div>

    <div class="demo-section">
      <h2>可关闭的 Tab</h2>
      <cui-tab
        :tabs="closableTabs"
        :active-tab="activeTab3"
        :closable="true"
        @update:active-tab="activeTab3 = $event"
        @remove="handleRemoveTab"
      />
    </div>

    <div class="demo-section">
      <h2>动态添加/删除 Tab</h2>
      <div style="margin-bottom: 15px">
        <el-button @click="handleAddTab">添加 Tab</el-button>
      </div>
      <cui-tab
        :tabs="dynamicTabs"
        :active-tab="activeTab5"
        :closable="true"
        @update:active-tab="handleTabChange"
        @remove="handleRemoveDynamicTab"
      />
      <div style="margin-top: 15px; color: #666">
        当前激活的 Tab: {{ activeTab5 }}
      </div>
    </div>

    <div class="demo-section">
      <h2>带插槽的 Tab</h2>
      <cui-tab
        :tabs="slotTabs"
        :active-tab="activeTab4"
        @update:active-tab="activeTab4 = $event"
      >
        <template #tab-tab1>
          <div style="padding: 20px">
            <p>这是第一个 Tab 的自定义内容</p>
            <el-button>操作按钮</el-button>
          </div>
        </template>
        <template #tab-tab2>
          <div style="padding: 20px">
            <p>这是第二个 Tab 的自定义内容</p>
            <el-input placeholder="输入框" />
          </div>
        </template>
      </cui-tab>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ElButton, ElInput } from 'element-plus';
import { CuiTab } from '@packages/vue-element-cui';
import type { CuiTabItem } from '@packages/vue-element-cui';

const activeTab1 = ref('tab1');
const activeTab2 = ref('tab1');
const activeTab3 = ref('tab1');
const activeTab4 = ref('tab1');
const activeTab5 = ref('tab1');

const basicTabs: CuiTabItem[] = [
  { label: 'Tab 1', name: 'tab1', content: '这是第一个 Tab 的内容' },
  { label: 'Tab 2', name: 'tab2', content: '这是第二个 Tab 的内容' },
  { label: 'Tab 3', name: 'tab3', content: '这是第三个 Tab 的内容' },
];

const closableTabs = ref<CuiTabItem[]>([
  { label: 'Tab 1', name: 'tab1', content: '内容 1', closable: true },
  { label: 'Tab 2', name: 'tab2', content: '内容 2', closable: true },
  { label: 'Tab 3', name: 'tab3', content: '内容 3', closable: true },
]);

const slotTabs: CuiTabItem[] = [
  { label: 'Tab 1', name: 'tab1' },
  { label: 'Tab 2', name: 'tab2' },
];

const dynamicTabs = ref<CuiTabItem[]>([
  { label: 'Tab 1', name: 'tab1', content: '动态内容 1', closable: true },
  { label: 'Tab 2', name: 'tab2', content: '动态内容 2', closable: true },
]);

let tabIndex = 3;

const handleRemoveTab = (tabName: string) => {
  closableTabs.value = closableTabs.value.filter((tab) => tab.name !== tabName);
};

const handleAddTab = () => {
  const newTabName = `tab${tabIndex}`;
  dynamicTabs.value.push({
    label: `Tab ${tabIndex}`,
    name: newTabName,
    content: `动态内容 ${tabIndex}`,
    closable: true,
  });
  activeTab5.value = newTabName;
  tabIndex++;
};

const handleRemoveDynamicTab = (tabName: string) => {
  const tabs = dynamicTabs.value;
  const index = tabs.findIndex((tab) => tab.name === tabName);

  if (index !== -1) {
    // 如果删除的是当前激活的 tab，切换到相邻的 tab
    if (activeTab5.value === tabName) {
      const nextTab = tabs[index + 1] || tabs[index - 1];
      if (nextTab) {
        activeTab5.value = nextTab.name;
      }
    }
    dynamicTabs.value = tabs.filter((tab) => tab.name !== tabName);
  }
};

const handleTabChange = (tabName: string) => {
  activeTab5.value = tabName;
  console.log('Tab 切换到:', tabName);
};
</script>

<style scoped lang="scss">
.demo-page {
  padding: 20px;
}

.demo-section {
  margin-bottom: 30px;
  padding: 20px;
  border: 1px solid #ddd;
  border-radius: 4px;

  h2 {
    margin-top: 0;
    margin-bottom: 15px;
    font-size: 16px;
  }
}
</style>
