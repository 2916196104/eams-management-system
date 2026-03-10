<template>
  <div class="min-h-screen bg-gray-50">
    <div class="flex">
      <!-- Sidebar -->
      <aside class="w-64 bg-white border-r border-gray-200 min-h-screen sticky top-0 overflow-y-auto">
        <div class="p-6">
          <NuxtLink to="/" class="text-2xl font-bold text-blue-600 hover:text-blue-700">
            Vue Element CUI
          </NuxtLink>
        </div>
        <nav class="px-4 pb-6">
          <div class="space-y-1">
            <NavSection title="指南">
              <NavLink to="/docs/getting-started" label="快速开始" />
              <NavLink to="/docs/installation" label="安装" />
              <NavLink to="/docs/usage" label="使用方法" />
            </NavSection>

            <NavSection title="核心组件">
              <NavLink to="/docs/components/table" label="CuiTable 表格" />
              <NavLink to="/docs/components/form" label="CuiForm 表单" />
              <NavLink to="/docs/components/search" label="CuiSearch 搜索" />
              <NavLink to="/docs/components/dialog-form" label="CuiDialogForm 弹窗表单" />
            </NavSection>

            <NavSection title="功能组件">
              <NavLink to="/docs/components/upload" label="CuiUpload 上传" />
              <NavLink to="/docs/components/tree" label="CuiTree 树形" />
              <NavLink to="/docs/components/select" label="CuiSelect 选择器" />
            </NavSection>

            <NavSection title="表单控件">
              <NavLink to="/docs/components/input" label="CuiInput 输入框" />
              <NavLink to="/docs/components/date-picker" label="CuiDatePicker 日期选择" />
              <NavLink to="/docs/components/cascader" label="CuiCascader 级联选择" />
            </NavSection>
          </div>
        </nav>
      </aside>

      <!-- Main Content -->
      <main class="flex-1">
        <div class="max-w-4xl mx-auto px-8 py-12">
          <ContentDoc>
            <template #not-found>
              <div class="text-center py-16">
                <h1 class="text-4xl font-bold text-gray-900 mb-4">页面未找到</h1>
                <p class="text-gray-600 mb-8">抱歉，您访问的文档页面不存在。</p>
                <NuxtLink
                  to="/docs/getting-started"
                  class="inline-block bg-blue-600 hover:bg-blue-700 text-white font-medium px-6 py-3 rounded-md transition-colors"
                >
                  返回快速开始
                </NuxtLink>
              </div>
            </template>
          </ContentDoc>
        </div>
      </main>
    </div>
  </div>
</template>

<script setup lang="ts">
definePageMeta({
  layout: false
})
</script>
