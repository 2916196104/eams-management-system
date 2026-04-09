# 杂项提示词

## 001 <!-- TODO: --> 更新 AI 记忆文档

AI 记忆文档应该适当更新，说明清楚本项目目前的 monorepo 项目架构，简单说明其架构即可。

## 002 <!-- 已完成 --> 增加 prettier 配置，避免格式化误伤了 `packages\vue-element-cui-nuxt\package.json` 项目的 nuxt content 文档格式，避免出现 icon 渲染错误

在 prettier.config.mjs 内增加对 packages\vue-element-cui-nuxt\package.json 文档的忽略。不增加格式化。

是 prettier 的格式化导致这些文档出错了。

另外，给这些文档增加关于 prettier 的格式化忽略配置

### 01 记录经验教训

在本次任务内，我们走了很多弯路，遇到了很多困难，请你及时在 `.claude\skills\fix-bug\record-bug-fix-memory\SKILL.md` 这款技能内，记录我们遭遇的 bug，和出现的思维误区，以及解决方案。我们真的不能再 nuxt 项目启动上，反复出现障碍了。

随后，请你及时使用本地记忆 MCP，完成经验教训的总结和记录。
