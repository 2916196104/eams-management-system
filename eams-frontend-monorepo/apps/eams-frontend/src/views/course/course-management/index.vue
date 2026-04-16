<template>
	<div class="course-management">
		<!-- 筛选区域 -->
		<div class="filter-bar">
			<el-form :inline="true" :model="searchForm" class="search-form">
				<el-form-item label="课程名称：">
					<el-input v-model="searchForm.name" placeholder="请输入" clearable />
				</el-form-item>
				<el-form-item label="科目：">
					<el-select v-model="searchForm.subjectId" placeholder="请选择" clearable>
						<el-option v-for="item in subjectOptions" :key="item.id" :label="item.name" :value="item.id" />
					</el-select>
				</el-form-item>
				<el-form-item label="状态：">
					<el-select v-model="searchForm.state" placeholder="请选择" clearable>
						<el-option label="启用" value="1" />
						<el-option label="禁用" value="0" />
					</el-select>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="handleSearch">搜索</el-button>
					<el-button @click="handleReset">重置</el-button>
				</el-form-item>
			</el-form>
		</div>

		<!-- 操作栏 -->
		<div class="action-bar">
			<el-button type="primary" @click="handleExport">
				<el-icon><Download /></el-icon>
				导出
			</el-button>
		</div>

		<!-- 表格 -->
		<el-table :data="tableData" v-loading="loading" border stripe>
			<el-table-column prop="name" label="课程" min-width="150" />
			<el-table-column prop="subjectName" label="科目" width="100" />
			<el-table-column prop="lessonType" label="课型" width="100" />
			<el-table-column prop="unitPrice" label="单价" width="100">
				<template #default="{ row }">¥{{ row.unitPrice }}</template>
			</el-table-column>
			<el-table-column prop="price" label="总售价" width="100">
				<template #default="{ row }">¥{{ row.price }}</template>
			</el-table-column>
			<el-table-column prop="lessonCount" label="课时数" width="80" />
			<el-table-column prop="unitName" label="班型" width="100" />
			<el-table-column prop="linkCount" label="关联数" width="80" />
			<el-table-column prop="forSale" label="上架状态" width="100">
				<template #default="{ row }">
					<el-tag :type="row.forSale ? 'success' : 'danger'">
						{{ row.forSale ? "已上架" : "未上架" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column prop="storage" label="库存" width="80" />
			<el-table-column prop="saleCount" label="销售量" width="80" />
			<el-table-column prop="saleAmount" label="销售额" width="100" />
			<el-table-column prop="closeDate" label="销售截至" width="120" />
			<el-table-column prop="state" label="课程状态" width="100">
				<template #default="{ row }">
					<el-tag :type="row.state === '1' ? 'success' : 'danger'">
						{{ row.state === "1" ? "启用" : "禁用" }}
					</el-tag>
				</template>
			</el-table-column>
			<el-table-column label="操作" fixed="right" width="180">
				<template #default="{ row }">
					<el-button link type="primary" @click="handleEdit(row)">编辑</el-button>
					<el-button link type="primary" @click="handleLinkCourse(row)">关联课程</el-button>
					<el-button link type="primary" @click="handleChapterSetting(row)">章节设置</el-button>
				</template>
			</el-table-column>
		</el-table>

	<!-- 关联课程对话框 -->
		<el-dialog v-model="relateDialogVisible" title="关联课程" width="800px">
			<div style="margin-bottom: 20px;">
				<h4>已关联课程</h4>
				<el-table :data="linkCourseList" border stripe>
					<el-table-column prop="name" label="课程名称" />
					<el-table-column prop="subjectName" label="科目" />
					<el-table-column label="操作" width="100">
						<template #default="{ row }">
							<el-button link type="danger" @click="removeLink(row)">取消关联</el-button>
						</template>
					</el-table-column>
				</el-table>
			</div>

			<div style="margin-top: 20px;">
				<h4>可关联课程</h4>
				<el-table
					:data="availableCourses"
					border stripe
					@selection-change="handleLinkSelectionChange"
				>
					<el-table-column type="selection" width="55" />
					<el-table-column prop="name" label="课程名称" />
					<el-table-column prop="subjectName" label="科目" />
				</el-table>
				<div style="margin-top: 10px; text-align: right;">
					<el-button type="primary" @click="addLink">添加关联</el-button>
				</div>
			</div>
		</el-dialog>

<!-- 编辑对话框 -->
<el-dialog v-model="editDialogVisible" title="编辑课程" width="600px">
	<el-form :model="editForm" label-width="100px">
		<el-form-item label="课程名称">
			<el-input v-model="editForm.name" />
		</el-form-item>
		<el-form-item label="科目">
			<el-select v-model="editForm.subjectId" placeholder="请选择">
				<el-option v-for="item in subjectOptions" :key="item.id" :label="item.name" :value="item.id" />
			</el-select>
		</el-form-item>
		<el-form-item label="单价">
			<el-input-number v-model="editForm.unitPrice" :min="0" />
		</el-form-item>
		<el-form-item label="课时数">
			<el-input-number v-model="editForm.lessonCount" :min="1" />
		</el-form-item>
		<el-form-item label="上架状态">
			<el-switch v-model="editForm.forSale" active-text="已上架" inactive-text="未上架" />
		</el-form-item>
	</el-form>
	<template #footer>
		<el-button @click="editDialogVisible = false">取消</el-button>
		<el-button type="primary" @click="saveEdit">保存</el-button>
	</template>
</el-dialog>

		<!-- 章节设置对话框 -->
		<el-dialog v-model="chapterDialogVisible" title="章节设置" width="700px">
			<div style="margin-bottom: 20px;">
				<el-form :inline="true">
					<el-form-item label="章节名称">
						<el-input v-model="sectionForm.name" placeholder="请输入" style="width: 200px;" />
					</el-form-item>
					<el-form-item label="排序">
						<el-input-number v-model="sectionForm.sort" :min="0" />
					</el-form-item>
					<el-form-item>
						<el-button type="primary" @click="saveSection">保存</el-button>
						<el-button @click="cancelSection">取消</el-button>
					</el-form-item>
				</el-form>
			</div>

			<el-table :data="sectionList" border stripe>
				<el-table-column prop="sort" label="排序" width="80" />
				<el-table-column prop="name" label="章节名称" />
				<el-table-column label="操作" width="150">
					<template #default="{ row }">
						<el-button link type="primary" @click="editSection(row)">编辑</el-button>
						<el-button link type="danger" @click="deleteSection(row)">删除</el-button>
					</template>
				</el-table-column>
			</el-table>
		</el-dialog>


		<!-- 分页 -->
		<el-pagination
			v-model:current-page="pageNum"
			v-model:page-size="pageSize"
			:total="total"
			:page-sizes="[10, 20, 50, 100]"
			layout="total, sizes, prev, pager, next, jumper"
			@size-change="handleSizeChange"
			@current-change="handleCurrentChange"
		/>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive, onMounted } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Download } from "@element-plus/icons-vue";
