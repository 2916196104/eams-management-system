# 2026-03-12 Vue Element CUI Nuxt 详细迁移计划

## 执行概览

本文档提供了从 @nuxt/ui-pro 迁移到 @nuxt-themes/docus 的完整、可执行的迁移计划。

**迁移范围:** `packages/vue-element-cui-nuxt`
**预计工作量:** 4-6 小时
**风险等级:** 中等（高风险项可控）

---

## 第一部分：依赖变更清单

### 1.1 需要删除的依赖

```json
{
  "dependencies": {
    "❌ @nuxt/ui-pro": "^1.4.4"
  },
  "devDependencies": {}
}
```

**删除原因:** Docus 主题已包含所有必要的 UI 组件和样式。

### 1.2 需要保留的依赖

```json
{
  "dependencies": {
    "✅ @eams/vue-element-cui": "workspace:*",
    "✅ @nuxt/content": "^2.13.4",
    "✅ nuxt": "^3.15.1",
    "✅ vue": "^3.5.13"
  },
  "devDependencies": {
    "✅ @element-plus/icons-vue": "^2.3.2",
    "✅ @nuxt/types": "^2.18.1",
    "✅ element-plus": "^2.13.5",
    "✅ typescript": "^5.7.3",
    "✅ vue-tsc": "^3.2.5"
  }
}
```

**保留原因:** 这些依赖是项目的核心依赖，与 Docus 兼容。

### 1.3 需要添加的依赖

```json
{
  "dependencies": {
    "➕ @nuxt-themes/docus": "^1.x.x"
  }
}
```

**添加原因:** Docus 是新的文档主题框架。

### 1.4 需要移除的模块

在 `nuxt.config.ts` 中：

```typescript
// ❌ 删除
modules: ['@nuxt/content', '@nuxt/ui'],

// ✅ 改为
modules: ['@nuxt/content'],
```

**原因:** Docus 会自动加载 @nuxt/ui，无需显式声明。

### 1.5 依赖变更执行步骤

```bash
# 步骤 1: 删除 @nuxt/ui-pro
pnpm remove @nuxt/ui-pro

# 步骤 2: 添加 @nuxt-themes/docus
pnpm add -D @nuxt-themes/docus

# 步骤 3: 重新安装依赖
pnpm install

# 步骤 4: 验证依赖树
pnpm list
```

---

## 第二部分：配置文件修改清单

### 2.1 nuxt.config.ts 修改

**当前配置:**
```typescript
export default defineNuxtConfig({
  extends: ['@nuxt/ui-pro'],

  modules: ['@nuxt/content', '@nuxt/ui'],

  vite: {
    optimizeDeps: {
      include: ['@eams/vue-element-cui']
    },
    css: {
      preprocessorMaxWorkers: true,
      postcss: {
        plugins: []
      }
    },
    build: {
      cssCodeSplit: true
    }
  },

  content: {
    highlight: {
      theme: {
        default: 'github-light',
        dark: 'github-dark'
      },
      preload: ['vue', 'typescript', 'javascript', 'bash']
    }
  },

  components: [
    {
      path: '~/components',
      pathPrefix: false
    }
  ],

  compatibilityDate: '2024-11-01',

  devtools: { enabled: true }
})
```

**修改后配置:**
```typescript
export default defineNuxtConfig({
  extends: ['@nuxt-themes/docus'],  // ✅ 改为 Docus

  modules: ['@nuxt/content'],  // ✅ 移除 @nuxt/ui

  vite: {
    optimizeDeps: {
      include: ['@eams/vue-element-cui']
    },
    css: {
      preprocessorMaxWorkers: true,
      postcss: {
        plugins: []
      }
    },
    build: {
      cssCodeSplit: true
    }
  },

  content: {
    highlight: {
      theme: {
        default: 'github-light',
        dark: 'github-dark'
      },
      preload: ['vue', 'typescript', 'javascript', 'bash']
    }
  },

  components: [
    {
      path: '~/components',
      pathPrefix: false
    }
  ],

  compatibilityDate: '2024-11-01',

  devtools: { enabled: true }
})
```

**修改项:**
- Line 2: `extends: ['@nuxt/ui-pro']` → `extends: ['@nuxt-themes/docus']`
- Line 4: `modules: ['@nuxt/content', '@nuxt/ui']` → `modules: ['@nuxt/content']`

### 2.2 app.config.ts 修改

