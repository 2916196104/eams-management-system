<template>
	<SystemAnnouncementPage :config="internalAnnouncementConfig" />
</template>

<script setup lang="ts">
import SystemAnnouncementPage from "./components/SystemAnnouncementPage.vue";
import { internalAnnouncementConfig } from "./shared";
</script>
