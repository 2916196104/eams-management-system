<template>
	<div class="table-builder">
		<el-alert :title="info" type="info" v-if="info != ''" style="margin-bottom: 10px" :closable="false"></el-alert>
		<el-row style="margin-bottom: 10px" :gutter="10">
			<el-col :span="20">
				<template v-for="(item, index) in topActions">
					<el-button
						:key="index"
						:type="item.type || ''"
						v-if="handleMultiButtonVisible(item)"
						@click="item.click(multipleSelectionVal)"
						:icon="item.icon"
						size="mini"
					>
						{{ item.title }}
					</el-button>
				</template>
				<span>&nbsp;</span>
			</el-col>
			<el-col :span="4" style="text-align: right">
				<el-button-group v-if="showDiyButtons">
					<el-button icon="el-icon-refresh" size="mini" @click="handleRefresh"></el-button>
					<el-button icon="el-icon-printer" size="mini" v-print="'#printTable'"></el-button>
					<el-popover placement="right" width="400" trigger="click">
						<div style="margin-bottom: 10px; border-bottom: 1px solid #e4e4e4; color: #999">自定义显示列：</div>
						<el-checkbox-group v-model="checkedLabels">
							<el-checkbox v-for="(item, index) in config.fields" :key="index" :label="item.title"></el-checkbox>
						</el-checkbox-group>
						<div style="text-align: right">
							<el-button type="text" @click="resetVisibleColumn">恢 复</el-button>
							<el-button type="text" @click="visibleColumn">确 认</el-button>
						</div>
						<el-button icon="el-icon-menu" size="mini" slot="reference"></el-button>
					</el-popover>
				</el-button-group>
			</el-col>
		</el-row>
		<!--  -->
		<el-table
			id="printTable"
			class="cui-table bueatyScroll"
			border
			:data="data"
			v-loading="loading"
			ref="tableBuilder"
			:max-height="height"
			:default-expand-all="expand"
			highlight-current-row
			size="small"
			:empty-text="emptyText"
			@sort-change="handleSortChange"
			@selection-change="handleSelectionChange"
			@row-click="handleRowClick"
			:row-class-name="rowClassName"
			:show-summary="showSummary"
			:summary-method="() => sums"
			style="margin-bottom: 10px; width: 100%"
			:span-method="objectSpanMethod"
		>
			<el-table-column type="expand" v-if="expand">
				<template slot-scope="scope">
					<slot name="expandContent" :data="scope.row"></slot>
				</template>
			</el-table-column>
			<el-table-column
				type="selection"
				align="center"
				prop="selectable"
				:selectable="selectFunc"
				v-if="selectable"
				width="45"
			></el-table-column>
			<el-table-column label="序号" type="index" prop="indexed" :index="indexMethod" v-if="indexed"></el-table-column>
			<el-table-column
				v-for="(item, index) in columnFields"
				:key="index"
				:label="item.title"
				:prop="item.name"
				:sortable="item.sortable || false"
				:align="item.align || 'left'"
				:width="item.width || ''"
				v-if="typeof item.visible != 'undefined' ? item.visible(item) : true"
			>
				<template slot-scope="scope">
					<editalbe-text
						v-if="item.editable"
						:field="item.name"
						:row="scope.row"
						:editFunc="item.editFunc"
						:editConf="item.editConf"
					>
						<node-content :content="item.content" :row="scope.row" :text="scope.row[item.name]"></node-content>
					</editalbe-text>
					<node-content v-else :content="item.content" :row="scope.row" :text="scope.row[item.name]"></node-content>
				</template>
			</el-table-column>
			<!--            fixed="right"-->
			<el-table-column
				label="操作"
				:width="actionWidth"
				prop="actionButtons"
				class-name="action-column"
				v-if="actions && actions.length > 0"
			>
				<template slot-scope="scope">
					<template v-for="(item, index) in actions">
						<el-tooltip :key="index" :disabled="!item.alt" :content="item.alt" placement="top" effect="light">
							<el-dropdown v-if="item.type === 'list'">
								<el-button type="text" :icon="item.icon" :size="item.size || 'small'" style="margin-left: 10px">
									{{ item.title }}
									<i class="el-icon-arrow-down el-icon--right"></i>
								</el-button>
								<el-dropdown-menu slot="dropdown">
									<template v-for="(opt, ind) in item.options">
										<el-dropdown-item
											:key="ind"
											v-if="handleButtonVisible(opt, scope.row)"
											@click.native="opt.click && opt.click(scope.row)"
										>
											{{ opt.title }}
										</el-dropdown-item>
									</template>
								</el-dropdown-menu>
							</el-dropdown>
							<template v-else>
								<el-button
									:type="item.type || 'text'"
									:class="item.class || ''"
									@click.stop="item.click && item.click(scope.row)"
									v-if="handleButtonVisible(item, scope.row)"
									:icon="item.icon"
									:size="item.size || 'small'"
								>
									{{ item.title }}
								</el-button>
							</template>
						</el-tooltip>
					</template>
				</template>
			</el-table-column>
		</el-table>
		<el-row class="fixed-bottom">
			<el-col :span="topActions && topActions.length > 0 ? 12 : 0"></el-col>
			<!-- v-if="this.showPaginate && pagination.pageCount > 1" -->
			<el-col :span="topActions && topActions.length > 0 ? 12 : 24" v-if="this.showPaginate">
				<el-pagination
					small
					background
					@size-change="handleSizeChange"
					@current-change="handleCurrentChange"
					:current-page.sync="params.page"
					:page-sizes="[30, 50, 100, 200]"
					:page-size="params.pageSize"
					:layout="paginateLayout"
					:total="pagination.total"
				></el-pagination>
			</el-col>
		</el-row>
	</div>
