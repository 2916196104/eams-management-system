<template>
	<SystemSettingsPage :config="systemSettingsConfig" />
</template>

<script setup lang="ts">
import SystemSettingsPage from "./components/SystemSettingsPage.vue";
import { systemSettingsConfig } from "./shared";
</script>
