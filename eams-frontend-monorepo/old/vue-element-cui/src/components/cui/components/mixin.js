export default {
	props: {
		condition: {
			type: Object,
			default: () => {
				return {};
			},
		},
		limit: {
			type: Number,
			default: 0,
		},
	},
	computed: {
		isSingle: function () {
			return this.limit == 1;
		},
	},
	methods: {
		handleRequest(searchParam) {
			Object.assign(this.tableConfig.condition, this.condition);
			if (searchParam) Object.assign(this.tableConfig.condition, searchParam);
			this.$refs.tableBuilder.loadData();
		},
		handleClear() {
			this.selectedData = [];
		},
		handleSelect(row) {
			// 单选处理
			if (this.limit == 1) {
				this.selectedData = [row];
				this.formSubmit();
				return;
			}
			// 多选处理
			for (var item of this.selectedData) {
				if (item == row) return;
			}
			if (this.limit != 0 && this.selectedData.length >= this.limit) {
				alert(`最多选择 ${this.limit} 项`);
				return;
			}
			this.selectedData.push(row);
		},
		remove(index) {
			this.selectedData.splice(index, 1);
		},
		// 提交
		formSubmit: async function () {
			this.$emit("onSubmit", this.selectedData);
		},
	},
};
