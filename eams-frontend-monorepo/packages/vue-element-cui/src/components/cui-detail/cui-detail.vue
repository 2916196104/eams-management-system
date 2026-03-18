<template>
	<div class="cui-detail">
		<div class="detail-grid" :style="{ gridTemplateColumns: `repeat(${columns}, 1fr)` }">
			<div v-for="field in fields" :key="field.prop" class="detail-item">
				<div class="detail-label" :style="{ width: labelWidth }">{{ field.label }}:</div>
				<div class="detail-value">
					<template v-if="field.render">
						{{ field.render(data) }}
					</template>
					<template v-else>
						{{ data[field.prop] }}
					</template>
				</div>
			</div>
		</div>
	</div>
</template>

<script setup lang="ts">
import type { CuiDetailProps } from "./types";

const props = withDefaults(defineProps<CuiDetailProps>(), {
	labelWidth: "140px",
	columns: 2,
});
</script>

<style scoped lang="scss">
.cui-detail {
	font-size: 14px;

	.detail-grid {
		display: grid;
		gap: 0;
	}

	.detail-item {
		display: flex;
		border-bottom: 1px solid #ebeef5;
		min-height: 32px;

		.detail-label {
			background-color: #f5f7fa;
			padding: 8px 12px;
			font-weight: 500;
			text-align: right;
			flex-shrink: 0;
		}

		.detail-value {
			padding: 8px 12px;
			flex: 1;
			word-break: break-word;
		}
	}
}
</style>
