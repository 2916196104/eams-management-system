<template>
	<div class="mb-6">
		<h3 class="px-3 text-xs font-semibold text-gray-500 uppercase tracking-wider mb-2">
			{{ title }}
		</h3>
		<div class="space-y-1">
			<slot />
		</div>
	</div>
</template>

<script setup lang="ts">
defineProps<{
	title: string;
}>();
</script>
