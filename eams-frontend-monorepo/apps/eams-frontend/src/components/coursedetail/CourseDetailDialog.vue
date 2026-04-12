<template>
	<el-dialog v-model="dialogVisible" :title="dialogTitle" width="760px" :close-on-click-modal="false">
		<div class="course-detail-dialog">
			<div v-if="loading" class="detail-loading">正在加载课次详情...</div>
			<div v-else class="detail-grid">
				<div class="detail-item detail-item-wide">
					<label>标题</label>
					<div>{{ detailData?.title || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>课程名称</label>
					<div>{{ detailData?.courseName || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>课程编号</label>
					<div>{{ detailData?.courseNo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>班级名称</label>
					<div>{{ detailData?.className || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>班级编号</label>
					<div>{{ detailData?.classNo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>课程类型</label>
					<div>{{ detailData?.courseType || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>状态</label>
					<div>{{ detailData?.status || "--" }}</div>
				</div>
				<div class="detail-item detail-item-wide">
					<label>上课时间</label>
					<div>{{ detailData?.lessonTimeText || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>上课老师</label>
					<div>{{ detailData?.teacherName || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>老师编号</label>
					<div>{{ detailData?.teacherNo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>助教老师</label>
					<div>{{ detailData?.assistantName || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>助教编号</label>
					<div>{{ detailData?.assistantNo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>教室名称</label>
					<div>{{ detailData?.classroomName || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>教室编号</label>
					<div>{{ detailData?.classroomNo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>实到/应到</label>
					<div>{{ detailData?.attendInfo || "--" }}</div>
				</div>
				<div class="detail-item">
					<label>消课基数</label>
					<div>{{ detailData?.decLessonCount ?? "--" }}</div>
				</div>
				<div class="detail-item">
					<label>是否可预约</label>
					<div>{{ reserveText }}</div>
				</div>
			</div>
		</div>
		<template #footer>
			<el-button @click="dialogVisible = false">关闭</el-button>
			<el-button type="danger" @click="handleDelete">
				<IconifyIconOffline icon="ep/delete" width="16" height="16" style="margin-right: 4px" />
				删除
			</el-button>
		</template>
	</el-dialog>
</template>

<script setup lang="ts">
import { computed, ref } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { IconifyIconOffline } from "@/components/ReIcon";
import { getCourseDetail, deleteCourses } from "@/apis/academic";
import type { CourseDetailVO, CourseListVO } from "@/apis/academic/type";

const dialogVisible = ref(false);
const loading = ref(false);
const detailData = ref<CourseDetailVO>();
const deleteLoading = ref(false);

const emit = defineEmits<{
	deleted: [id: number];
}>();

const dialogTitle = computed(() => detailData.value?.title || "课次详情");

const reserveText = computed(() => {
	const value = String(detailData.value?.canReserve || "").trim();
	if (["1", "true", "是", "开启", "可预约"].includes(value)) return "是";
	if (!value) return "--";
	return "否";
});

function buildFallbackDetail(row: CourseListVO): CourseDetailVO {
	return {
		title: row.courseName || "课次详情",
		courseName: row.courseName,
		courseNo: row.courseId ? String(row.courseId) : undefined,
		className: row.className,
		courseType: row.courseType,
		lessonTimeText: row.lessonTimeText,
		classroomName: row.classroomName,
		classroomNo: row.classroomId ? String(row.classroomId) : undefined,
		teacherName: row.teacherNames,
		teacherNo: row.teacherIds,
		assistantName: row.assistantNames,
		assistantNo: row.assistantIds,
		attendInfo:
			row.studentCount !== undefined && row.checkInCount !== undefined
				? `${row.checkInCount}/${row.studentCount}`
				: undefined,
		decLessonCount: row.decLessonCount,
		canReserve: row.canReserve,
		status: row.lessonStatus2 || row.lessonStatus,
	};
}

async function handleDelete() {
	if (!detailData.value?.id) {
		ElMessage.warning("课程 ID 不存在");
		return;
	}

	try {
		await ElMessageBox.confirm(
			`确认删除课程"${detailData.value.title || detailData.value.courseName}"吗？此操作不可恢复。`,
			"删除确认",
			{
				type: "warning",
				confirmButtonText: "确定",
				cancelButtonText: "取消",
			},
		);

		deleteLoading.value = true;
		const res = await deleteCourses([detailData.value.id]);

		if (res.code !== 0 && res.code !== 10000) {
			ElMessage.error(res.message || "删除失败");
			return;
		}

		ElMessage.success("删除成功");
		emit("deleted", detailData.value.id);
		dialogVisible.value = false;
	} catch (error) {
		if (error === "cancel") {
			return;
		}
		console.error("删除课程失败:", error);
		ElMessage.error("删除失败");
	} finally {
		deleteLoading.value = false;
	}
}

defineExpose({
	async openDialog(row: CourseListVO | CourseDetailVO) {
		dialogVisible.value = true;
		loading.value = true;

		const isCourseDetailVO = (data: any): data is CourseDetailVO => {
			return data && ("date" in data || "startTime" in data || "endTime" in data);
		};

		if (isCourseDetailVO(row)) {
			detailData.value = row;
			loading.value = false;
		} else {
			detailData.value = buildFallbackDetail(row);

			if (!row.id) {
				loading.value = false;
				return;
			}

			try {
				const res = await getCourseDetail(row.id);
				if (res.data) {
					detailData.value = { ...buildFallbackDetail(row), ...res.data };
				}
			} catch (error) {
				console.error("获取课次详情失败:", error);
			} finally {
				loading.value = false;
			}
		}
	},
	closeDialog() {
		dialogVisible.value = false;
	},
});
</script>

<style scoped>
.course-detail-dialog {
	padding: 8px 4px;
}

.detail-loading {
	color: #606266;
	padding: 24px 8px;
}

.detail-grid {
	display: grid;
	grid-template-columns: repeat(2, minmax(0, 1fr));
	gap: 14px 18px;
}

.detail-item {
	padding: 12px 14px;
	background: #f8fafc;
	border-radius: 8px;
}

.detail-item-wide {
	grid-column: span 2;
}

.detail-item label {
	display: block;
	font-size: 12px;
	color: #909399;
	margin-bottom: 8px;
}

.detail-item div {
	font-size: 14px;
	color: #303133;
	word-break: break-all;
}
</style>
