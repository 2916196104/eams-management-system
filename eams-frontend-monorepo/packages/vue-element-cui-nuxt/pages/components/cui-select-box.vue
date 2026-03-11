<template>
  <div class="demo-container">
    <h1>CuiSelectBox 组件演示</h1>

    <section class="demo-section">
      <h2>基础选择容器</h2>
      <p class="description">CuiSelectBox 是一个选择容器组件，通过插槽自定义选择器内容</p>
      <CuiSelectBox
        v-model="basicValue"
        type="basic"
        placeholder="请选择项目"
        @submit="handleBasicSubmit"
      >
        <template #selector="{ condition }">
          <div class="selector-content">
            <h3>选择项目</h3>
            <div class="item-list">
              <div
                v-for="item in basicItems"
                :key="item.id"
                class="item"
                :class="{ selected: isSelected(basicValue, item.id) }"
                @click="selectItem(item, 'basic')"
              >
                {{ item.label }}
              </div>
            </div>
          </div>
        </template>
      </CuiSelectBox>
      <p class="result">当前值: {{ basicValue }}</p>
    </section>

    <section class="demo-section">
      <h2>单选模式 (limit=1)</h2>
      <p class="description">限制只能选择一个项目</p>
      <CuiSelectBox
        v-model="singleValue"
        type="single"
        :limit="1"
        placeholder="请选择一个项目"
        @submit="handleSingleSubmit"
      >
        <template #selector="{ condition }">
          <div class="selector-content">
            <h3>选择一个项目</h3>
            <div class="item-list">
              <div
                v-for="item in basicItems"
                :key="item.id"
                class="item"
                :class="{ selected: singleValue === item.id }"
                @click="selectSingleItem(item)"
              >
                {{ item.label }}
              </div>
            </div>
          </div>
        </template>
      </CuiSelectBox>
      <p class="result">当前值: {{ singleValue }}</p>
    </section>

    <section class="demo-section">
      <h2>多选模式</h2>
      <p class="description">可以选择多个项目，以逗号分隔</p>
      <CuiSelectBox
        v-model="multipleValue"
        type="multiple"
        placeholder="请选择多个项目"
        @submit="handleMultipleSubmit"
      >
        <template #selector="{ condition }">
          <div class="selector-content">
            <h3>选择多个项目</h3>
            <div class="item-list">
              <div
                v-for="item in basicItems"
                :key="item.id"
                class="item"
                :class="{ selected: isSelected(multipleValue, item.id) }"
                @click="toggleMultipleItem(item)"
              >
                <el-checkbox :model-value="isSelected(multipleValue, item.id)" />
                {{ item.label }}
              </div>
            </div>
            <div class="selector-footer">
              <el-button size="small" @click="confirmMultipleSelection">确定</el-button>
            </div>
          </div>
        </template>
      </CuiSelectBox>
      <p class="result">当前值: {{ multipleValue }}</p>
    </section>

    <section class="demo-section">
      <h2>禁用状态</h2>
      <CuiSelectBox
        v-model="disabledValue"
        type="disabled"
        disabled
        placeholder="禁用状态"
      >
        <template #selector>
          <div class="selector-content">
            <p>此选择器已禁用</p>
          </div>
        </template>
      </CuiSelectBox>
    </section>

    <section class="demo-section">
      <h2>带条件过滤</h2>
      <p class="description">通过 condition 属性传递过滤条件</p>
      <div class="filter-controls">
        <el-input
          v-model="filterKeyword"
          placeholder="输入关键词过滤"
          style="width: 200px; margin-bottom: 10px"
        />
      </div>
      <CuiSelectBox
        v-model="filteredValue"
        type="filtered"
        :condition="{ keyword: filterKeyword }"
        placeholder="请选择项目"
        @submit="handleFilteredSubmit"
      >
        <template #selector="{ condition }">
          <div class="selector-content">
            <h3>选择项目 (过滤: {{ condition.keyword || '无' }})</h3>
            <div class="item-list">
              <div
                v-for="item in filteredItems"
                :key="item.id"
                class="item"
                :class="{ selected: isSelected(filteredValue, item.id) }"
                @click="selectItem(item, 'filtered')"
              >
                {{ item.label }}
              </div>
            </div>
          </div>
        </template>
      </CuiSelectBox>
      <p class="result">当前值: {{ filteredValue }}</p>
    </section>
  </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue';
