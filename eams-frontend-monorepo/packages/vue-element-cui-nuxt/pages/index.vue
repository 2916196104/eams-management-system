<template>
  <div class="min-h-screen bg-gradient-to-br from-blue-50 to-indigo-100">
    <div class="container mx-auto px-4 py-16">
      <!-- Header -->
      <header class="text-center mb-16">
        <h1 class="text-5xl font-bold text-gray-900 mb-4">
          Vue Element CUI
        </h1>
        <p class="text-xl text-gray-600 max-w-2xl mx-auto">
          基于 Element Plus 的企业级 Vue 3 组件库，提供高质量的业务组件和最佳实践
        </p>
      </header>

      <!-- Quick Start -->
      <div class="max-w-4xl mx-auto mb-16">
        <div class="bg-white rounded-lg shadow-lg p-8">
          <h2 class="text-2xl font-semibold text-gray-900 mb-4">快速开始</h2>
          <div class="space-y-4">
            <div>
              <h3 class="text-lg font-medium text-gray-700 mb-2">安装</h3>
              <pre class="bg-gray-900 text-gray-100 p-4 rounded-md overflow-x-auto"><code>pnpm add @eams/vue-element-cui</code></pre>
            </div>
            <div>
              <NuxtLink
                to="/docs/getting-started"
                class="inline-block bg-blue-600 hover:bg-blue-700 text-white font-medium px-6 py-3 rounded-md transition-colors"
              >
                查看完整文档 →
              </NuxtLink>
            </div>
          </div>
        </div>
      </div>

      <!-- Component Preview -->
      <div class="max-w-6xl mx-auto">
        <h2 class="text-3xl font-bold text-gray-900 mb-8 text-center">核心组件</h2>
        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          <ComponentCard
            title="CuiTable"
            description="功能强大的数据表格组件，支持分页、排序、筛选等"
            icon="📊"
          />
          <ComponentCard
            title="CuiForm"
            description="灵活的表单组件，支持动态配置和验证"
            icon="📝"
          />
          <ComponentCard
            title="CuiSearch"
            description="高级搜索组件，支持多条件组合查询"
            icon="🔍"
          />
          <ComponentCard
            title="CuiDialogForm"
            description="弹窗表单组件，简化对话框表单开发"
            icon="💬"
          />
          <ComponentCard
            title="CuiUpload"
            description="文件上传组件，支持多种上传方式"
            icon="📤"
          />
          <ComponentCard
            title="CuiTree"
            description="树形组件，支持懒加载和虚拟滚动"
            icon="🌲"
          />
        </div>
      </div>

      <!-- Footer -->
      <footer class="text-center mt-16 text-gray-600">
        <p>© 2026 EAMS Frontend Team</p>
      </footer>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({
  layout: false
})
</script>
