<template>
	<NuxtLink
		:to="to"
		class="block px-3 py-2 text-sm rounded-md transition-colors"
		active-class="bg-blue-50 text-blue-700 font-medium"
		:class="{
			'text-gray-700 hover:bg-gray-100': !isActive,
			'bg-blue-50 text-blue-700 font-medium': isActive,
		}"
	>
		{{ label }}
	</NuxtLink>
</template>

<script setup lang="ts">
const props = defineProps<{
	to: string;
	label: string;
}>();

const route = useRoute();
const isActive = computed(() => route.path === props.to);
</script>
