<template>
	<finance-list-page :config="courseRewardConfig" />
</template>

<script setup lang="ts">
import FinanceListPage from './components/FinanceListPage.vue'
import { courseRewardConfig } from './shared'
</script>
