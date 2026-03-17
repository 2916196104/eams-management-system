<template>
	<el-form :model="searchParams" ref="searchFormRef" label-width="90px" size="mini">
		<div style="display: flex">
			<div style="flex: 1">
				<div :gutter="5" class="search-box">
					<div
						v-for="(item, index) in config.fields"
						:key="index"
						style="display: inline-block"
						:style="{ width: (item.width || 220) + 'px' }"
						v-if="item.hidden === undefined || (item.hidden && searchOpen)"
					>
						<el-form-item :label="item.label + ':'" v-if="item.type === 'input'">
							<el-input :placeholder="item.placeholder" v-model="searchParams[item.name]" clearable></el-input>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'textarea'">
							<el-input
								type="textarea"
								:rows="3"
								:placeholder="item.placeholder"
								v-model="searchParams[item.name]"
							></el-input>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'selectBox'">
							<cui-select-box
								:code="item.code"
								:value.sync="searchParams[item.name]"
								:visible.sync="selectorVisible[item.name]"
								:limit="item.limit || 0"
								:condition="item.condition || {}"
							/>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'select'">
							<cui-select
								:code="item.code"
								:value.sync="searchParams[item.name]"
								:clearable="true"
								:filterable="true"
							></cui-select>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'enum'">
							<cui-select-enum :code="item.code" :value.sync="searchParams[item.name]"></cui-select-enum>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'enumCheckbox'">
							<cui-checkbox-enum :code="item.code" :value.sync="searchParams[item.name]"></cui-checkbox-enum>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'dict'">
							<cui-select-dict :code="item.code" :value.sync="searchParams[item.name]"></cui-select-dict>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'month'">
							<el-date-picker
								v-model="searchParams[item.name]"
								type="month"
								placeholder="选择月"
								style="width: 100%"
								value-format="yyyy-MM-dd"
							></el-date-picker>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type == 'date' || item.type == 'daterange'">
							<el-date-picker
								v-model="searchParams[item.name]"
								:type="item.type"
								:picker-options="{ firstDayOfWeek: 1 }"
								:placeholder="item.placeholder"
								value-format="yyyy-MM-dd"
							></el-date-picker>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type == 'datetime'">
							<el-date-picker
								v-model="searchParams[item.name]"
								:type="item.type"
								:picker-options="{ firstDayOfWeek: 1 }"
								:placeholder="item.placeholder"
								value-format="yyyy-MM-dd HH:mm:ss"
								clearable
							></el-date-picker>
						</el-form-item>

						<el-form-item :label="item.label + ':'" v-if="item.type === 'timerange'">
							<el-time-picker
								is-range
								v-model="searchParams[item.name]"
								range-separator="至"
								start-placeholder="开始时间"
								end-placeholder="结束时间"
								placeholder="选择时间范围"
								value-format="HH:mm"
							></el-time-picker>
						</el-form-item>
					</div>
				</div>
			</div>
			<div :style="{ width: rightWidth + 'px' }">
				<div class="text-right padding-bottom">
					<el-button size="mini" type="text" style="margin-right: 8px" @click="setSearchOpen" v-if="showToggleBtn">
						<template v-if="searchOpen">
							收起
							<i class="el-icon-arrow-up"></i>
						</template>
						<template v-else>
							展开
							<i class="el-icon-arrow-down"></i>
						</template>
					</el-button>
					<el-button-group>
						<el-button size="mini" @click="searchFormSubmit" icon="el-icon-search"></el-button>
						<el-button size="mini" @click="searchResetFields" icon="el-icon-circle-close"></el-button>
						<el-button size="mini" @click="handleExport" v-if="showExport">导出</el-button>
					</el-button-group>
				</div>
			</div>
		</div>
	</el-form>
</template>

<script>
/**
 * 参数例子：
 config: {
    fields: [
      {label: "学员姓名", name: "keyword", type: "input", placeholder: "请输入姓名或电话"},
      {label: "开始日期", name: "startDate", type: "date"},
      {label: "状态", name: "state", type: "enum", code: 'VerifyStateEnum'},
      {label: "教师", name: "teacherId", type: "select", code: "teacher"},
    ]
  },

 提交后传递给cui-table的查询方法：
 handleRequest(searchParam) {
      if (searchParam) Object.assign(this.tableConfig.condition, searchParam);
      this.$refs.tableBuilder.loadData();
    },
 * */
export default {
	name: "CuiSearch",
	props: {
		config: {
			type: Object,
			require: true,
		},
		params: {
			type: Object,
			default: () => {
				return {};
			},
		},
		showExport: {
			type: Boolean,
			default: false,
		},
	},
	computed: {
		rightWidth() {
			var base = this.showExport ? 180 : 130;
			var plus = this.showToggleBtn ? 50 : 0;
			return base + plus;
		},
	},
	data() {
		return {
			searchParams: {},
			showToggleBtn: false,
			searchOpen: false,
			selectorVisible: {},
		};
	},
	mounted() {
		if (this.config && this.config.fields) {
			for (const item of this.config.fields) {
				this.$set(this.searchParams, item.name, "");
				if (item.type == "selectBox") {
					this.$set(this.selectorVisible, item.name, false);
				}
				if (item.hidden === true) {
					this.showToggleBtn = true;
				}
			}
		}
	},
	methods: {
		setSearchOpen() {
			this.searchOpen = !this.searchOpen;
		},
		searchResetFields() {
			for (const i in this.searchParams) {
				this.searchParams[i] = null;
			}
			this.searchFormSubmit();
		},
		searchFormSubmit() {
			this.searchParams.page = 1;
			this.$emit("handleRequest", this.searchParams);
			this.$emit("update:params", this.searchParams);
		},
		handleExport() {
			this.$emit("handleExport", this.searchParams);
		},
	},
};
</script>
<style lang="scss"></style>
