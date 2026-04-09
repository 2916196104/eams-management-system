<template>
	<el-radio-group v-model="selectValue">
		<el-radio style="margin-bottom: 10px" v-for="(item, index) in dataList" :key="index" :label="item.id">
			{{ item.label }}
		</el-radio>
	</el-radio-group>
</template>

<script>
import request from "@/utils/request";
import apis from "../../api/apis";
export default {
	name: "CuiRadioDict",
	props: {
		value: [String, Number],
		code: {
			type: String,
			default: "input",
		},
	},
	data() {
		return {
			dataList: [],
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
	created() {
		this.handleLoad();
	},
	methods: {
		handleLoad(param) {
			this.loading = true;
			request({
				url: apis.dictBuilder,
				params: { ...param, code: this.code },
			}).then((res) => {
				this.dataList = res;
				this.loading = false;
			});
		},
	},
};
</script>
