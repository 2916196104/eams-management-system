<template>
	<el-row :gutter="10">
		<el-col :span="isSingle ? 24 : 12">
			<cui-search :config="searchConfig" @handleRequest="handleRequest"></cui-search>
			<cui-table ref="tableBuilder" :config="tableConfig"></cui-table>
		</el-col>
		<el-col :span="12" v-if="!isSingle">
			<el-form label-width="80px" size="mini" style="margin-bottom: 16px">
				<div style="display: flex">
					<div style="flex: 1">
						<div style="lin-height: 30px">已选列表：</div>
					</div>
					<div style="width: 200px" class="text-right">
						<el-button size="mini" type="primary" plain @click="handleClear">重选</el-button>
						<el-button size="mini" type="primary" @click="formSubmit">选好了</el-button>
					</div>
				</div>
			</el-form>
			<el-table border :data="selectedData" style="width: 100%" size="small" empty-text="暂未选择">
				<el-table-column prop="address" width="80">
					<template slot-scope="scope">
						<el-button type="text" @click="remove(scope.$index)">&lt; 移除</el-button>
					</template>
				</el-table-column>
				<el-table-column prop="name" label="已选项"></el-table-column>
			</el-table>
		</el-col>
	</el-row>
</template>

<script>
/*
 * 如果需要其他数据选择器，复制该组件到 CuiSelectBox 组件里注册即可
 */
import apis from "@/api/apis";
import mixin from "./mixin";
export default {
	name: "CourseSelectDialog",
	mixins: [mixin],
	data() {
		return {
			tableConfig: {
				url: apis.courseList,
				showDiyButtons: false,
				condition: { state: "启用" },
				// 根据情况自行设置表头内容
				fields: [{ title: "演示名称", name: "name" }],
				actions: [
					{
						title: "选择 >",
						click: (row) => {
							this.handleSelect(row);
						},
					},
				],
				height: 450,
			},
			selectedData: [],
			searchConfig: {
				fields: [{ label: "搜名称", name: "keyword", type: "input" }],
			},
		};
	},
	methods: {},
};
</script>
<style scoped></style>
