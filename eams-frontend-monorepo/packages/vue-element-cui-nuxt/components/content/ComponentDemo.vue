<template>
  <div class="component-demo border border-gray-200 dark:border-gray-800 rounded-lg overflow-hidden my-6">
    <!-- 标题和描述 -->
    <div v-if="title || description" class="px-6 py-4 bg-gray-50 dark:bg-gray-900 border-b border-gray-200 dark:border-gray-800">
      <h3 v-if="title" class="text-lg font-semibold text-gray-900 dark:text-gray-100 mb-1">
        {{ title }}
      </h3>
      <p v-if="description" class="text-sm text-gray-600 dark:text-gray-400">
        {{ description }}
      </p>
    </div>

    <!-- 预览和代码区域 -->
    <div class="grid grid-cols-1 lg:grid-cols-2 gap-0">
      <!-- 预览区域 -->
      <div class="preview-area p-6 bg-white dark:bg-gray-950 border-b lg:border-b-0 lg:border-r border-gray-200 dark:border-gray-800">
        <div class="preview-content">
          <ClientOnly>
            <slot name="preview" />
          </ClientOnly>
        </div>
      </div>

      <!-- 代码区域 -->
      <div class="code-area bg-gray-50 dark:bg-gray-900">
        <div class="flex items-center justify-between px-4 py-2 border-b border-gray-200 dark:border-gray-800">
          <span class="text-xs font-medium text-gray-600 dark:text-gray-400">代码示例</span>
          <button
            @click="toggleCode"
            class="text-xs text-gray-600 dark:text-gray-400 hover:text-gray-900 dark:hover:text-gray-100 transition-colors"
          >
            {{ isCodeVisible ? '收起' : '展开' }}
          </button>
        </div>
        <div v-show="isCodeVisible" class="code-content overflow-auto max-h-96">
          <slot name="code" />
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'

defineProps<{
  title?: string
  description?: string
}>()

const isCodeVisible = ref(true)

const toggleCode = () => {
  isCodeVisible.value = !isCodeVisible.value
}
</script>

<style scoped>
.component-demo {
  @apply shadow-sm;
}

.preview-area {
  min-height: 200px;
}

.code-area :deep(pre) {
  @apply m-0 rounded-none;
}

.code-area :deep(code) {
  @apply text-sm;
}

/* 响应式布局 */
@media (max-width: 1023px) {
  .grid {
    grid-template-columns: 1fr;
  }

  .preview-area {
    border-right: none;
    border-bottom: 1px solid;
  }
}
</style>
