<template>
	<finance-list-page :config="paymentManagementConfig" />
</template>

<script setup lang="ts">
import FinanceListPage from './components/FinanceListPage.vue'
import { paymentManagementConfig } from './shared'
</script>
