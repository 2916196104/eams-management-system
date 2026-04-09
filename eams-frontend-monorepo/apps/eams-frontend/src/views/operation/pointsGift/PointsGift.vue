<template>
	<FilterToolbar
		@refresh="refresh"
		@print="print"
		@column-setting="handleColumnSetting"
		@search="search"
		@reset="clear"
	>
		<template #left>
			<div class="filter-grid">
				<div class="filter-item">
					<span>礼品名称：</span>
					<el-input v-model="form.searchTitle" placeholder="请输入" clearable />
				</div>
				<div class="filter-item">
					<span>状态：</span>
					<el-select v-model="form.enabled" placeholder="请选择状态">
						<el-option label="启用" value="1" />
						<el-option label="禁用" value="0" />
					</el-select>
				</div>
			</div>
			<div class="btn">
				<el-button type="primary" @click="addGiftClick" size="small">新增</el-button>
				<el-button @click="deleteClick" size="small">
					<el-icon><DeleteFilled /></el-icon>
					<span>删除</span>
				</el-button>
				<el-button @click="handleEnable" size="small">
					<el-icon><Check /></el-icon>
					启用
				</el-button>
				<el-button @click="handleDisable" size="small">
					<el-icon><Close /></el-icon>
					禁用
				</el-button>
			</div>
		</template>
	</FilterToolbar>

	<MyTable
		:istabmultiple="true"
		:tabdatacolumns="visibleColumns"
		:tabdata="tabdata"
		:tabtitle="''"
		:istabexpand="false"
		:istabseq="false"
		:istabpage="true"
		:istabselection="true"
		:taboperbtns="taboperbtns"
		@selection-change="handleSelectionChange"
		@taboper-click="editClick"
	/>

	<MyFormDialog ref="formDialog" v-bind="formDialogProps" @confirm="onSubmit">
		<template #itemdefault="{ item }">
			<!-- 图片上传 -->
			<el-upload
				v-if="item.prop === 'avatar'"
				class="avatar-uploader"
				action="https://jsonplaceholder.typicode.com/posts/"
				:show-file-list="false"
				@success="handleUploadSuccess"
			>
				<el-button class="avatar-uploader-icon" type="primary" icon="IconUpload">上传</el-button>
			</el-upload>

			<!-- 物料选择器：v-model绑定materialName，display-prop指定显示名称，校验直接绑定materialName -->
			<SelectTablePopover
				v-else-if="item.prop === 'materialName'"
				v-model="formDialogProps.data.materialName"
				display-prop="name"
				:search-fields="materialSearchFields"
				:columns="materialColumns"
				:data="materialData"
				placeholder="请选择物料"
				@select="onMaterialSelect"
			/>

			<!-- 分类选择器：直接用el-select，v-model绑定category，彻底解决绑定问题 -->
			<el-select
				v-else-if="item.prop === 'category'"
				v-model="formDialogProps.data.category"
				placeholder="请选择所属分类"
				style="width: 100%"
			>
				<el-option v-for="opt in categoryOptions" :key="opt.value" :label="opt.label" :value="opt.value" />
			</el-select>

			<!-- 其他字段默认渲染 -->
			<my-form-render
				v-else
				:item="item"
				:model="formDialogProps.data[item.prop]"
				@update:model="(val: unknown) => (formDialogProps.data[item.prop] = val)"
			/>
		</template>
	</MyFormDialog>

	<PrintTable
		ref="printRef"
		print-title="学生积分记录表"
		:column-list="tabdatacolumns"
		:table-data="tabdata.rows || []"
	/>

	<ColumnSetting
		v-model="columnSettingVisible"
		:columns="allColumns"
		@change="handleColumnChange"
		@confirm="handleColumnConfirm"
		@reset="handleColumnReset"
	/>
</template>

