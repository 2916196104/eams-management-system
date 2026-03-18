你改数据就能改菜单

- 菜单数据集中在 nav-data.ts
- 结构是：
  - 一级： { key, label, icon, children? , path? }
  - 二级： { key, label, path }
- 你只要改 label/icon/path/children ，左侧菜单会跟着变；同时路由也会自动生成（下面说）。
  路由跳转 + 顶部记录（标签页）

- 左侧导航组件： EamsNav.vue
  - 点击一级（有 children）会默认选中并触发第一个二级
  - 点击二级会触发 select 事件，Home 页收到后 router.push(path)
- 路由自动注册在 router/main/index.ts
  - 会读取 eamsNavItems ，把每个 path 都变成一个路由，并写入 meta.label
  - 顶部标签页的“记录”是通过全局路由守卫：只要路由有 meta.label 就会加入 tab（你项目原本就有这套逻辑）
- 主页面接入在 HomeView.vue
  - 左侧换成 EamsNav
  - 顶部继续用现有 el-tabs 记录打开页面
