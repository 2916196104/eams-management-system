<template>
	<nav class="eams-nav" role="navigation" aria-label="教务系统导航">
		<div v-if="showLogo" class="eams-nav__brand">
			<img class="eams-nav__brand-logo" :src="logoSrcResolved" :alt="appNameResolved" :title="appNameResolved" />
		</div>
		<div class="eams-nav__list">
			<div v-for="item in items" :key="item.key" class="eams-nav__group">
				<button
					class="eams-nav__group-btn"
					type="button"
					:aria-expanded="openGroupKey === item.key"
					@click="toggleGroup(item)"
				>
					<span class="eams-nav__icon-wrap" :class="{ 'is-active': activeGroupKeyResolved === item.key }">
						<el-icon :size="22">
							<component :is="resolveIcon(item.icon)" />
						</el-icon>
					</span>
					<span class="eams-nav__group-label">{{ item.label }}</span>
				</button>

				<div
					v-if="(item.children?.length ?? 0) > 0"
					class="eams-nav__sub"
					:class="{ 'is-open': openGroupKey === item.key }"
				>
					<button
						v-for="child in item.children"
						:key="child.key"
						class="eams-nav__sub-btn"
						type="button"
						:class="{ 'is-active': activeGroupKeyResolved === item.key && activeSubKeyResolved === child.key }"
						@click="selectSub(item, child)"
					>
						{{ child.label }}
					</button>
				</div>
			</div>
		</div>
	</nav>
</template>

<script setup lang="ts">
import { computed, ref, resolveComponent, watch } from 'vue'
import type { Component } from 'vue'
import { useRoute } from 'vue-router'
import type { EamsNavItem, EamsNavSubItem } from './types'

const props = withDefaults(
	defineProps<{
		items: EamsNavItem[]
		activeGroupKey?: string | null
		activeSubKey?: string | null
		showLogo?: boolean
		logoSrc?: string
		appName?: string
	}>(),
	{
		showLogo: true,
		logoSrc: '/logo.jpg'
	}
)

const emit = defineEmits<{
	(e: 'update:activeGroupKey', v: string | null): void
	(e: 'update:activeSubKey', v: string | null): void
	(e: 'select', payload: { group: EamsNavItem; sub?: EamsNavSubItem; path: string }): void
}>()

const route = useRoute()

const logoSrcResolved = computed(() => props.logoSrc)
const appNameResolved = computed(() => props.appName ?? import.meta.env.VITE_APP_TITLE ?? '')
const showLogo = computed(() => props.showLogo)

function resolveIcon(icon?: string | Component) {
	if (!icon) return resolveComponent('IconMenu')
	if (typeof icon !== 'string') return icon
	const resolved = resolveComponent(icon)
	if (typeof resolved === 'string') return resolveComponent('IconMenu')
	return resolved as Component
}

const openGroupKey = ref<string | null>(props.activeGroupKey ?? null)
const activeGroupKeyInner = ref<string | null>(props.activeGroupKey ?? null)
const activeSubKeyInner = ref<string | null>(props.activeSubKey ?? null)

const activeGroupKeyResolved = computed(() => props.activeGroupKey ?? activeGroupKeyInner.value)
const activeSubKeyResolved = computed(() => props.activeSubKey ?? activeSubKeyInner.value)

function syncActiveByRoute(path: string) {
	for (const group of props.items) {
		if (group.path && group.path === path) {
			activeGroupKeyInner.value = group.key
			activeSubKeyInner.value = group.key
			openGroupKey.value = null
			return
		}
		const hit = group.children?.find((c) => c.path === path)
		if (!hit) continue
		activeGroupKeyInner.value = group.key
		activeSubKeyInner.value = hit.key
		openGroupKey.value = group.key
		return
	}
}

watch(
	() => route.path,
	(p) => syncActiveByRoute(p),
	{ immediate: true }
)

function toggleGroup(item: EamsNavItem) {
	const hasChildren = (item.children?.length ?? 0) > 0
	if (!hasChildren) {
		activeGroupKeyInner.value = item.key
		activeSubKeyInner.value = item.key
		openGroupKey.value = null
		emit('update:activeGroupKey', item.key)
		emit('update:activeSubKey', item.key)
		emit('select', { group: item, path: item.path ?? '' })
		return
	}

	openGroupKey.value = openGroupKey.value === item.key ? null : item.key
	activeGroupKeyInner.value = item.key
	emit('update:activeGroupKey', item.key)

	const child = item.children?.[0]
	if (!child) return
	activeSubKeyInner.value = child.key
	emit('update:activeSubKey', child.key)
	emit('select', { group: item, sub: child, path: child.path })
}

function selectSub(group: EamsNavItem, sub: EamsNavSubItem) {
	openGroupKey.value = group.key
	activeGroupKeyInner.value = group.key
	activeSubKeyInner.value = sub.key
	emit('update:activeGroupKey', group.key)
	emit('update:activeSubKey', sub.key)
	emit('select', { group, sub, path: sub.path })
}
</script>

<style scoped>
.eams-nav {
	width: 96px;
	height: 100%;
	background: #0b1e2d;
	color: rgba(255, 255, 255, 0.92);
	overflow: auto;
}

.eams-nav__brand {
	padding: 12px 8px 6px;
	display: flex;
	justify-content: center;
}

.eams-nav__brand-logo {
	width: 34px;
	height: 34px;
	border-radius: 8px;
	object-fit: cover;
}

.eams-nav__list {
	padding: 10px 8px;
	display: flex;
	flex-direction: column;
	gap: 10px;
}

.eams-nav__group {
	display: flex;
	flex-direction: column;
	align-items: center;
}

.eams-nav__group-btn {
	appearance: none;
	border: 0;
	padding: 6px 0;
	width: 100%;
	background: transparent;
	color: inherit;
	cursor: pointer;
	display: flex;
	flex-direction: column;
	align-items: center;
	gap: 6px;
}

.eams-nav__icon-wrap {
	width: 46px;
	height: 46px;
	border-radius: 50%;
	display: flex;
	align-items: center;
	justify-content: center;
	background: transparent;
	transition: background-color 0.18s ease;
}

.eams-nav__icon-wrap.is-active {
	background: #2a7bff;
}

.eams-nav__group-label {
	font-size: 12px;
	line-height: 16px;
	user-select: none;
}

.eams-nav__sub {
	width: 100%;
	max-height: 0;
	opacity: 0;
	overflow: hidden;
	transition: max-height 0.2s ease, opacity 0.2s ease;
	display: flex;
	flex-direction: column;
	gap: 4px;
}

.eams-nav__sub.is-open {
	max-height: 360px;
	opacity: 1;
	margin-top: 6px;
}

.eams-nav__sub-btn {
	appearance: none;
	border: 0;
	padding: 8px 6px;
	width: 100%;
	background: rgba(255, 255, 255, 0.06);
	border-radius: 8px;
	color: rgba(255, 255, 255, 0.9);
	font-size: 12px;
	line-height: 16px;
	cursor: pointer;
	text-align: center;
	white-space: normal;
}

.eams-nav__sub-btn.is-active {
	background: rgba(42, 123, 255, 0.28);
	color: #ffffff;
}
</style>