<script setup lang="ts">
import FilterToolbar from "@/views/material/components/FilterToolbar.vue";
import { ref, reactive, onMounted } from "vue";
import { DeleteFilled, Check, Close } from "@element-plus/icons-vue";
import MyTable from "@/components/mytable/MyTable.vue";
import type { PageDTO, MyTableColumn, MyTableOperationsBtn } from "@/components/mytable/type";
import MyFormDialog from "@/components/mydialog/MyFormDialog.vue";
import type { MyFormDialogProps } from "@/components/mydialog/type";
import type { MyFormItemAttr } from "@/components/myform/type";
import ColumnSetting from "../components/ColumnSetting.vue";
import PrintTable from "../components/PrintTable.vue";
import type { ColumnOption } from "../components/ColumnSetting.vue";
import { computed } from "vue";
import { getGiftList, deleteGift, useOrbanGift, saveGift } from "@/apis/operation/pointsGift";
import type { GiftList, SaveGiftParams } from "@/apis/operation/pointsGift/type";
import { ElMessage, ElMessageBox } from "element-plus";
import SelectTablePopover from "@/views/material/components/SelectTablePopover.vue";
import type { SearchField } from "@/views/material/components/type";

interface GiftFormData extends Record<string, any> {
	id: number | null;
	giftName: string;
	materialId: string;
	materialName: string;
	category: string;
	points: number;
	giftDesc: string;
	avatar: string;
}

// ==================== 状态变量 ====================
const columnSettingVisible = ref(false);
const originalRows = ref<GiftList[]>([]);
const selectedRows = ref<GiftList[]>([]);

// ==================== 分类配置 ====================
const categoryOptions = ref([
	{ label: "玩具", value: "玩具" },
	{ label: "书籍", value: "书籍" },
	{ label: "学习用品", value: "学习用品" },
	{ label: "花", value: "花" },
]);

// ==================== 物料选择配置 ====================
const materialSearchFields = ref<SearchField[]>([{ label: "物料名称", prop: "name", component: "input" }]);
const materialColumns = ref([
	{ label: "物料ID", prop: "id", width: 100 },
	{ label: "物料名称", prop: "name" },
	{ label: "库存", prop: "stock" },
]);
const materialData = ref([
	{ id: 1, name: "笔记本", stock: 100 },
	{ id: 2, name: "钢笔", stock: 200 },
	{ id: 3, name: "书包", stock: 50 },
]);

// 选择物料时，同时回填materialId（提交用）和materialName（显示+校验用）
const onMaterialSelect = (row: any) => {
	formDialogProps.data.materialId = row.id;
	formDialogProps.data.materialName = row.name;
};

// 图片上传成功回调
const handleUploadSuccess = (response: any) => {
	formDialogProps.data.avatar = response.url || "https://placehold.co/100x100";
	ElMessage.success("图片上传成功");
};

// ==================== 列配置 ====================
const allColumns = ref<ColumnOption[]>([
	{ label: "图片", prop: "image", visible: true },
	{ label: "礼品名称", prop: "giftName", visible: true },
	{ label: "所属学校", prop: "schoolName", visible: true },
	{ label: "兑换所需积分", prop: "points", visible: true },
	{ label: "已兑换数量", prop: "redeemedCount", visible: true },
	{ label: "浏览次数", prop: "viewCount", visible: true },
	{ label: "最后编辑时间", prop: "lastEditTime", visible: true },
	{ label: "状态", prop: "state", visible: true },
	{ label: "操作", prop: "operate", visible: true },
]);
const visibleColumns = computed(() => allColumns.value.filter((col) => col.visible));

// ==================== 表格列 ====================
const tabdatacolumns = ref<MyTableColumn[]>([
	{ label: "图片", prop: "image", fixed: "left", width: "100" },
	{ label: "礼品名称", prop: "giftName" },
	{ label: "所属学校", prop: "schoolName" },
	{ label: "兑换所需积分", prop: "points" },
	{ label: "已兑换数量", prop: "redeemedCount" },
	{ label: "浏览次数", prop: "viewCount" },
	{ label: "最后编辑时间", prop: "lastEditTime" },
	{ label: "状态", prop: "state" },
	{ label: "操作", prop: "operate", width: "120", fixed: "right" },
]);

// ==================== 操作按钮 ====================
const taboperbtns = ref<MyTableOperationsBtn[]>([
	{
		text: "编辑",
		evtname: "edit",
		attr: { type: "primary", link: true, style: { color: "#409eff", border: "none", background: "transparent" } },
	},
]);

