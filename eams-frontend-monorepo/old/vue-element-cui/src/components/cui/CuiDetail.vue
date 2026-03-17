<template>
	<div class="detail-box">
		<template v-for="(item, index) in config.fields">
			<div class="item" :key="index" :style="{ width: item.width || '50%' }">
				<div class="item-content">
					<div class="label">{{ item.label }}:</div>
					<div class="content">
						<node-content :content="item.content" :row="config.record" :field="item.name"></node-content>
					</div>
				</div>
			</div>
		</template>
	</div>
</template>
<script>
export default {
	name: "CuiDetail",
	props: {
		config: {
			type: Object,
			required: true,
			default: () => {
				return {
					fields: [], // 字段配置
					record: {}, // 查询结果
				};
			},
		},
	},
	components: {
		NodeContent: {
			props: {
				content: {},
				row: {},
				field: {},
			},
			render(h) {
				if (typeof this.content === "function") return this.content(this.row);
				else return h("span", [this.row[this.field]]);
			},
		},
	},
	data() {
		return {};
	},
	methods: {},
};
</script>
<style lang="scss" scoped>
.detail-box {
	font-size: 12px;
	.item {
		display: inline-block;
		border-bottom: 1px solid #ebeef5;
		margin-bottom: 1px;
		line-height: 18px;
		.item-content {
			display: flex;
			.label {
				width: 140px;
				background-color: #ecf5ff;
				padding: 6px;
				text-align: right;
			}
			.content {
				padding: 6px;
				flex: 1;
			}
		}
	}
}
</style>
