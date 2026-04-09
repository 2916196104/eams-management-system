<template>
	<el-checkbox-group v-model="selectValue">
		<el-checkbox v-for="(item, index) in dataList" :label="item" :key="index">{{ item }}</el-checkbox>
	</el-checkbox-group>
</template>
<script>
import { getEnumItem } from "@/utils/common";

export default {
	name: "SearchEnum",
	props: {
		value: {
			type: String,
			default: "",
		},
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
				return this.value ? this.value.split(",") : [];
			},
			set: function (val) {
				this.$emit("update:value", val.join(","));
			},
		},
	},
	created() {
		this.handleRequest();
	},
	methods: {
		handleRequest() {
			this.dataList = getEnumItem(this.code);
		},
	},
};
</script>
