<script lang="ts" setup>
definePage({
  name: 'mine',
  layout: 'tabbar',
  style: {
    navigationBarTitleText: '我的',
    titleNView: false,
  },
})
// 个人信息
const { userInfo } = useUserStore()

// 获取路由实例
const router = useRouter()

// 页面跳转方法
function navigateTo(name: string) {
  router.push({
    name,
  })
}

// 打开链接
function openUrl(url: string) {
  window.open(url, '_blank')
}
</script>

<template>
  <view class="box-border">
    <!-- 个人信息 -->
    <view
      class="flex gap-10 flex-justify-between flex-items-center rounded-lg bg-white px-4 py-3 dark:bg-[var(--wot-dark-background2)]"
    >
      <view>
        <wd-avatar :text="userInfo.nickName" size="large" bg-color="#1E90FF" color="#fff" />
      </view>
      <view class="text-gray-500 dark:text-gray-300">
        <text class="block">
          昵称：{{ userInfo.nickName }}
        </text>
        <text class="block">
          手机：{{ userInfo.phone }}
        </text>
        <text>
          性别：{{ userInfo.sex }}
        </text>
      </view>
      <view>
        <wd-button type="primary" size="small" plain>
          编辑
        </wd-button>
      </view>
    </view>
    <!-- 基础设置 -->
    <title-block title="基础设置" transparent>
      <wd-cell-group border custom-class="rounded-2! overflow-hidden">
        <wd-cell title="🔮 设置主题" is-link @click="navigateTo('them')" />
      </wd-cell-group>
    </title-block>
    <!-- 使用示例参考 -->
    <title-block title="使用参考" transparent>
      <wd-cell-group border custom-class="rounded-2! overflow-hidden">
        <wd-cell title="🧩 WotUI 组件库" is-link @click="openUrl('https://wot-ui.cn/')" />
        <wd-cell title="🚦 Router 路由使用" is-link @click="openUrl('https://starter.wot-ui.cn/guide/router.html')" />
        <wd-cell title="🌐 Alova 网络请求" is-link @click="openUrl('https://starter.wot-ui.cn/guide/request.html')" />
        <wd-cell title="🎨 Icon 图标" is-link @click="openUrl('https://starter.wot-ui.cn/guide/icons.html')" />
        <wd-cell title="✨ Unocss 原子化" is-link @click="openUrl('https://starter.wot-ui.cn/guide/styling.html')" />
        <wd-cell
          title="🍍 Pinia 持久化" is-link
          @click="openUrl('https://starter.wot-ui.cn/guide/state-management.html')"
        />
        <wd-cell title="💬 Fedback 反馈组件" is-link @click="openUrl('https://starter.wot-ui.cn/guide/feedback.html')" />
        <wd-cell title="📊 uni-echarts" is-link @click="openUrl('https://starter.wot-ui.cn/guide/uni-echarts.html')" />
      </wd-cell-group>
    </title-block>
  </view>
</template>

<style scoped></style>
