<template>
	<div class="my-6 grid gap-3 md:grid-cols-2">
		<section
			v-for="item in normalizedItems"
			:key="item.title"
			class="rounded-2xl border border-border bg-card px-4 py-4 shadow-sm"
		>
			<p class="text-sm font-semibold text-foreground">
				{{ item.title }}
			</p>
			<p v-if="item.description" class="mt-2 text-sm leading-6 text-muted-foreground">
				{{ item.description }}
			</p>
		</section>
	</div>
</template>

<script setup lang="ts">
import { computed } from "vue";

interface FeatureItem {
	title: string;
	description?: string;
}

const props = defineProps<{
	items: FeatureItem[] | string;
}>();

const normalizedItems = computed<FeatureItem[]>(() => {
	if (Array.isArray(props.items)) {
		return props.items;
	}

	if (typeof props.items !== "string" || !props.items.trim()) {
		return [];
	}

	try {
		const parsed = JSON.parse(props.items) as FeatureItem[];
		return Array.isArray(parsed) ? parsed : [];
	} catch {
		try {
			const parsed = Function(`"use strict"; return (${props.items});`)() as FeatureItem[];
			return Array.isArray(parsed) ? parsed : [];
		} catch {
			return [];
		}
	}
});
</script>