</template>
<script>
import request from "@/utils/request";
import checkPermission from "@/utils/permission";
import EditalbeText from "./components/EditalbeText.vue";
/* 用法
模板：
<cui-table ref="tableBuilder" :config="tableConfig" :selectedRows.sync="selectedRows"></cui-table>
配置参数：
  data() {
    return {
     tableConfig: {
        url: apis.studentList,
        indexed: true,
        selectable: false,
        emptyText: "暂无数据",
        selectFunc: (row, index) => true,
        fields: [
          {title: "学员姓名", name: "name", content: (row) => { return (<span class='text-link' onClick={()=> this.test() }>{row.studentName}</span>) } },
          {title: "联系电话", name: "mobile"},
          {title: "性别", name: "gender"},
          {title: "出生年月", name: "birthday"},
          {title: "年龄(周岁)", name: "age"},
          {title: "添加时间", name: "addTime"},
          {title: "备注", name: "remark"},
        ],
        actions: [
          {
            title: "查看", click: (row) => {
              this.showDetail(row.id);
            }
          },
          {
            title: "修改", click: (row) => {
              this.handleEdit(row.id);
            }
          },
        ],
        topActions: [
          {
            title: '添加学员', type: 'primary', icon: "el-icon-plus", click: () => {
              this.handleAdd()
            }
          },
          {
            title: '删除', icon: "el-icon-delete", click: () => {
              actions.handleDelete(this.selectedRows, () => this.handleRequest())
            }
          },
        ],
        condition: {},
      },
      selectedRows: [],
      
  }
}
如果要使用组件里的方法，需要用在mounted中
*/
export default {
	props: {
		config: {
			required: true,
			default: () => {
				return {};
			},
		},
		selectedRows: {
			default: () => {
				return [];
			},
		},
	},
	components: {
		EditalbeText,
		NodeContent: {
			props: {
				content: {},
				row: {},
				text: {},
			},
			render(h) {
				if (typeof this.content === "function") return this.content(this.row);
				else return h("span", [this.text]);
			},
		},
	},
	data() {
		return {
			// 获取参数
			url: this.config.url ?? "",
			info: this.config.info ?? "",
			condition: this.config.condition ?? {},
			emptyText: this.config.emptyText ?? "暂无数据!",
			actions: this.config.actions ?? [],
			topActions: this.config.topActions ?? [],
			indexed: this.config.indexed ?? false,
			actionWidth: this.config.actionWidth ?? "90px",
			selectable: this.config.selectable ?? false,
			selectFunc: this.config.selectFunc ?? (() => true),
			height: this.config.height ?? 2000,
			expand: this.config.expand ?? false, // 是否有展开列
			rowClassName: this.config.rowClassName ?? (() => ""), // 是否自动加载数据
			autoLoad: this.config.autoLoad ?? true, // 是否自动加载数据
			showSummary: this.config.showSummary ?? false, // 是否显示求和行
			summaryFields: this.config.summaryFields ?? [], // 求和字段
			rowClick: this.config.rowClick ?? (() => {}), // 行点击
			selectSingle: this.config.selectSingle ?? false, // 单选
			spanMergeIndex: this.config.spanMergeIndex ?? [], // 合并列
			paginateLayout: this.config.paginateLayout ?? "total, sizes, prev, pager, next, jumper", // 分页布局
			showDiyButtons: this.config.showDiyButtons ?? true, // 是否显示刷新和自定义列操作按钮

			// 组件数据
			data: [],
			showPaginate: false,
			loading: false,
			params: {
				page: 1,
				pageSize: this.config.pageSize ?? 30,
			},
			firstOpen: true, // 有页码的页码会发送两次请求，第一次过滤掉。
			multipleSelectionVal: [],
			pagination: {
				total: 0, // 总共列表数据数量
				pageCount: 0,
			},

			sums: ["合计"],

			// 被选中的显示列
			checkedLabels: [],

			columnFields: [],
		};
	},
	computed: {
		// fields: {
		//   get: function () {
		//      return this.config.fields || []
		//   },
		//   set: function (newValue) {
		//     return newValue
		//   }
		// }
		// fields: function () {
		//   return this.config.fields || []
		// },
	},
	watch: {
		"config.fields": {
			handler(newVal, oldVal) {
				this.columnFields = newVal;
			},
			immediate: true,
		},
		selectedRows: function (v) {
			// 计算合计行
			const sums = [];
			this.$refs.tableBuilder.columns.forEach((column, index) => {
				if (index === 0) {
					sums[index] = "合计";
					return;
				}
				for (const f of this.summaryFields) {
					if (f === column.property) {
						const values = this.selectedRows.map((item) => Number(item[column.property]));
						if (!values.every((value) => isNaN(value))) {
							sums[index] = values.reduce((prev, curr) => {
								const value = Number(curr);
								if (!isNaN(value)) {
									return prev + curr;
								} else {
									return prev;
								}
							}, 0);
						} else {
							sums[index] = "";
						}
					}
				}
			});
			this.sums = sums;
		},
	},
	mounted() {
		if (this.autoLoad) {
			this.loadData();
		}
		// 自动高度 todo
		// this.$nextTick(() => {
		//   this.height = this.height ? this.height : (window.innerHeight - this.$refs.tableBuilder.$el.offsetTop - 65);
		// })
	},
	methods: {
		loadData() {
			if (this.url === "") {
				return;
			}
			this.loading = true;
			request({
				url: this.url,
				method: "get",
				params: Object.assign({}, this.params, this.config.condition || {}),
			}).then((res) => {
				this.loading = false;
				if (res.page && res.pageSize) {
					this.showPaginate = true;
					this.data = res.records;
					this.firstOpen = false;

					this.params.page = res.page;
					this.params.pageSize = res.pageSize;

					this.pagination.total = res.total;
					this.pagination.pageCount = res.pageCount;
				} else {
					this.data = res;
				}
			});
		},
		clearSelection() {
			this.$refs.tableBuilder.clearSelection();
		},
		handleSelectionChange(val) {
			if (this.selectSingle) {
				if (val.length == 0) {
					this.$emit("update:selectedRows", []);
					return;
				}
				this.data.forEach((item) => {
					if (val[val.length - 1] === item) {
						this.$emit("update:selectedRows", [item]);
						this.$refs.tableBuilder.toggleRowSelection(item, true);
					} else {
						this.$refs.tableBuilder.toggleRowSelection(item, false);
					}
				});
			} else {
				this.multipleSelectionVal = val;
				this.$emit("update:selectedRows", val);
			}
		},
		handleSortChange(params) {
			if (params.column) {
				let sortType;
				if (params.order === "ascending") {
					sortType = "asc";
				} else if (params.order === "descending") {
					sortType = "desc";
				} else {
					sortType = "";
				}
				this.$emit("onSort", {
					sortLabel: params.column.label,
					sortBy: params.prop,
					sortType,
				});
			}
		},
		handleRowClick(row) {
			this.$refs.tableBuilder.toggleRowSelection(row);
			this.rowClick(row);
		},
		handleCurrentChange(val) {
			this.params.page = val;
			this.condition.page = val;
			this.firstOpen || this.loadData(); // 有页码的页码会发送两次请求，第一次过滤掉。
		},
		handleSizeChange(val) {
			this.params.pageSize = val;
			this.firstOpen || this.loadData();
		},
		indexMethod(index) {
			return (this.params.page - 1) * this.params.pageSize + index + 1;
		},
		// 按钮显示逻辑
		handleButtonVisible(item, row) {
			var hasPermission = true;
			if (item.pms) {
				hasPermission = checkPermission(item.pms);
			}
			if (typeof item.visible === "undefined") {
				return hasPermission;
			} else if (typeof item.visible === "boolean") {
				return this.visible && hasPermission;
			} else if (typeof item.visible === "function") {
				return item.visible(row) && hasPermission;
			}
		},
		handleMultiButtonVisible(item) {
			if (typeof item.visible != "undefined") {
				return !!item.visible;
			} else if (typeof item.pms == "undefined") {
				return true;
			} else {
				return checkPermission(item.pms);
			}
		},
		handleToggleExpansion(row) {
			if (this.expand) {
				this.$refs.tableBuilder.toggleRowExpansion(row);
			}
		},
		// 获取合并的数组
		spanFlitterData(fieldName) {
			let spanOneArr = [];
			let concatOne = 0;
			this.data.forEach((item, index) => {
				if (index === 0) {
					spanOneArr.push(1);
				} else {
					if (item[fieldName] === this.data[index - 1][fieldName]) {
						//第一列需合并相同内容的判断条件
						spanOneArr[concatOne] += 1;
						spanOneArr.push(0);
					} else {
						spanOneArr.push(1);
						concatOne = index;
					}
				}
			});
			return spanOneArr;
		},
		objectSpanMethod({ row, column, rowIndex, columnIndex }) {
			if (this.spanMergeIndex.length > 0) {
				for (var i of this.spanMergeIndex) {
					if (columnIndex === i) {
						const _row = this.spanFlitterData(column.property)[rowIndex];
						const _col = _row > 0 ? 1 : 0;
						return {
							rowspan: _row,
							colspan: _col,
						};
					}
				}
			}
		},
		handleRefresh() {
			this.loadData();
		},
		visibleColumn() {
			let res = [];
			for (var f of this.config.fields) {
				for (var l of this.checkedLabels) {
					if (f.title == l) {
						let f1 = Object.assign({}, f);
						f1.visible = function (data) {
							return true;
						};
						res.push(f1);
					}
				}
			}
			this.columnFields = res;
		},
		resetVisibleColumn() {
			this.columnFields = this.config.fields || [];
			this.checkedLabels = [];
		},
	},
};
</script>
<style lang="scss" scoped>
.action-column {
	text-align: center !important;
}
.fixed-bottom {
	// position: absolute;
	// bottom: 0px;
}
</style>