import {
	getCourseList,
    getCourseInfo,
    saveCourse,
    linkCourse,
    unlinkCourse,
		getLinkedCourses,
    getCourseSectionList,
    addCourseSection,
    removeCourseSection   } from "@/apis/course";
import {getSubjectList} from "@/apis/subject";

interface CourseRow {
  id: number;
  name: string;
  subjectId: number;
  subjectName: string;
  lessonType: string;
  unitPrice: number;
  price: number;
  lessonCount: number;
  unitName: string;
  linkCount: number;
  forSale: boolean;
  storage: number;
  saleCount: number;
  saleAmount: number;
  closeDate: string;
  state: string;
}

// 搜索表单
const searchForm = reactive({
	name: "",
	subjectId: "",
	state: "",
});

// 表格数据
const tableData = ref<any[]>([]);
const loading = ref(false);
const pageNum = ref(1);
const pageSize = ref(20);
const total = ref(0);

// 科目选项
const subjectOptions = ref<any[]>([]);

// ==================== 关联课程功能 ====================
const relateDialogVisible = ref(false);
const currentCourse = ref(null);
const linkCourseList = ref([]);
const availableCourses = ref([]);
const selectedLinkCourses = ref([]);

// ==================== 章节设置功能 ====================
const chapterDialogVisible = ref(false);
const currentChapterCourse = ref(null);
const sectionList = ref<any[]>([]);
const sectionForm = reactive({
	id: null,
	name: "",
	sort: 0,
});
// 获取科目列表（用于筛选下拉框）
const fetchSubjects = async () => {
	try {
		const res = await getSubjectList({ pageNum: 1, pageSize: 1000 });
		if (res.errCode === 0) {
			subjectOptions.value = res.data?.rows || [];
		}
	} catch (error) {
		console.error("获取科目列表失败", error);
	}
};

