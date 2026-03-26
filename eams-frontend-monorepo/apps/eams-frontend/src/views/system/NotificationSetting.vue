<template>
	<SystemNotificationPage :config="notificationSettingConfig" />
</template>

<script setup lang="ts">
import SystemNotificationPage from "./components/SystemNotificationPage.vue";
import { notificationSettingConfig } from "./shared";
</script>
