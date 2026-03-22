<template>
	<finance-list-page :config="monthlyClassFeeConfig" />
</template>

<script setup lang="ts">
import FinanceListPage from './components/FinanceListPage.vue'
import { monthlyClassFeeConfig } from './shared'
</script>
