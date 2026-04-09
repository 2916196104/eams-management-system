<template>
	<aside :data-tone="tone" :class="wrapperClass" class="my-6 rounded-2xl border px-4 py-4">
		<p v-if="title" class="text-sm font-semibold">
			{{ title }}
		</p>
		<div class="mt-2 text-sm leading-6">
			<slot />
		</div>
	</aside>
</template>

<script setup lang="ts">
import { computed } from "vue";

const props = withDefaults(
	defineProps<{
		title?: string;
		tone?: "info" | "warning" | "success";
	}>(),
	{
		tone: "info",
	},
);

const toneClassMap = {
	info: "border-sky-200/80 bg-sky-50/80 text-sky-950 dark:border-sky-900 dark:bg-sky-950/30 dark:text-sky-100",
	warning:
		"border-amber-200/80 bg-amber-50/80 text-amber-950 dark:border-amber-900 dark:bg-amber-950/30 dark:text-amber-100",
	success:
		"border-emerald-200/80 bg-emerald-50/80 text-emerald-950 dark:border-emerald-900 dark:bg-emerald-950/30 dark:text-emerald-100",
} as const;

const wrapperClass = computed(() => toneClassMap[props.tone]);
</script>
