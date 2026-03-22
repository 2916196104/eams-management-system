<template>
	<finance-list-page :config="requestManagementConfig" />
</template>

<script setup lang="ts">
import FinanceListPage from './components/FinanceListPage.vue'
import { requestManagementConfig } from './shared'
</script>