import { ElButton, ElCheckbox, ElInput, ElMessage } from 'element-plus';
import { CuiSelectBox } from '@eams/vue-element-cui';

const basicValue = ref('');
const singleValue = ref('');
const multipleValue = ref('');
const disabledValue = ref('1,2');
const filteredValue = ref('');
const filterKeyword = ref('');

const basicItems = [
  { id: '1', label: '项目 A' },
  { id: '2', label: '项目 B' },
  { id: '3', label: '项目 C' },
  { id: '4', label: '项目 D' },
  { id: '5', label: '项目 E' },
];

const selectedMultipleItems = ref<string[]>([]);

const filteredItems = computed(() => {
  if (!filterKeyword.value) return basicItems;
  return basicItems.filter(item =>
    item.label.toLowerCase().includes(filterKeyword.value.toLowerCase())
  );
});

const isSelected = (value: string, id: string) => {
  if (!value) return false;
  const ids = value.split(',');
  return ids.includes(id);
};

const selectItem = (item: any, type: string) => {
  if (type === 'basic') {
    basicValue.value = item.id;
  } else if (type === 'filtered') {
    filteredValue.value = item.id;
  }
};

const selectSingleItem = (item: any) => {
  singleValue.value = item.id;
};

const toggleMultipleItem = (item: any) => {
  const index = selectedMultipleItems.value.indexOf(item.id);
  if (index > -1) {
    selectedMultipleItems.value.splice(index, 1);
  } else {
    selectedMultipleItems.value.push(item.id);
  }
};

const confirmMultipleSelection = () => {
  multipleValue.value = selectedMultipleItems.value.join(',');
};

const handleBasicSubmit = (value: string | string[]) => {
  ElMessage.success(`基础选择提交: ${value}`);
};

const handleSingleSubmit = (value: string | string[]) => {
  ElMessage.success(`单选提交: ${value}`);
};

const handleMultipleSubmit = (value: string | string[]) => {
  ElMessage.success(`多选提交: ${value}`);
};

const handleFilteredSubmit = (value: string | string[]) => {
  ElMessage.success(`过滤选择提交: ${value}`);
};
</script>

<style scoped lang="scss">
.demo-container {
  padding: 20px;
  max-width: 800px;
  margin: 0 auto;

  h1 {
    margin-bottom: 30px;
    color: #333;
  }

  .demo-section {
    margin-bottom: 30px;
    padding: 20px;
    border: 1px solid #ddd;
    border-radius: 4px;

    h2 {
      margin-top: 0;
      margin-bottom: 10px;
      font-size: 16px;
      color: #666;
    }

    .description {
      margin-bottom: 15px;
      color: #999;
      font-size: 14px;
    }

    .result {
      margin-top: 10px;
      color: #999;
      font-size: 14px;
    }
  }
}

.selector-content {
  padding: 10px;

  h3 {
    margin: 0 0 10px 0;
    font-size: 14px;
    color: #333;
  }

  .item-list {
    max-height: 300px;
    overflow-y: auto;

    .item {
      padding: 10px;
      margin-bottom: 5px;
      border: 1px solid #ddd;
      border-radius: 4px;
      cursor: pointer;
      transition: all 0.3s;
      display: flex;
      align-items: center;
      gap: 8px;

      &:hover {
        background-color: #f5f5f5;
      }

      &.selected {
        background-color: #409eff;
        color: white;
        border-color: #409eff;
      }
    }
  }

  .selector-footer {
    margin-top: 10px;
    text-align: right;
  }
}

.filter-controls {
  margin-bottom: 10px;
}
</style>
