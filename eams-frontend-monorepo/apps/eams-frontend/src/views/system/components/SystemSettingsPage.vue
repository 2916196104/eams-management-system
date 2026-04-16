<template>
	<section class="panel-card parameter-page">
		<aside class="group-nav">
			<div
				v-for="group in groups"
				:key="group.id"
				:class="['group-nav__item', { 'group-nav__item--active': group.id === activeGroupId }]"
				@click="activeGroupId = group.id"
			>
				{{ group.label }}
			</div>
		</aside>

		<section class="setting-panel">
			<div class="setting-panel__header">
				<div>{{ config.headers.item }}</div>
				<div>{{ config.headers.value }}</div>
			</div>

			<div v-for="item in currentGroup?.items" :key="item.id" class="setting-row">
				<div class="setting-row__label">
					<div class="setting-row__title">{{ item.label }}</div>
					<div v-if="item.description" class="setting-row__desc">{{ item.description }}</div>
				</div>

				<div class="setting-row__value">
					<el-switch
						v-if="item.type === 'switch'"
						:model-value="Boolean(item.value)"
						@change="(value) => handleValueChange(item.id, Boolean(value))"
					/>
					<el-input
						v-else-if="item.type === 'input'"
						:model-value="String(item.value ?? '')"
						@change="(value) => handleValueChange(item.id, value)"
					/>
					<el-input-number
						v-else-if="item.type === 'number'"
						:model-value="Number(item.value)"
						:min="0"
						:controls="false"
						class="setting-row__number"
						@change="(value) => handleValueChange(item.id, value ?? 0)"
					/>
					<el-time-picker
						v-else-if="item.type === 'time'"
						:model-value="String(item.value ?? '00:00')"
						format="HH:mm"
						value-format="HH:mm"
						class="setting-row__time"
						@change="handleTimeValueChange(item.id, $event)"
					/>
					<el-input
						v-else
						:model-value="String(item.value ?? '')"
						type="textarea"
						:rows="3"
						@change="(value) => handleValueChange(item.id, value)"
					/>
				</div>
			</div>
		</section>
	</section>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from "vue";
import { ElMessage } from "element-plus";
import type { SystemSettingGroup } from "@/apis/system/type";
import type { SystemSettingsPageConfig } from "../shared";

const props = defineProps<{
	config: SystemSettingsPageConfig;
}>();

const groups = ref<SystemSettingGroup[]>([]);
const activeGroupId = ref("");

const currentGroup = computed(() => groups.value.find((item) => item.id === activeGroupId.value));

async function loadGroups() {
	groups.value = await props.config.loadGroups();
	if (!activeGroupId.value && groups.value.length > 0) activeGroupId.value = groups.value[0].id;
}

async function handleValueChange(itemId: string, value: string | number | boolean) {
	const group = currentGroup.value;
	if (!group) return;
	const target = group.items.find((item) => item.id === itemId);
	if (!target) return;
	target.value = value;
	await props.config.updateValue(group.id, itemId, value);
	ElMessage.success("设置已更新");
}

function handleTimeValueChange(itemId: string, value: unknown) {
	const nextValue =
		typeof value === "string"
			? value
			: value instanceof Date
				? `${String(value.getHours()).padStart(2, "0")}:${String(value.getMinutes()).padStart(2, "0")}`
				: "00:00";
	return handleValueChange(itemId, nextValue);
}

onMounted(() => {
	loadGroups();
});
</script>

<style scoped>
.panel-card {
	background: #ffffff;
	border: 1px solid #edf0f5;
	box-shadow: 0 1px 2px rgb(31 45 61 / 4%);
}

.parameter-page {
	margin: 16px;
	display: grid;
	grid-template-columns: 320px minmax(0, 1fr);
}

.group-nav {
	padding: 16px 0;
	border-right: 1px solid #edf1f7;
}

.group-nav__item {
	padding: 14px 40px;
	font-size: 16px;
	color: #2e3b52;
	cursor: pointer;
}

.group-nav__item--active {
	color: #4a89f3;
	background: #edf4ff;
}

.setting-panel {
	padding: 12px 20px;
}

.setting-panel__header {
	padding: 6px 0 16px;
	display: grid;
	grid-template-columns: 380px minmax(0, 1fr);
	gap: 20px;
	font-weight: 700;
	color: #5a687c;
}

.setting-row {
	padding: 14px 0;
	display: grid;
	grid-template-columns: 380px minmax(0, 1fr);
	gap: 20px;
	border-top: 1px solid #eef2f7;
}

.setting-row__title {
	font-size: 16px;
	font-weight: 600;
	color: #3a475d;
}

.setting-row__desc {
	margin-top: 6px;
	font-size: 14px;
	color: #8d98ab;
	line-height: 1.5;
}

.setting-row__value {
	display: flex;
	align-items: center;
}

.setting-row__value :deep(.el-input),
.setting-row__number,
.setting-row__time {
	width: 100%;
}
</style>
