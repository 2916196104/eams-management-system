<template>
	<NuxtLink :to="to" :target="target">
		<slot />
	</NuxtLink>
</template>

<script setup lang="ts">
defineProps<{
	to?: string;
	target?: string;
}>();
</script>
