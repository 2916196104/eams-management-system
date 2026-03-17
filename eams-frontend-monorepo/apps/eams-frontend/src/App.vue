<template>
  <!-- 全屏加载动画 -->
  <section v-loading.fullscreen.lock="false"></section>
  <router-view />
</template>
