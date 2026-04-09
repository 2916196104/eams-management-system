<template>
	<SystemDictionaryPage :config="dataDictionaryConfig" />
</template>

<script setup lang="ts">
import SystemDictionaryPage from "./components/SystemDictionaryPage.vue";
import { dataDictionaryConfig } from "./shared";
</script>
