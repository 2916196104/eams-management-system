<template>
	<el-dialog
		v-el-drag-dialog
		custom-class="custom-dialog"
		:close-on-click-modal="false"
		:close-on-press-escape="false"
		:modal="false"
		:title="title"
		:width="width"
		:top="top"
		:visible.sync="dialogVisible"
		@close="onClose"
	>
		<slot></slot>
		<template #footer>
			<el-button key="back" @click="onClose()">{{ showSubmitBtn ? "取消" : "关闭" }}</el-button>
			<slot name="btn"></slot>
			<el-button
				v-if="showSubmitBtn"
				key="submit"
				type="primary"
				:disabled="disabled"
				:loading="loading"
				@click="handleSubmit()"
			>
				{{ submitBtnText }}
			</el-button>
		</template>
	</el-dialog>
</template>
<script>
import elDragDialog from "@/directive/el-drag-dialog";
export default {
	name: "DialogBuilder",
	directives: { elDragDialog },
	props: {
		visible: {
			type: Boolean,
			required: true,
		},
		title: {
			type: String,
			default: "提示",
		},
		width: {
			type: String,
			default: "600px",
		},
		top: {
			type: String,
			default: "13vh",
		},
		submitBtnText: {
			type: String,
			default: "提交",
		},
		showSubmitBtn: {
			type: Boolean,
			default: true,
		},
	},
	computed: {
		dialogVisible: {
			get: function () {
				return this.visible;
			},
			set: function (v) {
				this.$emit("update:visible", v);
			},
		},
	},
	data() {
		return {
			loading: false,
			disabled: false,
		};
	},
	methods: {
		onClose() {
			this.dialogVisible = false;
			this.$emit("onclose");
		},
		handleSubmit() {
			this.disabled = true;
			setTimeout(() => {
				this.disabled = false;
			}, 3000);
			this.loading = true;
			this.$emit("submit");
			this.loading = false;
		},
	},
};
</script>
