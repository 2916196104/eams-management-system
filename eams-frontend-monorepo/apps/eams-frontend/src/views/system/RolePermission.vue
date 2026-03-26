<template>
	<SystemRolePermissionPage :config="rolePermissionConfig" />
</template>

<script setup lang="ts">
import SystemRolePermissionPage from "./components/SystemRolePermissionPage.vue";
import { rolePermissionConfig } from "./shared";
</script>
