<template>
	<div>
		<el-input v-if="!choosing" readonly @focus="onChoose" v-model="defaultText" :size="size"></el-input>
		<template v-else>
			<el-select
				:size="size"
				:automatic-dropdown="autoDown"
				ref="searchBuilder"
				v-model="selectValue"
				placeholder="请选择"
				:multiple="multiple"
				:loading="loading"
				:clearable="clearable"
				:filterable="filterable"
				:disabled="disabled"
				@focus="onLoad"
				style="width: 100%"
			>
				<el-option
					v-for="item in options"
					:key="item[id]"
					:label="item[label]"
					:value="item[id]"
					:class="{ 'option-with-info': !!item.info }"
				>
					<div v-if="!!item.info">{{ item.label }}</div>
					<div v-if="!!item.info" class="info">{{ item.info }}</div>
				</el-option>
			</el-select>
		</template>
	</div>
</template>
<script>
import request from "@/utils/request";
import apis from "../../api/apis";

export default {
	name: "CuiSelect",
	props: {
		value: [String, Number, Array],
		code: {
			type: String,
			required: true,
		},
		readonly: {
			type: Boolean,
			default: false,
		},
		clearable: {
			type: Boolean,
			default: false,
		},
		filterable: {
			type: Boolean,
			default: false,
		},
		multiple: {
			type: Boolean,
			default: false,
		},
		id: {
			type: String,
			default: "id",
		},
		label: {
			type: String,
			default: "label",
		},
		size: {
			type: String,
			default: "",
		},
	},
	data() {
		return {
			options: [],
			autoDown: true,
			choosing: false,
			disabled: false,
			defaultText: "",
			loading: false,
		};
	},
	computed: {
		selectValue: {
			get: function () {
				return this.value;
			},
			set: function (val) {
				this.$emit("update:value", val);
			},
		},
	},
	watch: {
		value: {
			handler: function (v) {
				this.loadLabel(v);
			},
			immediate: true,
		},
	},
	methods: {
		handleLoad(param) {
			request({
				url: apis.selectBuilder,
				params: { ...param, code: this.code },
			}).then((res) => {
				this.options = res;
			});
		},
		onLoad() {
			if (this.options.length === 0) {
				this.loading = true;
				this.handleLoad();
				this.loading = false;
			}
		},
		onChoose() {
			if (!this.readonly) {
				this.choosing = true;
				this.$emit("update:defaultText", "");
			}

			this.$nextTick(() => {
				this.$refs.searchBuilder.focus();
				this.autoDown = false;
			});
		},
		loadLabel(v) {
			this.defaultText = "loading...";
			if (v === "" || !v) {
				this.defaultText = "";
			} else {
				if (this.multiple == false) {
					request({
						url: apis.selectLoadLabel,
						params: { ids: v, code: this.code },
					}).then((res) => {
						this.defaultText = res;
					});
				}
			}
		},
	},
};
</script>
<style lang="scss" scoped>
.option-with-info {
	height: 50px !important;

	.info {
		color: #8492a6;
		font-size: 12px;
		line-height: 14px;
	}
}
</style>