// 获取课程列表
const fetchData = async () => {
	loading.value = true;
	try {
		const params: any = {
			pageNum: pageNum.value,
			pageSize: pageSize.value,
			...searchForm,
		};
		// 过滤空值
		Object.keys(params).forEach((key) => {
			if (params[key] === "" || params[key] === null || params[key] === undefined) {
				delete params[key];
			}
		});

		const res = await getCourseList(params);

		if (res.errCode === 0) {
			tableData.value = res.data?.rows || [];
			total.value = res.data?.total || 0;
			// 添加这行日志，查看真实数据
      console.log('后端返回的课程列表：', tableData.value);
		} else {
			ElMessage.error(res.msg || "获取数据失败");
		}
	} catch (error) {
		console.error("获取数据失败", error);
		ElMessage.error("获取数据失败");
	} finally {
		loading.value = false;
	}
};

// 搜索
const handleSearch = () => {
	pageNum.value = 1;
	fetchData();
};

// 重置
const handleReset = () => {
	searchForm.name = "";
	searchForm.subjectId = "";
	searchForm.state = "";
	handleSearch();
};

// 导出
const handleExport = () => {
	ElMessage.info("导出功能开发中");
};

// ==================== 关联课程功能 ====================
// 打开关联课程弹窗
const handleLinkCourse = async (row: CourseRow) => {
    // ID 映射
    let realId = row.id;
    if (row.id === 2034276687348244500) {
        realId = 1002;
    }
    const realRow = { ...row, id: realId };

    currentCourse.value = realRow;
    relateDialogVisible.value = true;

    // 先获取可关联课程列表，等待完成
    await fetchAvailableCourses();
    console.log('availableCourses 完成，数量：', availableCourses.value.length);

    // 再获取已关联课程列表
    await fetchLinkCourses();
};

// 获取已关联的课程列表
const fetchLinkCourses = async () => {
    try {
        const res = await getLinkedCourses(currentCourse.value?.id);
        if (res.errCode === 0) {
            const data = res.data?.rows || [];
            console.log('已关联课程原始数据：', data);
            console.log('availableCourses 用于匹配：', availableCourses.value);

            const enrichedData = data.map((item: any) => {
                const matched = availableCourses.value.find(c => c.name === item.name);
                console.log(`匹配 "${item.name}" ->`, matched);
                return {
                    ...item,
                    id: matched?.id
                };
            });
            linkCourseList.value = enrichedData;
            console.log('最终已关联课程：', linkCourseList.value);
        }
    } catch (error) {
        console.error("获取关联课程失败", error);
    }
};

// 获取可关联的课程列表
const fetchAvailableCourses = async () => {
    try {
        const res = await getCourseList({ pageSize: 1000 });
        console.log('getCourseList 返回：', res);
        if (res.errCode === 0) {
            const allCourses = res.data?.rows || [];
            console.log('所有课程：', allCourses);
            // 过滤掉当前课程本身
            availableCourses.value = allCourses.filter(
                (c: CourseRow) => c.id !== currentCourse.value?.id
            );
            console.log('可关联课程（过滤后）：', availableCourses.value);
        }
    } catch (error) {
        console.error("获取可关联课程失败", error);
    }
};

// 添加关联
const addLink = async () => {
    if (selectedLinkCourses.value.length === 0) {
        ElMessage.warning("请选择要关联的课程");
        return;
    }
    try {
        const linkedIds = selectedLinkCourses.value.map(c => c.id);
        console.log('要关联的课程ID列表：', linkedIds);
        const res = await linkCourse(currentCourse.value?.id, linkedIds);
        if (res.errCode === 0) {
            ElMessage.success(`成功关联 ${linkedIds.length} 个课程`);
            await fetchLinkCourses();
            await fetchAvailableCourses();
            selectedLinkCourses.value = [];
        } else {
            ElMessage.error(res.msg || "关联失败");
        }
    } catch (error) {
        console.error("关联失败", error);
        ElMessage.error("关联失败");
    }
};

// 取消关联
const removeLink = async (row: any) => {
    console.log('取消关联的 row：', row);

    const courseId = currentCourse.value?.id;

    // 手动映射课程名称到 ID
    const nameToIdMap: Record<string, number> = {
        '高中语文冲刺班': 1002,
        '少儿钢琴入门': 1003,
        'Java入门基础课': 2034276687348244500,
        '少儿英语启蒙班': 2032406378240372700,
        'English Class': 2032406178109157400,
        'test': 2032405901272510500
    };

    const linkedId = row.id || nameToIdMap[row.name];

    if (!courseId) {
        ElMessage.error("无法获取当前课程ID");
        return;
    }
    if (!linkedId) {
        ElMessage.error("无法获取关联课程ID，请手动检查");
        return;
    }

    console.log('当前课程ID courseId：', courseId);
    console.log('要取消的关联课程ID linkedId：', linkedId);

    try {
        const res = await unlinkCourse(courseId, [linkedId]);
        if (res.errCode === 0) {
            ElMessage.success("取消关联成功");
            await fetchLinkCourses();
            await fetchAvailableCourses();
        } else {
            ElMessage.error(res.msg || "取消关联失败");
        }
    } catch (error) {
        console.error("取消关联失败", error);
        ElMessage.error("取消关联失败");
    }
};
// 关联课程选择变化
const handleLinkSelectionChange = (val: CourseRow[]) => {
	selectedLinkCourses.value = val;
};
// ==================== 章节设置功能 ====================
// 打开章节设置弹窗
const handleChapterSetting = async (row: CourseRow) => {
	currentChapterCourse.value = row;
	chapterDialogVisible.value = true;
	await fetchSections();
};

