<template>
	<div>
		<el-input readonly @focus="clickSelector" v-model="label"></el-input>
		<component
			:is="currentComponent"
			:limit="limit"
			:visible.sync="dialogVisible"
			@onSubmit="handleSelectorChange"
			:condition="condition"
		/>
	</div>
</template>

<script>
import apis from "../../api/apis";
import request from "@/utils/request";
export default {
	name: "CuiSelectorBox",
	components: {
		/*
		 * 这里注册选择器组件，可以自己根据需要开发自己的内容选择器，下面是一个例子
		 */
		CourseSelectDialog: () => import("./components/CourseSelectDialog"),
		// 'StudentSelectDialog': () => import('./components/StudentSelectDialog'),
	},
	computed: {
		currentComponent: function () {
			/* 
      这里是一个例子，根据code来判断用哪个选择器。
      你需要做的事打开下面的注释，把if写成自己的
      */

			// var name = ''
			// if(this.code == 'course') name = 'CourseSelectDialog';
			// return name;

			return "CourseSelectDialog";
		},
	},
	props: {
		// teacher 等的标记
		code: {
			type: String,
			required: true,
		},
		condition: {
			type: Object,
		},
		value: {
			type: String | undefined,
			required: true,
		},
		disable: {
			type: Boolean,
			required: false,
		},
		// 限制选择数量 0 表示不限制
		limit: {
			type: Number,
			default: 0,
		},
	},
	data() {
		return {
			label: "",
			dialogVisible: false,
		};
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
		handleSelectorChange(rows) {
			var value = [];
			for (var r of rows) {
				value.push(r.id);
			}
			this.$emit("update:value", value.join(","));
			this.$emit("onSubmit", value.join(","));
		},
		loadLabel(v) {
			this.label = "loading...";
			if (v === "" || !v) {
				this.label = "";
			} else {
				request({
					url: apis.selectLoadLabel,
					params: { ids: v, code: this.code },
				}).then((res) => {
					this.label = res;
				});
			}
		},
		clickSelector() {
			if (!this.disable) {
				this.dialogVisible = true;
			}
		},
	},
};
</script>
