# vue-element-cui（历史归档）

vue-element-cui 是一个基于 element ui 的组件包，实现了 json 控制页面内容显示的功能，支持通过 json 配置并渲染生成表格，表单，提示框等多种组件。

> **当前状态**：历史归档（`Vue 2 + Element UI + vue-cli`），不作为当前业务主线依赖。
>
> **推荐替代**：`packages/vue-element-cui`（Vue 3 + Element Plus 版本）。

## 何时使用这个目录

- 对照旧实现做功能迁移
- 排查历史行为差异
- 回溯旧页面对 JSON 渲染逻辑的实现方式

## 不建议做的事情

- 不要在新业务里继续基于该目录开发新功能
- 不要将该目录作为当前发布产物来源
- 不要把这里的依赖版本（如旧 `sass`、`vue-cli`）直接迁入新包

## 用法

拷贝 src/components 里的 cui 到相同的项目目录位置。
在 main.js 中，加入 cui 组件：import "./components/cui"
示例代码：

```plain
// 引入cui组件
import "./components/cui"
import './components/cui/style/index.scss'
```

## 演示

宏之博教务系统采用了 CUI 组件：http://erp2.hzb-it.com

## 文档

请查阅 WIKI: https://gitee.com/ryan1981/vue-element-cui/wikis

## 效果

![输入图片说明](%E5%BE%AE%E4%BF%A1%E6%88%AA%E5%9B%BE_20211228170609.png)

![输入图片说明](%E5%BE%AE%E4%BF%A1%E6%88%AA%E5%9B%BE_20211228170731.png)

## 历史脚本（仅供参考）

```bash
pnpm --dir old/vue-element-cui serve
pnpm --dir old/vue-element-cui build
pnpm --dir old/vue-element-cui lint
```

## 迁移建议

若需要继续演进组件能力，请在 `packages/vue-element-cui` 中实现，并同步维护文档站 `packages/vue-element-cui-nuxt`。
