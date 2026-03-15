<template>
	<DemoPlayground :title="title" :description="description">
		<template #preview>
			<slot name="preview" />
		</template>

		<template #code>
			<slot name="code" />
		</template>

		<slot />
	</DemoPlayground>
</template>

<script setup lang="ts">
defineProps<{
	title?: string;
	description?: string;
}>();
</script>