// ==================== 表格数据 ====================
const tabdata = ref<PageDTO<GiftList>>({
	rows: [
		{
			id: 1,
			image: "https://placehold.co/64x64",
			giftName: "礼品A",
			schoolName: "学校A",
			points: 100,
			redeemedCount: 50,
			viewCount: 200,
			lastEditTime: "2023-10-01 10:00:00",
			state: "启用",
			materialId: 1,
			materialName: "笔记本",
			category: "学习用品",
		},
		{
			id: 2,
			image: "https://placehold.co/64x64",
			giftName: "礼品B",
			schoolName: "学校B",
			points: 200,
			redeemedCount: 30,
			viewCount: 150,
			lastEditTime: "2023-10-02 11:00:00",
			state: "禁用",
			materialId: 2,
			materialName: "钢笔",
			category: "书籍",
		},
	],
	total: 2,
	pageIndex: 1,
	pageSize: 10,
});

// ==================== 搜索 ====================
const form = reactive({ searchTitle: "", enabled: "" });

// ==================== 弹窗配置（终极修复：校验字段和绑定字段完全一致） ====================
const formDialog = ref();
const formDialogProps = reactive<MyFormDialogProps<GiftFormData>>({
	data: reactive<GiftFormData>({
		id: null,
		giftName: "",
		materialId: "", // 后端需要的ID，不参与校验
		materialName: "", // 显示+校验用，和SelectTablePopover的v-model绑定
		category: "",
		points: 0,
		giftDesc: "",
		avatar: "",
	}),
	formitemdata: reactive<MyFormItemAttr[]>([
		{
			type: "input",
			prop: "giftName",
			label: "礼品名称",
		},
		{
			type: "input",
			prop: "materialName", // 校验字段改成materialName，和v-model绑定一致
			label: "选择物料",
		},
		{
			type: "select",
			prop: "category",
			label: "所属分类",
		},
		{
			type: "number",
			prop: "points",
			label: "兑换积分",
			fprops: { width: "100%" },
		},
		{
			type: "input",
			prop: "giftDesc",
			label: "礼品说明",
			fprops: { type: "textarea", rows: 4 },
		},
		{
			type: "file",
			prop: "avatar",
			label: "图片",
		},
	]),
	formattr: { "label-width": "80px" },
	title: "新增礼品",
	width: "35vw",
});

// ==================== 工具方法 ====================
const printRef = ref();
const print = () => printRef.value?.handlePrint();
const handleColumnSetting = () => (columnSettingVisible.value = true);
const handleColumnChange = (cols: ColumnOption[]) => (allColumns.value = cols);
const handleColumnConfirm = (cols: ColumnOption[]) => {
	allColumns.value = cols;
	localStorage.setItem("creditExchangeColumns", JSON.stringify(cols));
};
const handleColumnReset = () => allColumns.value.forEach((c) => (c.visible = true));
const handleSelectionChange = (rows: GiftList[]) => (selectedRows.value = rows);

// ==================== 刷新 / 搜索 / 清空 ====================
const refresh = () => {
	getGiftList({ name: form.searchTitle, state: form.enabled ? +form.enabled : undefined }).then((res) => {
		tabdata.value.rows = res.data?.rows || [];
		originalRows.value = res.data?.rows || [];
	});
};
const search = () => {
	let filtered = [...originalRows.value];
	if (form.searchTitle) filtered = filtered.filter((r) => r.giftName?.includes(form.searchTitle));
	if (form.enabled)
		filtered = filtered.filter((r) => String(r.state ?? "") === (form.enabled === "1" ? "启用" : "禁用"));
	tabdata.value.rows = filtered;
};
const clear = () => {
	Object.assign(form, { searchTitle: "", enabled: "" });
	refresh();
};

// ==================== 新增 / 编辑（修复回填） ====================
const addGiftClick = () => {
	Object.assign(formDialogProps.data, {
		id: null,
		giftName: "",
		materialId: "",
		materialName: "",
		category: "",
		points: 0,
		giftDesc: "",
		avatar: "",
	});
	formDialogProps.title = "新增礼品";
	formDialog.value?.openDialog(true);
};
const editClick = (_index: number, row: GiftList, evtname: string) => {
	if (evtname === "edit") {
		Object.assign(formDialogProps.data, {
			...row,
			materialId: row.materialId,
			materialName: row.materialName,
			category: row.category,
		});
		formDialogProps.title = "修改礼品";
		formDialog.value?.openDialog(true);
	}
};

