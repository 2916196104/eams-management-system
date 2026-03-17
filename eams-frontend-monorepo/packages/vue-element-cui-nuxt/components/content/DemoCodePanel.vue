<template>
	<div class="flex min-w-0 flex-1 flex-col">
		<div class="flex items-center justify-between border-b border-border/80 px-5 py-3">
			<div>
				<p class="text-xs font-semibold uppercase tracking-[0.18em] text-muted-foreground">Code</p>
				<p class="mt-1 text-xs text-muted-foreground">先看效果，再决定是否展开代码细节。</p>
			</div>

			<button
				type="button"
				class="inline-flex items-center rounded-full border border-border bg-background px-3 py-1.5 text-xs font-medium text-foreground transition hover:bg-accent hover:text-accent-foreground"
				@click="$emit('toggle')"
			>
				{{ visible ? "收起代码" : "展开代码" }}
			</button>
		</div>

		<div class="cui-demo-code min-h-0 flex-1 overflow-auto px-5 py-4" :hidden="!visible">
			<slot />
		</div>
	</div>
</template>

<script setup lang="ts">
defineProps<{
	visible: boolean;
}>();

defineEmits<{
	toggle: [];
}>();
</script>
