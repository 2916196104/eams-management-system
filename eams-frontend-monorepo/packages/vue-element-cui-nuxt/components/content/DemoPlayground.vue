<template>
	<section class="cui-demo-wrapper my-8 overflow-hidden rounded-2xl border border-border bg-card shadow-sm">
		<header v-if="title || description" class="border-b border-border/80 bg-muted/40 px-5 py-4">
			<div class="flex items-start justify-between gap-4">
				<div class="space-y-1">
					<h3 v-if="title" class="text-base font-semibold text-foreground">
						{{ title }}
					</h3>
					<p v-if="description" class="text-sm leading-6 text-muted-foreground">
						{{ description }}
					</p>
				</div>

				<span
					class="inline-flex items-center rounded-full border border-border bg-background px-2.5 py-1 text-xs font-medium text-muted-foreground"
				>
					Live Demo
				</span>
			</div>
		</header>

		<div class="grid gap-px bg-border/70 lg:grid-cols-[minmax(0,1.15fr)_minmax(320px,0.85fr)]">
			<div class="cui-demo-preview bg-background p-5">
				<p class="mb-3 text-xs font-semibold uppercase tracking-[0.18em] text-muted-foreground">Preview</p>
				<div class="cui-demo-container rounded-xl border border-dashed border-border/80 bg-muted/20 p-4">
					<ClientOnly>
						<slot name="preview" />
					</ClientOnly>
				</div>
			</div>

			<div class="flex min-w-0 flex-col bg-muted/40">
				<DemoCodePanel data-testid="code-panel" :visible="isCodeVisible" @toggle="toggleCode">
					<slot name="code" />
				</DemoCodePanel>
			</div>
		</div>

		<footer v-if="$slots.default" class="border-t border-border/80 bg-background px-5 py-4">
			<slot />
		</footer>
	</section>
</template>

<script setup lang="ts">
import { ref } from "vue";

defineProps<{
	title?: string;
	description?: string;
}>();

const isCodeVisible = ref(true);

const toggleCode = () => {
	isCodeVisible.value = !isCodeVisible.value;
};
</script>