**当前配置:**
```typescript
export default defineAppConfig({
  ui: {
    primary: 'green',
    gray: 'slate',
    icons: {
      dark: 'i-heroicons-moon-20-solid',
      light: 'i-heroicons-sun-20-solid',
      search: 'i-heroicons-magnifying-glass-20-solid',
      external: 'i-heroicons-arrow-up-right-20-solid',
      chevron: 'i-heroicons-chevron-down-20-solid',
      hash: 'i-heroicons-hashtag-20-solid'
    }
  }
})
```

**修改后配置:**
```typescript
export default defineAppConfig({
  docus: {
    title: 'Vue Element CUI',
    description: '企业级 Vue 3 组件库，基于 Element Plus 封装',
    image: '/cover.jpg',
    socials: {
      github: 'https://github.com/your-org/vue-element-cui'
    },
    header: {
      logo: true,
      showLinkIcon: true,
      exclude: []
    },
    aside: {
      level: 0,
      collapsed: false
    },
    footer: {
      credits: 'EAMS Frontend Team',
      iconLinks: []
    }
  }
})
```

**修改项:**
- 命名空间从 `ui.*` 改为 `docus.*`
- 配置项从 UI 主题改为 Docus 文档配置
- 添加文档标题、描述、社交链接等

**可选配置项:**
```typescript
// 如需保持绿色主题，可在 Docus 配置中添加：
docus: {
  // ... 其他配置
  colorMode: 'light',  // 或 'dark'
  // 使用 CSS 变量覆盖主题颜色
}
```

### 2.3 package.json 修改

**当前 dependencies:**
```json
{
  "dependencies": {
    "@eams/vue-element-cui": "workspace:*",
    "@nuxt/content": "^2.13.4",
    "@nuxt/ui-pro": "^1.4.4",
    "nuxt": "^3.15.1",
    "vue": "^3.5.13"
  }
}
```

**修改后 dependencies:**
```json
{
  "dependencies": {
    "@eams/vue-element-cui": "workspace:*",
    "@nuxt/content": "^2.13.4",
    "nuxt": "^3.15.1",
    "vue": "^3.5.13"
  }
}
```

**修改项:**
- 删除 `"@nuxt/ui-pro": "^1.4.4"`

**devDependencies 保持不变:**
```json
{
  "devDependencies": {
    "@element-plus/icons-vue": "^2.3.2",
    "@nuxt/types": "^2.18.1",
    "element-plus": "^2.13.5",
    "typescript": "^5.7.3",
    "vue-tsc": "^3.2.5"
  }
}
```

---

## 第三部分：文件删除/创建/修改清单

### 3.1 需要删除的文件

| 文件路径 | 原因 | 优先级 |
|---------|------|--------|
| `packages/vue-element-cui-nuxt/layouts/default.vue` | Docus 提供默认布局 | 高 |
| `packages/vue-element-cui-nuxt/pages/[...slug].vue` | Docus 自动生成路由 | 高 |

**删除步骤:**
```bash
# 删除布局文件
rm packages/vue-element-cui-nuxt/layouts/default.vue

# 删除页面文件
rm packages/vue-element-cui-nuxt/pages/[...slug].vue
```

### 3.2 需要保留的文件

| 文件/目录 | 说明 | 修改需求 |
|----------|------|--------|
| `content/` | 所有 markdown 文档 | 无需修改 |
| `components/ComponentCard.vue` | 自定义组件 | 无需修改 |
| `components/NavLink.vue` | 自定义组件 | 无需修改 |
| `components/NavSection.vue` | 自定义组件 | 无需修改 |
| `components/content/ComponentDemo.vue` | MDC 组件 | 无需修改 |
| `plugins/vue-element-cui.ts` | 插件 | 无需修改 |
| `tsconfig.json` | TypeScript 配置 | 无需修改 |
| `.gitignore` | Git 配置 | 无需修改 |

### 3.3 需要修改的文件

| 文件路径 | 修改内容 | 优先级 |
|---------|--------|--------|
| `nuxt.config.ts` | 更新 extends 和 modules | 高 |
| `app.config.ts` | 更新配置命名空间 | 高 |
| `package.json` | 删除 @nuxt/ui-pro | 高 |

### 3.4 可选创建的文件

根据 Docus 的最佳实践，可选创建以下文件来增强文档站点：

```
packages/vue-element-cui-nuxt/
├── public/
│   └── cover.jpg              # 文档封面图片
├── app.vue                    # 已存在，无需修改
└── nuxt.config.ts             # 已修改
```

