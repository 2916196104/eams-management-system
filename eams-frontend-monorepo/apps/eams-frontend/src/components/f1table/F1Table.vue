<template>
	<!-- 表格容器 -->
	<div class="f1-table">
		<!--
            Element Plus el-table 表格组件
            :data         - 绑定表格数据源
            v-bind        - 绑定 el-table 的属性配置（如 stripe、border、height 等）
            :row-key      - 行唯一标识，用于复选框、展开行等功能
            v-loading     - 加载状态，显示加载遮罩
            @selection-change - 复选框选择变化事件
        -->
		<el-table
			:data="tableData"
			v-bind="config.tableProperties"
			:row-key="config.rowKey || 'id'"
			v-loading="config.loading"
			style="width: 100%"
			@selection-change="handleSelectionChange"
		>
			<!--
                遍历表格列配置，动态生成 el-table-column
                key 使用 prop 或 type + index 的组合，确保唯一性
            -->
			<template v-for="(item, index) in config.tableList" :key="item.prop ?? item.type + index">
				<!-- 序号列：显示行号 -->
				<template v-if="item.type === 'index'">
					<el-table-column align="center" v-bind="item" />
				</template>

				<!-- 复选框列：用于多选 -->
				<template v-else-if="item.type === 'selection'">
					<el-table-column align="center" v-bind="item" />
				</template>

				<!--
                    自定义列：通过插槽自定义单元格内容
                    slotName 属性指定插槽名称
                -->
				<template v-else-if="item.type === 'custom'">
					<el-table-column align="center" v-bind="item">
						<template #default="scope">
							<!--
                                将 scope 传递给具名插槽
                                scope 包含：row（行数据）、$index（行索引）、column（列配置）
                            -->
							<slot :name="item.slotName" v-bind="scope"></slot>
						</template>
					</el-table-column>
				</template>

				<!--
                    操作列：渲染操作按钮（查看、编辑、删除）
                    通过 handler 配置控制按钮的显示和文本
                -->
				<template v-else-if="item.type === 'handler'">
					<el-table-column align="center" v-bind="item">
						<template #default="scope">
							<!-- 操作按钮容器 -->
							<div class="handler-btns">
								<!-- 查看按钮 -->
								<el-button v-if="config.handler?.view" type="primary" link @click="handleView(scope.row)">
									{{ config.handler?.viewText || "查看" }}
								</el-button>

								<!-- 编辑按钮 -->
								<el-button v-if="config.handler?.edit" type="primary" link @click="handleEdit(scope.row)">
									{{ config.handler?.editText || "编辑" }}
								</el-button>

								<!-- 删除按钮 -->
								<el-button v-if="config.handler?.delete" type="danger" link @click="handleDelete(scope.row)">
									{{ config.handler?.deleteText || "删除" }}
								</el-button>

								<!--
                                    操作栏额外按钮插槽
                                    用于在操作栏中添加自定义按钮
                                    使用方式：<template #handler-extra="{ row }">
                                -->
								<slot name="handler-extra" v-bind="scope"></slot>
							</div>
						</template>
					</el-table-column>
				</template>

				<!-- 普通列：直接显示数据 -->
				<template v-else>
					<el-table-column align="center" v-bind="item" />
				</template>
			</template>
		</el-table>

		<!--
            分页组件
            v-if        - 仅当分页功能启用时显示
            :page-sizes - 可选的每页条数选项
            :total      - 数据总条数
        -->
		<div v-if="config.pagination?.enabled" class="pagination">
			<el-pagination
				v-model:current-page="currentPage"
				v-model:page-size="pageSize"
				:page-sizes="config.pagination.pageSizes || [10, 20, 50, 100]"
				size="small"
				:layout="config.pagination.layout || 'total, sizes, prev, pager, next, jumper'"
				:total="config.pagination.total"
				@current-change="handlePageChange"
				@size-change="handleSizeChange"
			/>
		</div>
	</div>
</template>

<script setup lang="ts">
/**
 * ============================================
 * 引入 Vue 响应式 API
 * ============================================
 * ref         - 创建响应式引用
 * computed    - 创建计算属性
 * watch       - 监听数据变化
 */
import { ref, computed, watch } from "vue";

/** 引入类型定义 */
import type { TableConfig } from "./type";

/**
 * ============================================
 * Props 定义
 * ============================================
 * 组件接收的外部属性
 */
interface Props {
	/**
	 * 表格配置对象
	 * 包含列配置、分页配置、操作栏配置等
	 */
	config: TableConfig;

	/**
	 * 表格数据数组
	 * 支持任意结构的数据对象
	 */
	data?: any[];
}

/**
 * 定义组件 Props，设置默认值
 * - config: 表格配置
 * - data: 空数组
 */