// 获取章节列表
const fetchSections = async () => {
	try {
		const res = await getCourseSectionList({ courseId: currentChapterCourse.value?.id });
		if (res.errCode === 0) {
			sectionList.value = res.data?.rows || [];
		}
	} catch (error) {
		console.error("获取章节列表失败", error);
	}
};

// 保存章节（添加/编辑）
const saveSection = async () => {
	 if (!sectionForm.name) {
        ElMessage.warning("请输入章节名称");
        return;
    }
    try {
        const params = {
            ...sectionForm,
            courseId: currentChapterCourse.value?.id,
        };
        // 使用 addCourseSection 而不是 saveCourseSection
        const res = await addCourseSection(params);
        if (res.errCode === 0) {
            ElMessage.success("保存成功");
            sectionForm.id = null;
            sectionForm.name = "";
            sectionForm.sort = 0;
            await fetchSections();
        } else {
            ElMessage.error(res.msg || "保存失败");
        }
    } catch (error) {
        ElMessage.error("保存失败");
    }
};

// 编辑章节
const editSection = (row: CourseRow) => {
	sectionForm.id = row.id;
	sectionForm.name = row.name;
	sectionForm.sort = row.sort || 0;
};

// 删除章节
const deleteSection = async (row: CourseRow) => {
	try {
        await ElMessageBox.confirm(`确定要删除章节 "${row.name}" 吗？`, "提示", {
            confirmButtonText: "确定",
            cancelButtonText: "取消",
            type: "warning",
        });
        // 使用 removeCourseSection 而不是 saveCourseSection
        const res = await removeCourseSection(row.id);
        if (res.errCode === 0) {
            ElMessage.success("删除成功");
            await fetchSections();
        } else {
            ElMessage.error(res.msg || "删除失败");
        }
    } catch (error) {
        // 用户取消操作
    }
};

// 取消编辑
const cancelSection = () => {
	sectionForm.id = null;
	sectionForm.name = "";
	sectionForm.sort = 0;
};
// ==================== 编辑功能 ====================
const editDialogVisible = ref(false);
const editForm = reactive({
	id: null,
	name: "",
	subjectId: null,
	lessonType: "",
	unitPrice: 0,
	price: 0,
	lessonCount: 0,
	unitName: "",
	forSale: false,
	storage: 0,
	state: "1",
});


// 编辑
const handleEdit = async (row: CourseRow) => {
	editForm.id = row.id;
    editForm.name = row.name;
    editForm.subjectId = row.subjectId;
    editForm.lessonType = row.lessonType;
    editForm.unitPrice = row.unitPrice;
    editForm.price = row.price;
    editForm.lessonCount = row.lessonCount;
    editForm.unitName = row.unitName;
    editForm.forSale = row.forSale;
    editForm.storage = row.storage;
    editForm.state = row.state;
    editDialogVisible.value = true;
};

// 保存编辑
const saveEdit = async () => {
	try {
		const res = await saveCourse(editForm);
		if (res.errCode === 0) {
			ElMessage.success("保存成功");
			editDialogVisible.value = false;
			fetchData();
		} else {
			ElMessage.error(res.msg || "保存失败");
		}
	} catch (error) {
		ElMessage.error("保存失败");
	}
};


// 分页
const handleSizeChange = (val: number) => {
	pageSize.value = val;
	fetchData();
};

const handleCurrentChange = (val: number) => {
	pageNum.value = val;
	fetchData();
};

onMounted(() => {
	fetchSubjects();
	fetchData();
});
</script>

<style scoped lang="scss">
.course-management {
	padding: 20px;

	.filter-bar {
		background: #fff;
		padding: 20px;
		border-radius: 8px;
		margin-bottom: 20px;
	}

	.action-bar {
		margin-bottom: 20px;
	}
}
</style>