---

## 第四部分：迁移步骤顺序

### Phase 1: 准备阶段（5-10 分钟）

**步骤 1.1: 创建迁移分支**
```bash
cd packages/vue-element-cui-nuxt
git checkout -b feat/migrate-to-docus
```

**步骤 1.2: 备份当前状态**
```bash
# 记录当前的 git 状态
git status
git log --oneline -5
```

**步骤 1.3: 验证当前项目可运行**
```bash
pnpm run dev
# 验证开发服务器启动成功，然后 Ctrl+C 停止
```

### Phase 2: 依赖更新（10-15 分钟）

**步骤 2.1: 删除 @nuxt/ui-pro**
```bash
pnpm remove @nuxt/ui-pro
```

**步骤 2.2: 添加 @nuxt-themes/docus**
```bash
pnpm add -D @nuxt-themes/docus
```

**步骤 2.3: 重新安装依赖**
```bash
pnpm install
```

**步骤 2.4: 验证依赖安装**
```bash
pnpm list | grep docus
pnpm list | grep ui-pro  # 应该没有输出
```

### Phase 3: 配置文件修改（10-15 分钟）

**步骤 3.1: 修改 nuxt.config.ts**
- 打开文件: `packages/vue-element-cui-nuxt/nuxt.config.ts`
- 修改 Line 2: `extends: ['@nuxt/ui-pro']` → `extends: ['@nuxt-themes/docus']`
- 修改 Line 4: `modules: ['@nuxt/content', '@nuxt/ui']` → `modules: ['@nuxt/content']`
- 保存文件

**步骤 3.2: 修改 app.config.ts**
- 打开文件: `packages/vue-element-cui-nuxt/app.config.ts`
- 替换整个文件内容为新的 Docus 配置
- 保存文件

**步骤 3.3: 验证配置文件语法**
```bash
# 检查 TypeScript 编译错误
pnpm run build 2>&1 | head -20
```

### Phase 4: 文件删除（5 分钟）

**步骤 4.1: 删除 layouts/default.vue**
```bash
rm packages/vue-element-cui-nuxt/layouts/default.vue
```

**步骤 4.2: 删除 pages/[...slug].vue**
```bash
rm packages/vue-element-cui-nuxt/pages/[...slug].vue
```

**步骤 4.3: 验证文件删除**
```bash
ls -la packages/vue-element-cui-nuxt/layouts/
ls -la packages/vue-element-cui-nuxt/pages/
# 两个目录应该为空或不存在
```

### Phase 5: 验证阶段（15-20 分钟）

**步骤 5.1: 启动开发服务器**
```bash
pnpm run dev
```

**预期输出:**
```
✔ Nuxt app built in XXXms
ℹ Local:    http://localhost:3000
```

**步骤 5.2: 验证首页渲染**
- 打开浏览器: http://localhost:3000
- 检查页面是否正确加载
- 检查导航菜单是否显示
- 检查搜索功能是否可用

**步骤 5.3: 验证组件文档页面**
- 点击导航中的"组件"链接
- 验证组件列表是否显示
- 点击某个组件（如 Table）
- 验证组件文档是否正确渲染
- 验证代码示例是否显示

**步骤 5.4: 验证 MDC 组件**
- 检查 `::component-demo` 组件是否正确渲染
- 检查 `::callout` 组件是否正确渲染
- 检查 `::code-group` 组件是否正确渲染
- 检查 `::card-group` 和 `::card` 组件是否正确渲染

**步骤 5.5: 验证样式和主题**
- 检查页面样式是否正确
- 检查深色模式切换是否工作
- 检查响应式布局是否正确

**步骤 5.6: 验证搜索功能**
- 点击搜索按钮
- 输入搜索关键词（如 "table"）
- 验证搜索结果是否显示

**步骤 5.7: 检查浏览器控制台**
- 打开浏览器开发者工具 (F12)
- 检查 Console 标签是否有错误
- 检查 Network 标签是否有失败的请求

### Phase 6: 优化阶段（可选，10-20 分钟）

**步骤 6.1: 调整 Docus 配置**
- 根据需要调整 `app.config.ts` 中的 Docus 配置
- 例如: 添加社交链接、调整导航结构等

**步骤 6.2: 自定义样式（如需要）**
- 如需保持绿色主题，创建 `app.vue` 或 CSS 文件
- 使用 CSS 变量覆盖 Docus 的默认颜色