// ==================== 完善的onSubmit函数 ====================
const onSubmit = async (data: GiftFormData) => {
	if (!data) {
		ElMessage.warning("请完善必填项");
		return;
	}

	const { giftName, materialId, materialName, category, points, giftDesc, avatar, id } = data;

	// 前端二次校验，双重保障
	if (!giftName?.trim()) {
		ElMessage.warning("请输入礼品名称");
		return;
	}
	if (!materialName || !materialId) {
		ElMessage.warning("请选择物料");
		return;
	}
	if (!category) {
		ElMessage.warning("请选择所属分类");
		return;
	}
	if (points === undefined || points === null || points < 0) {
		ElMessage.warning("请输入合法的兑换积分");
		return;
	}

	// 分类名称→ID映射（根据后端实际分类ID调整）
	const categoryIdMap: Record<string, number> = {
		玩具: 1,
		书籍: 2,
		学习用品: 3,
		花: 4,
	};
	const categoryId = categoryIdMap[category];
	if (categoryId === undefined) {
		ElMessage.error("分类配置错误，请联系管理员");
		return;
	}

	// 构造接口参数（完全匹配接口要求）
	const requestParams: SaveGiftParams = {
		name: giftName.trim(),
		materialId: String(materialId), // 提交用materialId，后端需要
		categoryId,
		credit: Number(points),
		content: giftDesc?.trim() || "",
		cover: avatar || "",
	};
	if (id) requestParams.id = id;

	console.log("最终提交参数：", requestParams);

	try {
		const res = await saveGift(requestParams);
		// 判断后端业务状态
		if (res.code === 10000 || res.code === 200) {
			ElMessage.success(id ? "修改成功" : "新增成功");
			formDialog.value?.closeDialog();
			refresh();
			// 重置表单
			Object.assign(formDialogProps.data, {
				id: null,
				giftName: "",
				materialId: "",
				materialName: "",
				category: "",
				points: 0,
				giftDesc: "",
				avatar: "",
			});
		} else {
			ElMessage.error(`保存失败：${res.message || "未知错误"}`);
		}
	} catch (error) {
		console.error("保存失败：", error);
		ElMessage.error("保存失败，请重试");
	}
};

// ==================== 删除 / 启用 / 禁用 ====================
const deleteClick = () => {
	if (!selectedRows.value.length) return ElMessage.warning("请选择");
	ElMessageBox.confirm("确定删除？")
		.then(async () => {
			await deleteGift({
				name: selectedRows.value.map((r) => r.giftName).filter((name): name is string => Boolean(name)),
			});
			ElMessage.success("删除成功");
			refresh();
			selectedRows.value = [];
		})
		.catch(() => {});
};
const handleEnable = () => {
	if (!selectedRows.value.length) return ElMessage.warning("请选择");
	ElMessageBox.confirm("确定启用？")
		.then(async () => {
			await useOrbanGift({
				ids: selectedRows.value.map((r) => r.id).filter((id): id is string | number => id !== undefined),
				status: 1,
			});
			ElMessage.success("启用成功");
			refresh();
			selectedRows.value = [];
		})
		.catch(() => {});
};
const handleDisable = () => {
	if (!selectedRows.value.length) return ElMessage.warning("请选择");
	ElMessageBox.confirm("确定禁用？")
		.then(async () => {
			await useOrbanGift({
				ids: selectedRows.value.map((r) => r.id).filter((id): id is string | number => id !== undefined),
				status: 0,
			});
			ElMessage.success("禁用成功");
			refresh();
			selectedRows.value = [];
		})
		.catch(() => {});
};

onMounted(() => {
	refresh();
});
</script>

<style scoped>
.filter-grid {
	display: flex;
	flex-wrap: wrap;
	gap: 16px;
}
.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
	flex: 1;
	min-width: 0;
}
.filter-item span {
	white-space: nowrap;
}
.btn {
	display: flex;
	gap: 8px;
	margin-top: 20px;
}
.my-table-operate-btn {
	display: flex;
	gap: 8px;
	align-items: center;
}
.avatar-uploader {
	margin-top: 8px;
}
</style>
