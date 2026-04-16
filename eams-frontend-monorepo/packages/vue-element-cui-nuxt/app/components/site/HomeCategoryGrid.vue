<template>
	<div class="grid gap-4 md:grid-cols-2 xl:grid-cols-3">
		<NuxtLink
			v-for="category in categories"
			:key="category.to"
			:to="category.to"
			class="rounded-2xl border border-border bg-card p-5 transition hover:-translate-y-0.5 hover:border-sky-300 hover:shadow-sm dark:hover:border-sky-800"
		>
			<div class="flex items-start justify-between gap-3">
				<div class="space-y-2">
					<p class="text-sm font-semibold text-foreground">
						{{ category.title }}
					</p>
					<p class="text-sm leading-6 text-muted-foreground">
						{{ category.description }}
					</p>
				</div>
				<Icon :name="category.icon" class="mt-1 h-4 w-4 text-muted-foreground" />
			</div>
			<p class="mt-4 text-xs uppercase tracking-[0.16em] text-muted-foreground">
				{{ category.items }}
			</p>
		</NuxtLink>
	</div>
</template>

<script setup lang="ts">
defineProps<{
	categories: Array<{
		title: string;
		description: string;
		to: string;
		icon: string;
		items: string;
	}>;
}>();
</script>