const props = withDefaults(defineProps<Props>(), {
	config: () => ({
		/** 默认开启斑马纹和边框 */
		tableProperties: {
			stripe: true,
			border: true,
		},
		/** 默认无列 */
		tableList: [],
		/** 默认启用分页 */
		pagination: {
			enabled: true,
			currentPage: 1,
			pageSize: 10,
			total: 0,
		},
		/** 默认非加载状态 */
		loading: false,
	}),
	data: () => [],
});

/**
 * ============================================
 * Emit 定义
 * ============================================
 * 组件向外部触发的事件
 */
const emit = defineEmits<{
	/**
	 * 分页变化事件
	 * @param page 变化后的页码
	 * @param size 变化后的每页条数
	 */
	(e: "page-change", page: number, size: number): void;

	/**
	 * 复选框选择变化事件
	 * @param selection 当前选中的所有行数据
	 */
	(e: "selection-change", selection: any[]): void;

	/**
	 * 编辑按钮点击事件
	 * @param row 当前行的数据
	 */
	(e: "edit", row: any): void;

	/**
	 * 删除按钮点击事件
	 * @param row 当前行的数据
	 */
	(e: "delete", row: any): void;

	/**
	 * 查看按钮点击事件
	 * @param row 当前行的数据
	 */
	(e: "view", row: any): void;
}>();

/**
 * ============================================
 * 响应式状态
 * ============================================
 * 当前页码和每页条数
 */
const currentPage = ref(props.config.pagination?.currentPage || 1);
const pageSize = ref(props.config.pagination?.pageSize || 10);

/**
 * ============================================
 * 计算属性
 * ============================================
 * 表格数据，直接返回 props.data
 */
const tableData = computed(() => {
	return props.data;
});

/**
 * ============================================
 * 监听器
 * ============================================
 * 监听 config.pagination.currentPage 的外部变化
 * 用于父组件直接修改 currentPage 时同步状态
 */
watch(
	() => props.config.pagination?.currentPage,
	(val) => {
		if (val) currentPage.value = val;
	},
);

/**
 * ============================================
 * 页码变化处理
 * ============================================
 * 当用户点击分页组件的页码时触发
 * @param page 新的页码
 */
function handlePageChange(page: number) {
	// 更新当前页码状态
	currentPage.value = page;
	// 调用配置中的回调函数（如果存在）
	props.config.pagination?.onPageChange?.(page, pageSize.value);
	// 触发 page-change 事件
	emit("page-change", page, pageSize.value);
}

/**
 * ============================================
 * 每页条数变化处理
 * ============================================
 * 当用户切换每页显示条数时触发
 * @param size 新的每页条数
 */
function handleSizeChange(size: number) {
	// 更新每页条数状态
	pageSize.value = size;
	// 重置到第一页
	currentPage.value = 1;
	// 调用配置中的回调函数（如果存在）
	props.config.pagination?.onPageChange?.(1, size);
	// 触发 page-change 事件
	emit("page-change", 1, size);
}

/**
 * ============================================
 * 复选框选择变化处理
 * ============================================
 * 当用户勾选/取消复选框时触发
 * @param selection 当前选中的所有行数据
 */
function handleSelectionChange(selection: any[]) {
	// 调用配置中的回调函数（如果存在）
	props.config.onSelectionChange?.(selection);
	// 触发 selection-change 事件
	emit("selection-change", selection);
}

/**
 * ============================================
 * 编辑按钮点击处理
 * ============================================
 * @param row 当前行的数据
 */
function handleEdit(row: any) {
	// 调用配置中的回调函数（如果存在）
	props.config.handler?.onEdit?.(row);
	// 触发 edit 事件
	emit("edit", row);
}

/**
 * ============================================
 * 删除按钮点击处理
 * ============================================
 * @param row 当前行的数据
 */
function handleDelete(row: any) {
	// 调用配置中的回调函数（如果存在）
	props.config.handler?.onDelete?.(row);
	// 触发 delete 事件
	emit("delete", row);
}

/**
 * ============================================
 * 查看按钮点击处理
 * ============================================
 * @param row 当前行的数据
 */
function handleView(row: any) {
	// 调用配置中的回调函数（如果存在）
	props.config.handler?.onView?.(row);
	// 触发 view 事件
	emit("view", row);
}

/**
 * ============================================
 * 暴露给父组件的属性和方法
 * ============================================
 * 允许父组件通过 ref 访问组件内部状态
 */
defineExpose({
	/** 当前页码 */
	currentPage,
	/** 每页条数 */
	pageSize,
});
</script>

<style scoped>
/* 表格容器样式 */
.f1-table {
	width: 100%;
}

/* 分页容器样式 */
.pagination {
	display: flex;
	justify-content: flex-end;
	margin-top: 16px;
	background: #fff;
	padding: 12px 0;
}

/* 操作按钮容器样式 */
.handler-btns {
	display: flex;
	gap: 8px;
	justify-content: center;
}
</style>
