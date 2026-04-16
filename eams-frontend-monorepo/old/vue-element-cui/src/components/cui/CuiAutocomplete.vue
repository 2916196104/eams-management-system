<template>
	<el-autocomplete
		v-model="selectValue"
		:fetch-suggestions="querySearchAsync"
		placeholder="请输入"
		@select="handleSelect"
		style="width: 100%"
	></el-autocomplete>
</template>
<script>
import request from "@/utils/request";
import apis from "@/api/apis";
export default {
	name: "CuiAutocomplete",
	props: {
		value: String,
		code: {
			type: String,
			default: "input",
		},
	},
	data() {
		return {
			timeout: null,
		};
	},
	computed: {
		selectValue: {
			get: function () {
				console.log("8881111");
				return this.value;
			},
			set: function (val) {
				console.log("abc1111");
				this.$emit("update:value", val);
			},
		},
	},
	methods: {
		querySearchAsync(queryString, cb) {
			clearTimeout(this.timeout);
			this.timeout = setTimeout(() => {
				request({
					url: apis.aotucompleteBuilder,
					params: { code: this.code, keyword: queryString },
				}).then((res) => {
					cb(res);
				});
			}, 500);
		},
		handleSelect(item) {
			console.log(item);
		},
	},
};
</script>
