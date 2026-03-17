<template>
	<el-select :size="size" v-model="selectValue" :placeholder="placeholder || '请选择'" style="width: 100%">
		<el-option v-for="(item, index) in dataList" :key="index" :label="item" :value="item"></el-option>
	</el-select>
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
	name: "SearchEnum",
	props: {
		value: String,
		placeholder: String,
		code: {
			type: String,
			default: "input",
		},
		size: {
			type: String,
			default: "",
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