**步骤 6.3: 性能测试**
```bash
# 构建生产版本
pnpm run build

# 预览生产版本
pnpm run preview
```

### Phase 7: 提交和清理（5-10 分钟）

**步骤 7.1: 提交更改**
```bash
git add -A
git commit -m "feat(docs): migrate from @nuxt/ui-pro to @nuxt-themes/docus"
```

**步骤 7.2: 推送分支**
```bash
git push origin feat/migrate-to-docus
```

**步骤 7.3: 创建 Pull Request**
- 在 GitHub 上创建 PR
- 添加描述和相关链接
- 请求代码审查

---

## 第五部分：验证检查清单

### 构建验证

- [ ] `pnpm install` 成功完成，无错误
- [ ] `pnpm run build` 成功完成，无错误
- [ ] 构建输出大小合理（无异常增长）

### 开发服务器验证

- [ ] `pnpm run dev` 启动成功
- [ ] 开发服务器在 http://localhost:3000 可访问
- [ ] 浏览器控制台无错误

### 页面渲染验证

- [ ] 首页正确加载和渲染
- [ ] 导航菜单显示正确
- [ ] 所有页面链接可点击
- [ ] 页面内容正确显示

### 功能验证

- [ ] 搜索功能正常工作
- [ ] 深色模式切换正常工作
- [ ] 代码示例正确渲染
- [ ] 所有 MDC 组件正确渲染

### 样式验证

- [ ] 页面样式正确应用
- [ ] 响应式布局在不同屏幕尺寸下正确
- [ ] 颜色主题正确应用
- [ ] 字体和排版正确

### 性能验证

- [ ] 页面加载时间合理
- [ ] 没有明显的性能问题
- [ ] 生产构建大小合理

---

## 第六部分：故障排除指南

### 问题 1: 构建失败，提示找不到 @nuxt-themes/docus

**症状:**
```
Error: Cannot find module '@nuxt-themes/docus'
```

**解决方案:**
```bash
# 清除 node_modules 和 lock 文件
rm -rf node_modules pnpm-lock.yaml

# 重新安装
pnpm install
```

### 问题 2: 开发服务器启动失败

**症状:**
```
Error: [nuxt] A fatal error occurred: ...
```

**解决方案:**
1. 检查 `nuxt.config.ts` 中的 `extends` 配置是否正确
2. 检查 `app.config.ts` 中的 `docus` 配置是否有语法错误
3. 清除 `.nuxt` 缓存目录: `rm -rf .nuxt`
4. 重新启动开发服务器

### 问题 3: 页面无法加载，显示 404

**症状:**
- 访问 http://localhost:3000 显示 404 错误

**解决方案:**
1. 检查 `content/` 目录是否存在
2. 检查 `content/0.index.md` 是否存在
3. 检查 `nuxt.config.ts` 中的 `modules` 是否包含 `@nuxt/content`
4. 重新启动开发服务器

### 问题 4: 样式丢失或不正确

**症状:**
- 页面显示但样式不正确
- 颜色或布局不符合预期

**解决方案:**
1. 检查浏览器开发者工具中的 CSS 是否加载
2. 检查 `app.config.ts` 中的 Docus 配置
3. 清除浏览器缓存: Ctrl+Shift+Delete
4. 重新启动开发服务器

### 问题 5: 搜索功能不工作

**症状:**
- 点击搜索按钮无反应
- 搜索结果不显示

**解决方案:**
1. 检查浏览器控制台是否有错误
2. 检查 `@nuxt/content` 是否正确加载
3. 检查 `content/` 目录中的 markdown 文件是否有效
4. 重新启动开发服务器

---

## 第七部分：回滚计划

如果迁移过程中出现严重问题，可以按以下步骤回滚：

### 回滚步骤

```bash
# 步骤 1: 停止开发服务器
# Ctrl+C

# 步骤 2: 切换回主分支
git checkout main

# 步骤 3: 删除迁移分支
git branch -D feat/migrate-to-docus

# 步骤 4: 重新安装依赖
pnpm install

# 步骤 5: 验证项目状态
pnpm run dev
```

---

## 第八部分：预期结果

### 迁移前后对比

