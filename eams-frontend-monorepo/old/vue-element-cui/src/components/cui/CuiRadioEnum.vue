<template>
	<el-radio-group v-model="selectValue">
		<el-radio v-for="(item, index) in dataList" :key="index" :label="item">{{ item }}</el-radio>
	</el-radio-group>
</template>

<script>
/**
 * 用法
 *  const searchConfig = {
      fields: [
          {label: "姓名", name: "keyword", type: "input", placeholder: "请输入姓名或电话"},
          {label: "性别", name: "gender", type: "enum", code: "GenderEnum", placeholder: "请输入姓名或电话"},
      ]
  };
 *
 * */
import { getEnumItem } from "@/utils/common";

export default {
	name: "RadioEnum",
	props: {
		value: String,
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
		this.fetchRequest();
	},
	methods: {
		fetchRequest() {
			this.dataList = getEnumItem(this.code);
		},
	},
};
</script>
