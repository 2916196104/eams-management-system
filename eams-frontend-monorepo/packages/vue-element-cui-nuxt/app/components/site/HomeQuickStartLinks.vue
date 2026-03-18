<template>
	<div class="grid gap-4 md:grid-cols-2">
		<NuxtLink
			v-for="entry in entries"
			:key="entry.to"
			:to="entry.to"
			class="rounded-2xl border border-border/80 bg-background/80 p-4 transition hover:-translate-y-0.5 hover:border-sky-300 hover:shadow-sm dark:hover:border-sky-800"
		>
			<div class="flex items-start justify-between gap-3">
				<div class="space-y-2">
					<p class="text-sm font-semibold text-foreground">
						{{ entry.title }}
					</p>
					<p class="text-sm leading-6 text-muted-foreground">
						{{ entry.description }}
					</p>
				</div>
				<Icon :name="entry.icon" class="mt-1 h-4 w-4 text-muted-foreground" />
			</div>
		</NuxtLink>
	</div>
</template>

<script setup lang="ts">
defineProps<{
	entries: Array<{
		title: string;
		description: string;
		to: string;
		icon: string;
	}>;
}>();
</script>