| 方面 | 迁移前 | 迁移后 |
|------|--------|--------|
| 主题框架 | @nuxt/ui-pro | @nuxt-themes/docus |
| 文档路由 | 手动定义 (pages/[...slug].vue) | 自动生成 |
| 布局 | 自定义 (layouts/default.vue) | Docus 提供 |
| 配置命名空间 | ui.* | docus.* |
| 依赖数量 | 5 个 dependencies | 4 个 dependencies |
| 文件数量 | 包含 layouts/ 和 pages/ | 无 layouts/ 和 pages/ |

### 迁移后的优势

1. **更轻量级** - 移除了 @nuxt/ui-pro，减少了依赖
2. **更专业** - Docus 是专为文档设计的主题
3. **更易维护** - 自动路由生成，无需手动管理
4. **更好的文档体验** - Docus 提供了更多文档特定的功能

---

## 第九部分：时间估算

| 阶段 | 预计时间 | 实际时间 |
|------|---------|---------|
| Phase 1: 准备 | 5-10 分钟 | _____ |
| Phase 2: 依赖更新 | 10-15 分钟 | _____ |
| Phase 3: 配置修改 | 10-15 分钟 | _____ |
| Phase 4: 文件删除 | 5 分钟 | _____ |
| Phase 5: 验证 | 15-20 分钟 | _____ |
| Phase 6: 优化 | 10-20 分钟 | _____ |
| Phase 7: 提交 | 5-10 分钟 | _____ |
| **总计** | **60-95 分钟** | **_____ 分钟** |

---

## 第十部分：参考资源

- [Docus 官方文档](https://docus.dev)
- [Nuxt Content 文档](https://content.nuxt.com)
- [Nuxt 官方文档](https://nuxt.com)
- [@nuxt-themes/docus GitHub](https://github.com/nuxt-themes/docus)

---

## 附录：完整的文件修改示例

### 附录 A: nuxt.config.ts 完整修改

**文件位置:** `packages/vue-element-cui-nuxt/nuxt.config.ts`

```typescript
export default defineNuxtConfig({
  extends: ['@nuxt-themes/docus'],

  modules: ['@nuxt/content'],

  vite: {
    optimizeDeps: {
      include: ['@eams/vue-element-cui']
    },
    css: {
      preprocessorMaxWorkers: true,
      postcss: {
        plugins: []
      }
    },
    build: {
      cssCodeSplit: true
    }
  },

  content: {
    highlight: {
      theme: {
        default: 'github-light',
        dark: 'github-dark'
      },
      preload: ['vue', 'typescript', 'javascript', 'bash']
    }
  },

  components: [
    {
      path: '~/components',
      pathPrefix: false
    }
  ],

  compatibilityDate: '2024-11-01',

  devtools: { enabled: true }
})
```

### 附录 B: app.config.ts 完整修改

**文件位置:** `packages/vue-element-cui-nuxt/app.config.ts`

```typescript
export default defineAppConfig({
  docus: {
    title: 'Vue Element CUI',
    description: '企业级 Vue 3 组件库，基于 Element Plus 封装',
    image: '/cover.jpg',
    socials: {
      github: 'https://github.com/your-org/vue-element-cui'
    },
    header: {
      logo: true,
      showLinkIcon: true,
      exclude: []
    },
    aside: {
      level: 0,
      collapsed: false
    },
    footer: {
      credits: 'EAMS Frontend Team',
      iconLinks: []
    }
  }
})
```

### 附录 C: package.json 依赖部分修改

**文件位置:** `packages/vue-element-cui-nuxt/package.json`

```json
{
  "name": "@eams/vue-element-cui-nuxt",
  "version": "1.0.0",
  "type": "module",
  "private": true,
  "scripts": {
    "dev": "nuxt dev",
    "build": "nuxt build",
    "generate": "nuxt generate",
    "preview": "nuxt preview",
    "postinstall": "nuxt prepare"
  },
  "dependencies": {
    "@eams/vue-element-cui": "workspace:*",
    "@nuxt/content": "^2.13.4",
    "nuxt": "^3.15.1",
    "vue": "^3.5.13"
  },
  "devDependencies": {
    "@element-plus/icons-vue": "^2.3.2",
    "@nuxt-themes/docus": "^1.x.x",
    "@nuxt/types": "^2.18.1",
    "element-plus": "^2.13.5",
    "typescript": "^5.7.3",
    "vue-tsc": "^3.2.5"
  }
}
```

---

## 文档版本历史

| 版本 | 日期 | 作者 | 变更 |
|------|------|------|------|
| 1.0 | 2026-03-12 | project-analyzer | 初始版本 |
