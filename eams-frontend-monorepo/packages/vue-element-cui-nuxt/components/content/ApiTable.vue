<template>
	<section class="my-8 rounded-2xl border border-border bg-card shadow-sm">
		<header v-if="title || description" class="border-b border-border/80 bg-muted/30 px-5 py-4">
			<h3 v-if="title" class="text-base font-semibold text-foreground">
				{{ title }}
			</h3>
			<p v-if="description" class="mt-1 text-sm text-muted-foreground">
				{{ description }}
			</p>
		</header>

		<div class="cui-api-table prose prose-sm max-w-none px-5 py-4 dark:prose-invert">
			<slot />
		</div>
	</section>
</template>

<script setup lang="ts">
defineProps<{
	title?: string;
	description?: string;
}>();
</script>
