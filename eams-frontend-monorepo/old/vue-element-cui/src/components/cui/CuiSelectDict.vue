<template>
	<el-select
		:size="size"
		ref="searchBuilder"
		v-model="selectValue"
		placeholder="请选择"
		:multiple="multiple"
		:loading="loading"
		:clearable="clearable"
		:filterable="filterable"
		:disabled="readonly"
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
<script>
import request from "@/utils/request";
import apis from "../../api/apis";
export default {
	name: "CuiSelectDict",
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
	mounted() {
		this.handleLoad();
	},
	methods: {
		handleLoad(param) {
			this.loading = true;
			request({
				url: apis.dictBuilder,
				params: { ...param, code: this.code },
			}).then((res) => {
				this.options = res;
				this.loading = false;
			});
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
