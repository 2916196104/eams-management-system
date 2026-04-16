<template>
	<div class="schedule-container">
		<div class="schedule-content">
			<div class="filter-area">
				<div class="filter-row">
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.cycleLabel }}</label>
						<el-select v-model="filters.cycle" :placeholder="TEXT.selectPlaceholder" clearable class="filter-input">
							<el-option :label="TEXT.thisWeek" :value="1" />
							<el-option :label="TEXT.lastWeek" :value="2" />
							<el-option :label="TEXT.thisWeekAndAfter" :value="3" />
						</el-select>
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.classLabel }}</label>
						<el-input v-model="filters.className" :placeholder="TEXT.classPlaceholder" clearable class="filter-input" />
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.courseLabel }}</label>
						<el-input
							v-model="filters.courseName"
							:placeholder="TEXT.coursePlaceholder"
							clearable
							class="filter-input"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.teacherLabel }}</label>
						<el-input
							v-model="filters.teacherName"
							:placeholder="TEXT.teacherPlaceholder"
							clearable
							class="filter-input"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.studentLabel }}</label>
						<el-input
							v-model="filters.studentName"
							:placeholder="TEXT.studentPlaceholder"
							clearable
							class="filter-input"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.startDateLabel }}</label>
						<el-date-picker
							v-model="filters.startDate"
							type="date"
							:placeholder="TEXT.selectPlaceholder"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-item">
						<label class="filter-label">{{ TEXT.endDateLabel }}</label>
						<el-date-picker
							v-model="filters.endDate"
							type="date"
							:placeholder="TEXT.selectPlaceholder"
							clearable
							class="filter-input"
							format="YYYY-MM-DD"
							value-format="YYYY-MM-DD"
						/>
					</div>
					<div class="filter-buttons">
						<el-button circle @click="handleSearch">
							<IconifyIconOffline icon="ep/search" width="16" height="16" />
						</el-button>
						<el-button circle @click="handleReset">
							<IconifyIconOffline icon="ep/close" width="16" height="16" />
						</el-button>
					</div>
				</div>
				<div class="filter-actions">
					<el-button circle @click="handleRefresh">
						<IconifyIconOffline icon="ep/refresh" width="16" height="16" />
					</el-button>
					<el-button circle @click="handlePrint">
						<IconifyIconOffline icon="ep/printer" width="16" height="16" />
					</el-button>
					<el-button circle @click="handleExport">
						<IconifyIconOffline icon="ep/download" width="16" height="16" />
					</el-button>
					<el-popover v-model:visible="columnPopoverVisible" placement="bottom-end" :width="640">
						<template #reference>
							<span class="column-trigger-wrap">
								<el-button circle @click="openColumnPopover">
									<IconifyIconOffline icon="ep/menu" width="16" height="16" />
								</el-button>
							</span>
						</template>
						<div class="column-popover">
							<div class="column-title">自定义显示列：</div>
							<div class="column-options">
								<el-checkbox v-model="columnDraft.lessonTimeText">上课时间</el-checkbox>
								<el-checkbox v-model="columnDraft.courseName">课程</el-checkbox>
								<el-checkbox v-model="columnDraft.className">班级名称</el-checkbox>
								<el-checkbox v-model="columnDraft.teacherNames">上课老师</el-checkbox>
								<el-checkbox v-model="columnDraft.courseType">类型</el-checkbox>
								<el-checkbox v-model="columnDraft.assistantNames">助教</el-checkbox>
								<el-checkbox v-model="columnDraft.classroomName">教室</el-checkbox>
								<el-checkbox v-model="columnDraft.canReserve">可预约</el-checkbox>
								<el-checkbox v-model="columnDraft.studentCount">学生数</el-checkbox>
								<el-checkbox v-model="columnDraft.checkInCount">签到数</el-checkbox>
								<el-checkbox v-model="columnDraft.attendanceRate">到课率</el-checkbox>
								<el-checkbox v-model="columnDraft.decLessonCount">消课基数</el-checkbox>
								<el-checkbox v-model="columnDraft.consumedCount">已消课数</el-checkbox>
								<el-checkbox v-model="columnDraft.lessonStatus">上课情况</el-checkbox>
								<el-checkbox v-model="columnDraft.lessonStatus2">状态</el-checkbox>
								<el-checkbox v-model="columnDraft.evaluationSummary">点评</el-checkbox>
							</div>
							<div class="column-actions">
								<el-button link @click="restoreColumns">恢复</el-button>
								<el-button link type="primary" @click="confirmColumns">确认</el-button>
							</div>
						</div>
					</el-popover>
				</div>
			</div>

			<div class="batch-actions">
				<el-button type="primary" @click="handleScheduleCalendar">
					<template #icon>
						<IconifyIconOffline icon="ep/calendar" width="14" height="14" />
					</template>
					{{ TEXT.scheduleCalendar }}
				</el-button>
				<el-button @click="handleRepeatSchedule">
					<template #icon>
						<IconifyIconOffline icon="ep/refresh-right" width="14" height="14" />
					</template>
					{{ TEXT.repeatScheduleAction }}
				</el-button>
				<el-button @click="handleFreeSchedule">
					<template #icon>
						<IconifyIconOffline icon="ep/edit" width="14" height="14" />
					</template>
					{{ TEXT.freeScheduleAction }}
				</el-button>
				<el-button @click="handleBatchDelete">
					<template #icon>
						<IconifyIconOffline icon="ep/delete" width="14" height="14" />
					</template>
					{{ TEXT.deleteAction }}
				</el-button>
				<el-button @click="handleBatchModify">
					<template #icon>
						<IconifyIconOffline icon="ep/edit-pen" width="14" height="14" />
					</template>
					{{ TEXT.batchModifyAction }}
				</el-button>
				<el-button @click="handleStop">
					<template #icon>
						<IconifyIconOffline icon="ep/video-pause" width="14" height="14" />
					</template>
					{{ TEXT.stopAction }}
				</el-button>
				<el-button @click="handleResume">
					<template #icon>
						<IconifyIconOffline icon="ep/video-play" width="14" height="14" />
					</template>
					{{ TEXT.resumeAction }}
				</el-button>
				<el-button @click="handleReservationOpen">
					<template #icon>
						<IconifyIconOffline icon="ep/open" width="14" height="14" />
					</template>
					{{ TEXT.reservationOpenAction }}
				</el-button>
				<el-button @click="handleReservationClose">
					<template #icon>
						<IconifyIconOffline icon="ep/close" width="14" height="14" />
					</template>
					{{ TEXT.reservationCloseAction }}
				</el-button>
			</div>

			<my-table
				:istabmultiple="true"
				:tabattr="tableAttr"
				:tabdatacolumns="tableColumns"
				:tabdata="displayPageData"
				@page-change="handlePageChange"
				@selection-change="handleSelectionChange"
			>
				<template #customercell="{ prop, row }">
					<template v-if="prop === 'lessonTimeText'">
						<el-button link type="primary" @click="openCourseDetailDialog(row)">
							{{ row[prop] }}
						</el-button>
					</template>
					<template v-else-if="prop === 'lessonStatus'">
						<span :class="getCellClass(prop)">{{ row[prop] }}</span>
					</template>
					<template v-else-if="prop === 'evaluationSummary'">
						<el-tooltip :content="getEvaluationTooltip(row)" placement="top" :show-after="200">
							<el-button
								link
								type="primary"
								:class="{ 'cell-evaluation-empty': getEvaluationSummary(row) === TEXT.evaluationEmpty }"
								@click="openEvaluationDialog(row)"
							>
								{{ getEvaluationSummary(row) }}
							</el-button>
						</el-tooltip>
					</template>
					<template v-else-if="prop === 'action'">
						<el-button link type="primary" size="small" @click="handleEdit(row)">{{ TEXT.editAction }}</el-button>
					</template>
					<template v-else>
						{{ row[prop] }}
					</template>
				</template>
			</my-table>

			<el-dialog v-model="evaluationDialogVisible" :title="TEXT.evaluationDialogTitle" width="960px">
				<div class="evaluation-dialog">
					<div class="evaluation-tip">{{ TEXT.evaluationDialogTip }}</div>
					<el-table :data="evaluationDialogRows" border>
						<el-table-column type="index" :label="TEXT.evaluationSeqLabel" width="72" align="center" />
						<el-table-column prop="studentDisplayName" :label="TEXT.evaluationStudentLabel" min-width="180" />
						<el-table-column :label="TEXT.evaluationScoreLabel" width="150" align="center">
							<template #default="{ row }">
								<el-rate :model-value="row.overallScore || 0" disabled />
							</template>
						</el-table-column>
						<el-table-column prop="content" :label="TEXT.evaluationContentLabel" min-width="220" show-overflow-tooltip>
							<template #default="{ row }">
								{{ row.content || TEXT.evaluationEmpty }}
							</template>
						</el-table-column>
						<el-table-column prop="teacherName" :label="TEXT.evaluationTeacherLabel" width="120" />
						<el-table-column prop="commentTimeText" :label="TEXT.evaluationTimeLabel" width="150" />
						<el-table-column :label="TEXT.tableAction" width="100" align="center" fixed="right">
							<template #default="{ row }">
								<el-button link type="primary" @click="openEvaluationEditDialog(row)">
									{{ row.id ? TEXT.evaluationEditAction : TEXT.evaluationCreateAction }}
								</el-button>
							</template>
						</el-table-column>
					</el-table>
				</div>
				<template #footer>
					<el-button @click="evaluationDialogVisible = false">{{ TEXT.closeAction }}</el-button>
				</template>
			</el-dialog>

			<el-dialog v-model="evaluationEditDialogVisible" :title="TEXT.evaluationEditDialogTitle" width="560px">
				<el-form label-width="92px">
					<el-form-item :label="TEXT.evaluationStudentLabel">
						<span>{{ editingEvaluation.studentDisplayName || "--" }}</span>
					</el-form-item>
					<el-form-item :label="TEXT.evaluationOverallLabel">
						<el-rate v-model="editingEvaluation.overallScore" />
					</el-form-item>
					<el-form-item :label="TEXT.evaluationAtmosphereLabel">
						<el-rate v-model="editingEvaluation.atmosphereScore" />
					</el-form-item>
					<el-form-item :label="TEXT.evaluationAttitudeLabel">
						<el-rate v-model="editingEvaluation.attitudeScore" />
					</el-form-item>
					<el-form-item :label="TEXT.evaluationEffectLabel">
						<el-rate v-model="editingEvaluation.effectScore" />
					</el-form-item>
					<el-form-item :label="TEXT.evaluationContentLabel">
						<el-input
							v-model="editingEvaluation.content"
							type="textarea"
							:rows="4"
							:placeholder="TEXT.evaluationContentPlaceholder"
						/>
					</el-form-item>
				</el-form>
				<template #footer>
					<el-button @click="evaluationEditDialogVisible = false">{{ TEXT.cancelAction }}</el-button>
					<el-button type="primary" :loading="evaluationSubmitting" @click="handleSaveEvaluation">
						{{ TEXT.submitAction }}
					</el-button>
				</template>
			</el-dialog>

			<el-dialog v-model="batchModifyDialogVisible" :title="TEXT.batchModifyDialogTitle" width="880px">
				<div class="batch-modify-dialog">
					<div class="batch-modify-tip">{{ TEXT.batchModifyTip }}</div>
					<el-form label-width="92px">
						<el-form-item :label="TEXT.batchModifyDayOffsetLabel">
							<el-input-number v-model="batchModifyForm.dayOffset" :min="-7" :max="7" class="w-100" />
							<div class="field-tip">{{ TEXT.batchModifyDayOffsetTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.batchModifyStartTimeLabel">
							<el-time-picker
								v-model="batchModifyForm.startTime"
								placeholder="请选择"
								clearable
								class="w-100"
								format="HH:mm:ss"
								value-format="HH:mm:ss"
							/>
							<div class="field-tip">{{ TEXT.batchModifyStartTimeTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.batchModifyEndTimeLabel">
							<el-time-picker
								v-model="batchModifyForm.endTime"
								placeholder="请选择"
								clearable
								class="w-100"
								format="HH:mm:ss"
								value-format="HH:mm:ss"
							/>
							<div class="field-tip">{{ TEXT.batchModifyEndTimeTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.batchModifyTeacherLabel">
							<el-select v-model="batchModifyForm.teacherId" placeholder="请选择" clearable filterable class="w-100">
								<el-option
									v-for="option in batchTeacherOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
							<div class="field-tip">{{ TEXT.batchModifyTeacherTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.batchModifyAssistantLabel">
							<el-select v-model="batchModifyForm.assistantId" placeholder="请选择" clearable filterable class="w-100">
								<el-option
									v-for="option in batchAssistantOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
							<div class="field-tip">{{ TEXT.batchModifyAssistantTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.batchModifyClassroomLabel">
							<el-select v-model="batchModifyForm.classroomId" placeholder="请选择" clearable filterable class="w-100">
								<el-option
									v-for="option in batchRoomOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
							<div class="field-tip">{{ TEXT.batchModifyClassroomTip }}</div>
						</el-form-item>
					</el-form>
				</div>
				<template #footer>
					<el-button @click="batchModifyDialogVisible = false">{{ TEXT.cancelAction }}</el-button>
					<el-button type="primary" :loading="batchModifySubmitting" @click="handleBatchModifySubmit">
						{{ TEXT.submitAction }}
					</el-button>
				</template>
			</el-dialog>

			<el-dialog v-model="editCourseDialogVisible" :title="TEXT.editCourseDialogTitle" width="880px">
				<div class="batch-modify-dialog">
					<el-form label-width="92px">
						<el-form-item :label="TEXT.editCourseTeacherLabel" required>
							<el-select v-model="editCourseForm.teacherId" placeholder="请选择" filterable class="w-100">
								<el-option
									v-for="option in batchTeacherOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseAssistantLabel">
							<el-select v-model="editCourseForm.assistantId" placeholder="请选择" clearable filterable class="w-100">
								<el-option
									v-for="option in batchAssistantOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseDateLabel" required>
							<el-date-picker
								v-model="editCourseForm.courseDate"
								type="date"
								class="w-100"
								format="YYYY-MM-DD"
								value-format="YYYY-MM-DD"
							/>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseStartLabel" required>
							<el-time-picker
								v-model="editCourseForm.startTime"
								class="w-100"
								format="HH:mm:ss"
								value-format="HH:mm:ss"
							/>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseEndLabel" required>
							<el-time-picker
								v-model="editCourseForm.endTime"
								class="w-100"
								format="HH:mm:ss"
								value-format="HH:mm:ss"
							/>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseRoomLabel">
							<el-select v-model="editCourseForm.roomId" placeholder="请选择" clearable filterable class="w-100">
								<el-option
									v-for="option in batchRoomOptions"
									:key="option.value"
									:label="option.label"
									:value="option.value"
								/>
							</el-select>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseDecCountLabel">
							<el-input-number v-model="editCourseForm.decCount" :min="0" class="w-100" />
							<div class="field-tip">{{ TEXT.editCourseDecCountTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseReserveLabel">
							<el-switch v-model="editCourseForm.enableReserve" />
						</el-form-item>
						<el-form-item :label="TEXT.editCourseBatchSyncLabel">
							<el-switch v-model="editCourseForm.batchSyncTime" />
							<div class="field-tip">{{ TEXT.editCourseBatchSyncTip }}</div>
						</el-form-item>
						<el-form-item :label="TEXT.editCourseConflictLabel">
							<el-switch v-model="editCourseForm.checkConflict" />
						</el-form-item>
					</el-form>
				</div>
				<template #footer>
					<el-button @click="editCourseDialogVisible = false">{{ TEXT.cancelAction }}</el-button>
					<el-button type="primary" :loading="editCourseSubmitting" @click="handleEditCourseSubmit">
						{{ TEXT.submitAction }}
					</el-button>
				</template>
			</el-dialog>

			<CourseDetailDialog ref="courseDetailDialogRef" />
			<RepeatScheduleDialog ref="repeatScheduleDialogRef" @success="loadData" />
			<FreeScheduleDialog ref="freeScheduleDialogRef" @success="loadData" />
		</div>
	</div>
</template>

<script setup lang="ts">
import { computed, onMounted, reactive, ref } from "vue";
import { useRouter } from "vue-router";
import { ElMessage, ElMessageBox } from "element-plus";
import * as XLSX from "xlsx";
import { IconifyIconOffline } from "@/components/ReIcon";
import MyTable from "@/components/mytable/MyTable.vue";
import CourseDetailDialog from "@/components/coursedetail/CourseDetailDialog.vue";
import RepeatScheduleDialog from "@/components/repeatschedule/RepeatScheduleDialog.vue";
import FreeScheduleDialog from "@/components/freeschedule/FreeScheduleDialog.vue";
import { createPageDTO, type MyTableAttr, type MyTableColumn, type PageDTO } from "@/components/mytable/type";
import {
	batchUpdateCourses,
	deleteCourses,
	getCourseListPage,
	getEvaluationList,
	resumeCourses,
	saveEvaluation,
	switchSchedule,
	updateCourse,
} from "@/apis/academic";
import type {
	BatchUpdateCoursesDTO,
	CourseListVO,
	EvaluationSaveDTO,
	EvaluationVO,
	UpdateCourseDTO,
} from "@/apis/academic/type";
import { buildScheduleExportFilename, buildScheduleExportRows, getScheduleExportColumns } from "./schedule-export";

type RepeatScheduleDialogInstance = {
	openDialog: (payload?: { selectedRow?: CourseListVO; candidateRows?: CourseListVO[] }) => void;
	closeDialog: () => void;
};

type FreeScheduleDialogInstance = {
	openDialog: (payload?: { selectedRow?: CourseListVO; candidateRows?: CourseListVO[] }) => void;
	closeDialog: () => void;
};

type CourseDetailDialogInstance = {
	openDialog: (row: CourseListVO) => void;
	closeDialog: () => void;
};

type LessonEvaluationRow = EvaluationVO & {
	studentDisplayName: string;
	commentTimeText: string;
};

type SelectOption = {
	value: number;
	label: string;
};

const TEXT = {
	cycleLabel: "\u5468\u671F:",
	selectPlaceholder: "\u8BF7\u9009\u62E9",
	thisWeek: "\u672C\u5468",
	lastWeek: "\u4E0A\u5468",
	thisWeekAndAfter: "\u672C\u5468\u53CA\u4EE5\u540E",
	classLabel: "\u73ED\u7EA7:",
	classPlaceholder: "\u8BF7\u8F93\u5165\u73ED\u7EA7\u540D",
	courseLabel: "\u8BFE\u7A0B:",
	coursePlaceholder: "\u8BF7\u8F93\u5165\u8BFE\u7A0B\u540D",
	teacherLabel: "\u8001\u5E08:",
	teacherPlaceholder: "\u8BF7\u8F93\u5165\u8001\u5E08\u59D3\u540D",
	studentLabel: "\u5B66\u751F:",
	studentPlaceholder: "\u8BF7\u8F93\u5165\u5B66\u751F\u59D3\u540D",
	startDateLabel: "\u5F00\u59CB\u65E5\u671F:",
	endDateLabel: "\u7ED3\u675F\u65E5\u671F:",
	scheduleCalendar: "\u8BFE\u8868\u65E5\u5386",
	repeatScheduleAction: "+ \u91CD\u590D\u6392\u8BFE",
	freeScheduleAction: "+ \u81EA\u7531\u6392\u8BFE",
	deleteAction: "\u5220\u9664",
	batchModifyAction: "\u6279\u91CF\u4FEE\u6539",
	stopAction: "\u505C\u8BFE",
	resumeAction: "\u6062\u590D",
	reservationOpenAction: "\u9884\u7EA6\u5F00",
	reservationCloseAction: "\u9884\u7EA6\u5173",
	editAction: "\u7F16\u8F91",
	pendingRefresh: "\u5237\u65B0\u529F\u80FD\u5F85\u63A5\u5165",
	pendingPrint: "\u6253\u5370\u529F\u80FD\u5F85\u63A5\u5165",
	pendingExport: "\u5BFC\u51FA\u529F\u80FD\u5F85\u63A5\u5165",
	exportNoColumns: "\u5F53\u524D\u6CA1\u6709\u53EF\u5BFC\u51FA\u7684\u5217",
	exportNoData: "\u5F53\u524D\u6CA1\u6709\u53EF\u5BFC\u51FA\u7684\u6570\u636E",
	exportSuccess: "\u5BFC\u51FA\u6210\u529F",
	exportFailed: "\u5BFC\u51FA\u5931\u8D25",
	pendingCustomColumn: "\u81EA\u5B9A\u4E49\u5217\u529F\u80FD\u5F85\u63A5\u5165",
	pendingFreeSchedule: "\u81EA\u7531\u6392\u8BFE\u529F\u80FD\u5F85\u63A5\u5165",
	pendingBatchModify: "\u6279\u91CF\u4FEE\u6539\u529F\u80FD\u5F85\u63A5\u5165",
	pendingStop: "\u505C\u8BFE\u529F\u80FD\u5F85\u63A5\u5165",
	pendingResume: "\u6062\u590D\u529F\u80FD\u5F85\u63A5\u5165",
	pendingReservationOpen: "\u9884\u7EA6\u5F00\u529F\u80FD\u5F85\u63A5\u5165",
	pendingReservationClose: "\u9884\u7EA6\u5173\u529F\u80FD\u5F85\u63A5\u5165",
	pendingEdit: "\u7F16\u8F91\u529F\u80FD\u5F85\u63A5\u5165",
	repeatScheduleEmpty:
		"\u5F53\u524D\u6CA1\u6709\u53EF\u7528\u7684\u8BFE\u6B21\u6570\u636E\uff0c\u8BF7\u5148\u67E5\u8BE2\u6216\u4F7F\u7528 mock \u6570\u636E",
	freeScheduleEmpty:
		"\u5F53\u524D\u6CA1\u6709\u53EF\u7528\u7684\u8BFE\u6B21\u6570\u636E\uff0c\u8BF7\u5148\u67E5\u8BE2\u518D\u8FDB\u884C\u81EA\u7531\u6392\u8BFE",
	loadFailed: "\u52A0\u8F7D\u6570\u636E\u5931\u8D25",
	evaluationLoadFailed: "\u52A0\u8F7D\u70B9\u8BC4\u6570\u636E\u5931\u8D25",
	tableLessonTime: "\u4E0A\u8BFE\u65F6\u95F4",
	tableCourse: "\u8BFE\u7A0B",
	tableClassName: "\u73ED\u7EA7\u540D\u79F0",
	tableTeacher: "\u4E0A\u8BFE\u8001\u5E08",
	tableCourseType: "\u7C7B\u578B",
	tableAssistant: "\u52A9\u6559",
	tableClassroom: "\u6559\u5BA4",
	tableCanReserve: "\u53EF\u9884\u7EA6",
	tableStudentCount: "\u5B66\u751F\u6570",
	tableCheckInCount: "\u7B7E\u5230\u6570",
	tableAttendanceRate: "\u5230\u8BFE\u7387",
	tableDescLessonCount: "\u6D88\u8BFE\u57FA\u6570",
	tableConsumedCount: "\u5DF2\u6D88\u8BFE\u6570",
	tableLessonStatus: "\u4E0A\u8BFE\u60C5\u51B5",
	tableStatus: "\u72B6\u6001",
	tableEvaluation: "\u70B9\u8BC4",
	tableAction: "\u64CD\u4F5C",
	evaluationEmpty: "\u6682\u65E0\u70B9\u8BC4",
	evaluationCountUnit: "\u6761",
	evaluationAvgPrefix: "\u5747\u5206",
	evaluationDialogTitle: "\u8BFE\u540E\u70B9\u8BC4",
	evaluationDialogTip:
		"\u8BFE\u540E\u70B9\u8BC4\u53EF\u4EE5\u6839\u636E\u6253\u5206\u7ED9\u4E88\u5B66\u751F\u79EF\u5206\u5956\u52B1\u3002",
	evaluationEditDialogTitle: "\u7F16\u8F91\u70B9\u8BC4",
	evaluationSeqLabel: "\u5E8F\u53F7",
	evaluationStudentLabel: "\u5B66\u5458",
	evaluationScoreLabel: "\u70B9\u8BC4\u5F97\u5206",
	evaluationContentLabel: "\u70B9\u8BC4\u5185\u5BB9",
	evaluationTeacherLabel: "\u70B9\u8BC4\u8001\u5E08",
	evaluationTimeLabel: "\u70B9\u8BC4\u65F6\u95F4",
	evaluationCreateAction: "\u70B9\u8BC4",
	evaluationEditAction: "\u4FEE\u6539",
	evaluationOverallLabel: "\u7EFC\u5408\u8BC4\u5206",
	evaluationAtmosphereLabel: "\u8BFE\u5802\u6C14\u6C1B",
	evaluationAttitudeLabel: "\u6388\u8BFE\u6001\u5EA6",
	evaluationEffectLabel: "\u6559\u5B66\u6548\u679C",
	evaluationContentPlaceholder: "\u8BF7\u8F93\u5165\u8BFE\u540E\u70B9\u8BC4",
	evaluationSaveFailed: "\u4FDD\u5B58\u70B9\u8BC4\u5931\u8D25",
	evaluationSaveSuccess: "\u4FDD\u5B58\u70B9\u8BC4\u6210\u529F",
	evaluationStudentMissing: "\u5F53\u524D\u7F3A\u5C11\u5B66\u751FID\uff0C\u65E0\u6CD5\u4FDD\u5B58\u70B9\u8BC4",
	evaluationScoreRequired: "\u8BF7\u5148\u8BBE\u7F6E\u7EFC\u5408\u8BC4\u5206",
	closeAction: "\u5173\u95ED",
	cancelAction: "\u53D6\u6D88",
	submitAction: "\u63D0\u4EA4",
	deleteSelectWarning: "\u8BF7\u5148\u52FE\u9009\u8981\u5220\u9664\u7684\u8BFE\u6B21",
	deleteConfirmTitle: "\u5220\u9664\u8BFE\u6B21",
	deleteConfirmMessage:
		"\u786E\u8BA4\u5220\u9664\u5DF2\u9009\u4E2D\u7684 {count} \u6761\u8BFE\u6B21\u5417\uff1F\u6B64\u64CD\u4F5C\u4E0D\u53EF\u6062\u590D\u3002",
	deleteSuccess: "\u5220\u9664\u6210\u529F",
	deleteFailed: "\u5220\u9664\u5931\u8D25",
	batchSelectWarning: "\u8BF7\u5148\u52FE\u9009\u8981\u64CD\u4F5C\u7684\u8BFE\u6B21",
	stopConfirmTitle: "\u505C\u8BFE",
	stopConfirmMessage: "\u786E\u8BA4\u505C\u6389\u5DF2\u9009\u4E2D\u7684 {count} \u6761\u8BFE\u6B21\u5417\uff1F",
	stopSuccess: "\u505C\u8BFE\u6210\u529F",
	stopFailed: "\u505C\u8BFE\u5931\u8D25",
	resumeConfirmTitle: "\u590D\u8BFE",
	resumeConfirmMessage: "\u786E\u8BA4\u6062\u590D\u5DF2\u9009\u4E2D\u7684 {count} \u6761\u8BFE\u6B21\u5417\uff1F",
	resumeSuccess: "\u590D\u8BFE\u6210\u529F",
	resumeFailed: "\u590D\u8BFE\u5931\u8D25",
	reservationOpenConfirmTitle: "\u9884\u7EA6\u5F00",
	reservationOpenConfirmMessage:
		"\u786E\u8BA4\u6253\u5F00\u5DF2\u9009\u4E2D\u7684 {count} \u6761\u8BFE\u6B21\u9884\u7EA6\u5417\uff1F",
	reservationOpenSuccess: "\u9884\u7EA6\u5F00\u542F\u6210\u529F",
	reservationOpenFailed: "\u9884\u7EA6\u5F00\u542F\u5931\u8D25",
	reservationCloseConfirmTitle: "\u9884\u7EA6\u5173",
	reservationCloseConfirmMessage:
		"\u786E\u8BA4\u5173\u95ED\u5DF2\u9009\u4E2D\u7684 {count} \u6761\u8BFE\u6B21\u9884\u7EA6\u5417\uff1F",
	reservationCloseSuccess: "\u9884\u7EA6\u5173\u95ED\u6210\u529F",
	reservationCloseFailed: "\u9884\u7EA6\u5173\u95ED\u5931\u8D25",
	batchModifyDialogTitle: "\u6279\u91CF\u4FEE\u6539\u8BFE\u6B21",
	batchModifyTip:
		"\u6279\u91CF\u4FEE\u6539\u53EF\u4EE5\u65B9\u4FBF\u6279\u91CF\u4FEE\u6539\u8BFE\u6B21\u4FE1\u606F\uff0c\u8C03\u6574\u524D\u8BF7\u6CE8\u610F\u5907\u6CE8\u63CF\u8FF0\uff1A",
	batchModifyDayOffsetLabel: "\u589E\u51CF\u5929\u6570",
	batchModifyDayOffsetTip:
		"\u7528\u6CD5\uff1A\u5982\u628A\u5468\u4E8C\u6539\u6210\u5468\u56DB\uff0c\u586B\u51992\uff1B\u628A\u5468\u65E5\u6539\u6210\u5468\u516D\u586B\u5199-1\uff1B\u6700\u5927\u8C03\u6574\u5929\u6570\u662F7\u5929\u3002",
	batchModifyStartTimeLabel: "\u5F00\u59CB\u65F6\u95F4",
	batchModifyStartTimeTip: "\u7559\u7A7A\u8868\u793A\u539F\u8BFE\u7A0B\u7684\u65F6\u95F4\u4E0D\u53D8",
	batchModifyEndTimeLabel: "\u7ED3\u675F\u65F6\u95F4",
	batchModifyEndTimeTip: "\u7559\u7A7A\u8868\u793A\u539F\u8BFE\u7A0B\u7684\u65F6\u95F4\u4E0D\u53D8",
	batchModifyTeacherLabel: "\u4E0A\u8BFE\u8001\u5E08",
	batchModifyTeacherTip: "\u7559\u7A7A\u8868\u793A\u8001\u5E08\u4E0D\u53D8",
	batchModifyAssistantLabel: "\u52A9\u6559\u8001\u5E08",
	batchModifyAssistantTip: "\u7559\u7A7A\u8868\u793A\u52A9\u6559\u4E0D\u53D8",
	batchModifyClassroomLabel: "\u9009\u62E9\u6559\u5BA4",
	batchModifyClassroomTip: "\u7559\u7A7A\u8868\u793A\u6559\u5BA4\u4E0D\u53D8",
	batchModifySelectWarning: "\u8BF7\u5148\u52FE\u9009\u8981\u6279\u91CF\u4FEE\u6539\u7684\u8BFE\u6B21",
	batchModifyNoChangeWarning: "\u8BF7\u81F3\u5C11\u8BBE\u7F6E\u4E00\u9879\u4FEE\u6539\u5185\u5BB9",
	batchModifyInvalidTime: "\u7ED3\u675F\u65F6\u95F4\u5FC5\u987B\u665A\u4E8E\u5F00\u59CB\u65F6\u95F4",
	batchModifySuccess: "\u6279\u91CF\u4FEE\u6539\u6210\u529F",
	batchModifyFailed: "\u6279\u91CF\u4FEE\u6539\u5931\u8D25",
	editCourseDialogTitle: "\u4FEE\u6539\u8BFE\u6B21",
	editCourseTeacherLabel: "\u4E0A\u8BFE\u8001\u5E08",
	editCourseAssistantLabel: "\u52A9\u6559\u8001\u5E08",
	editCourseDateLabel: "\u4E0A\u8BFE\u65E5\u671F",
	editCourseStartLabel: "\u5F00\u59CB\u65F6\u95F4",
	editCourseEndLabel: "\u7ED3\u675F\u65F6\u95F4",
	editCourseRoomLabel: "\u9009\u62E9\u6559\u5BA4",
	editCourseDecCountLabel: "\u6D88\u8BFE\u57FA\u6570",
	editCourseDecCountTip: "\u8868\u793A\u5355\u4EBA\u5355\u6B21\u7B7E\u5230\u6D88\u8BFE\u91CF",
	editCourseReserveLabel: "\u5F00\u542F\u9884\u7EA6",
	editCourseBatchSyncLabel: "\u6279\u91CF\u540C\u6B65\u65F6\u95F4",
	editCourseBatchSyncTip:
		"\u5F00\u542F\u540E\uff0c\u672C\u73ED\u7EA7\u540E\u7EED\u76F8\u540C\u65F6\u95F4\u7684\u8BFE\u7A0B\uff0c\u5C06\u4F1A\u540C\u6B65\u8C03\u6574\uff1B\u53EA\u4FEE\u6539\u4E0A\u8BFE\u65F6\u95F4\u548C\u8001\u5E08",
	editCourseConflictLabel: "\u662F\u5426\u68C0\u67E5\u51B2\u7A81",
	editCourseRequiredTeacher: "\u8BF7\u9009\u62E9\u4E0A\u8BFE\u8001\u5E08",
	editCourseRequiredDate: "\u8BF7\u9009\u62E9\u4E0A\u8BFE\u65E5\u671F",
	editCourseRequiredTime: "\u8BF7\u5B8C\u6574\u8BBE\u7F6E\u5F00\u59CB\u548C\u7ED3\u675F\u65F6\u95F4",
	editCourseInvalidTime: "\u7ED3\u675F\u65F6\u95F4\u5FC5\u987B\u665A\u4E8E\u5F00\u59CB\u65F6\u95F4",
	editCourseSuccess: "\u4FEE\u6539\u8BFE\u6B21\u6210\u529F",
	editCourseFailed: "\u4FEE\u6539\u8BFE\u6B21\u5931\u8D25",
} as const;

const router = useRouter();
const isDev = import.meta.env.DEV;

const filters = reactive({
	pageIndex: 1,
	pageSize: 30,
	classId: undefined as number | undefined,
	courseId: undefined as number | undefined,
	startDate: "",
	endDate: "",
	teacherId: undefined as number | undefined,
	roomId: undefined as number | undefined,
	state: undefined as number | undefined,
	onTrial: undefined as number | undefined,
	// 兼容旧字段
	cycle: undefined as number | undefined,
	className: "",
	courseName: "",
	teacherName: "",
	studentName: "",
});

const DEV_MOCK_SCHEDULE_ROWS: CourseListVO[] = [
	{
		id: 9001,
		scheduleId: 9001,
		courseId: 3001,
		lessonTimeText: "2026-03-30 09:00:00 - 10:30:00",
		courseName: "中学数学提升",
		classId: 2001,
		className: "初二春季培优班",
		teacherIds: "101",
		teacherNames: "张老师",
		courseType: "正式课",
		assistantIds: "201",
		assistantNames: "李助教",
		classroomId: 501,
		classroomName: "A101",
		canReserve: "1",
		studentCount: 18,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "王小明,李小雨",
	},
	{
		id: 9002,
		scheduleId: 9002,
		courseId: 3002,
		lessonTimeText: "2026-03-31 14:00:00 - 15:30:00",
		courseName: "英语口语训练",
		classId: 2002,
		className: "初一英语冲刺班",
		teacherIds: "102",
		teacherNames: "陈老师",
		courseType: "正式课",
		assistantIds: "202",
		assistantNames: "周助教",
		classroomId: 502,
		classroomName: "B202",
		canReserve: "0",
		studentCount: 12,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "赵晨,孙悦",
	},
	{
		id: 9003,
		scheduleId: 9003,
		courseId: 3003,
		lessonTimeText: "2026-04-02 19:00:00 - 20:30:00",
		courseName: "物理实验拓展",
		classId: 2003,
		className: "高一物理实验班",
		teacherIds: "103,104",
		teacherNames: "刘老师,何老师",
		courseType: "公开课",
		assistantIds: "",
		assistantNames: "",
		classroomId: 503,
		classroomName: "实验室301",
		canReserve: "1",
		studentCount: 20,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 2,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "林浩,许诺",
	},
	{
		id: 9004,
		scheduleId: 9004,
		courseId: 3004,
		lessonTimeText: "2026-04-03 10:00:00 - 11:30:00",
		courseName: "语文阅读表达",
		classId: 2004,
		className: "初三语文冲刺班",
		teacherIds: "105",
		teacherNames: "周老师",
		courseType: "正式课",
		assistantIds: "203",
		assistantNames: "韩助教",
		classroomId: 504,
		classroomName: "C103",
		canReserve: "1",
		studentCount: 16,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "陆然,程雪",
	},
	{
		id: 9005,
		scheduleId: 9005,
		courseId: 3005,
		lessonTimeText: "2026-04-04 13:30:00 - 15:00:00",
		courseName: "化学实验基础",
		classId: 2005,
		className: "高一化学实验班",
		teacherIds: "106",
		teacherNames: "孙老师",
		courseType: "实验课",
		assistantIds: "204",
		assistantNames: "何助教",
		classroomId: 505,
		classroomName: "实验室105",
		canReserve: "0",
		studentCount: 14,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 2,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "停课",
		studentNames: "蒋一,宋柠",
	},
	{
		id: 9006,
		scheduleId: 9006,
		courseId: 3006,
		lessonTimeText: "2026-04-05 18:30:00 - 20:00:00",
		courseName: "英语写作专项",
		classId: 2006,
		className: "高二英语提升班",
		teacherIds: "102",
		teacherNames: "陈老师",
		courseType: "正式课",
		assistantIds: "",
		assistantNames: "",
		classroomId: 506,
		classroomName: "D201",
		canReserve: "1",
		studentCount: 22,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "顾宁,高辰",
	},
	{
		id: 9007,
		scheduleId: 9007,
		courseId: 3007,
		lessonTimeText: "2026-04-06 08:30:00 - 10:00:00",
		courseName: "历史专题突破",
		classId: 2007,
		className: "高三历史冲刺班",
		teacherIds: "107",
		teacherNames: "吴老师",
		courseType: "正式课",
		assistantIds: "205",
		assistantNames: "郑助教",
		classroomId: 507,
		classroomName: "B105",
		canReserve: "0",
		studentCount: 11,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "罗一诺,沈嘉",
	},
	{
		id: 9008,
		scheduleId: 9008,
		courseId: 3008,
		lessonTimeText: "2026-04-07 15:30:00 - 17:00:00",
		courseName: "地理图表训练",
		classId: 2008,
		className: "高二地理班",
		teacherIds: "108",
		teacherNames: "杨老师",
		courseType: "正式课",
		assistantIds: "",
		assistantNames: "",
		classroomId: 508,
		classroomName: "C206",
		canReserve: "1",
		studentCount: 10,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "邵可,简言",
	},
	{
		id: 9009,
		scheduleId: 9009,
		courseId: 3009,
		lessonTimeText: "2026-04-08 19:30:00 - 21:00:00",
		courseName: "政治主观题训练",
		classId: 2009,
		className: "高三政治精品班",
		teacherIds: "109",
		teacherNames: "许老师",
		courseType: "正式课",
		assistantIds: "206",
		assistantNames: "邓助教",
		classroomId: 509,
		classroomName: "A205",
		canReserve: "1",
		studentCount: 19,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "白露,贺川",
	},
	{
		id: 9010,
		scheduleId: 9010,
		courseId: 3010,
		lessonTimeText: "2026-04-09 09:30:00 - 11:00:00",
		courseName: "生物实验探究",
		classId: 2010,
		className: "高一生物实验班",
		teacherIds: "110",
		teacherNames: "唐老师",
		courseType: "实验课",
		assistantIds: "207",
		assistantNames: "方助教",
		classroomId: 510,
		classroomName: "实验室203",
		canReserve: "0",
		studentCount: 13,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 2,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "停课",
		studentNames: "苏年,杜衡",
	},
	{
		id: 9011,
		scheduleId: 9011,
		courseId: 3011,
		lessonTimeText: "2026-04-10 14:30:00 - 16:00:00",
		courseName: "数学压轴题突破",
		classId: 2011,
		className: "高三数学尖子班",
		teacherIds: "101",
		teacherNames: "张老师",
		courseType: "正式课",
		assistantIds: "201",
		assistantNames: "李助教",
		classroomId: 511,
		classroomName: "A301",
		canReserve: "1",
		studentCount: 25,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 1,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "沈逸,周禾",
	},
	{
		id: 9012,
		scheduleId: 9012,
		courseId: 3012,
		lessonTimeText: "2026-04-11 16:30:00 - 18:00:00",
		courseName: "物理竞赛拓展",
		classId: 2012,
		className: "物理竞赛预备班",
		teacherIds: "103",
		teacherNames: "刘老师",
		courseType: "公开课",
		assistantIds: "208",
		assistantNames: "孟助教",
		classroomId: 512,
		classroomName: "科技楼101",
		canReserve: "1",
		studentCount: 9,
		checkInCount: 0,
		attendanceRate: "0%",
		decLessonCount: 2,
		consumedCount: 0,
		lessonStatus: "未上课",
		lessonStatus2: "正常",
		studentNames: "何沐,梁星",
	},
];

const DEV_MOCK_EVALUATIONS: EvaluationVO[] = [
	{
		id: 1,
		teacherId: 101,
		teacherName: "张老师",
		studentId: 10001,
		studentName: "王小明",
		lessonId: 9001,
		courseTitle: "中学数学提升",
		overallScore: 5,
		atmosphereScore: 5,
		attitudeScore: 5,
		effectScore: 4,
		content: "老师讲解清晰，课堂节奏很好，孩子听得很投入。",
	},
	{
		id: 2,
		teacherId: 101,
		teacherName: "张老师",
		studentId: 10002,
		studentName: "李小雨",
		lessonId: 9001,
		courseTitle: "中学数学提升",
		overallScore: 4,
		atmosphereScore: 4,
		attitudeScore: 5,
		effectScore: 4,
		content: "互动比较充分，课后练习也有针对性。",
	},
	{
		id: 3,
		teacherId: 102,
		teacherName: "陈老师",
		studentId: 10003,
		studentName: "赵晨",
		lessonId: 9002,
		courseTitle: "英语口语训练",
		overallScore: 5,
		atmosphereScore: 5,
		attitudeScore: 5,
		effectScore: 5,
		content: "老师鼓励表达，孩子参与度很高，开口明显更主动了。",
	},
	{
		id: 4,
		teacherId: 105,
		teacherName: "周老师",
		studentId: 10007,
		studentName: "陆然",
		lessonId: 9004,
		courseTitle: "语文阅读表达",
		overallScore: 4,
		atmosphereScore: 4,
		attitudeScore: 4,
		effectScore: 4,
		content: "课堂引导细致，阅读思路梳理得很清楚。",
	},
	{
		id: 5,
		teacherId: 107,
		teacherName: "吴老师",
		studentId: 10013,
		studentName: "罗一诺",
		lessonId: 9007,
		courseTitle: "历史专题突破",
		overallScore: 5,
		atmosphereScore: 4,
		attitudeScore: 5,
		effectScore: 5,
		content: "专题总结很到位，知识框架更清晰了。",
	},
	{
		id: 6,
		teacherId: 101,
		teacherName: "张老师",
		studentId: 10019,
		studentName: "沈逸",
		lessonId: 9011,
		courseTitle: "数学压轴题突破",
		overallScore: 5,
		atmosphereScore: 5,
		attitudeScore: 5,
		effectScore: 5,
		content: "压轴题拆解很有帮助，解题步骤更稳了。",
	},
];

const DEV_MOCK_LESSON_STUDENTS: Record<number, Array<{ studentId: number; studentName: string; mobile?: string }>> = {
	9001: [
		{ studentId: 10001, studentName: "王小明", mobile: "199****6233" },
		{ studentId: 10002, studentName: "李小雨", mobile: "176****3453" },
	],
	9002: [
		{ studentId: 10003, studentName: "赵晨", mobile: "159****6936" },
		{ studentId: 10004, studentName: "孙悦", mobile: "136****4321" },
	],
	9003: [
		{ studentId: 10005, studentName: "林浩", mobile: "199****8675" },
		{ studentId: 10006, studentName: "许诺", mobile: "158****2139" },
	],
	9004: [
		{ studentId: 10007, studentName: "陆然", mobile: "188****3201" },
		{ studentId: 10008, studentName: "程雪", mobile: "177****4520" },
	],
	9005: [
		{ studentId: 10009, studentName: "蒋一", mobile: "166****6108" },
		{ studentId: 10010, studentName: "宋柠", mobile: "155****8842" },
	],
	9006: [
		{ studentId: 10011, studentName: "顾宁", mobile: "133****1092" },
		{ studentId: 10012, studentName: "高辰", mobile: "137****4530" },
	],
	9007: [
		{ studentId: 10013, studentName: "罗一诺", mobile: "189****2671" },
		{ studentId: 10014, studentName: "沈嘉", mobile: "156****9823" },
	],
	9008: [
		{ studentId: 10015, studentName: "邵可", mobile: "132****7780" },
		{ studentId: 10016, studentName: "简言", mobile: "135****4209" },
	],
	9009: [
		{ studentId: 10017, studentName: "白露", mobile: "181****6612" },
		{ studentId: 10018, studentName: "贺川", mobile: "138****7710" },
	],
	9010: [
		{ studentId: 10021, studentName: "苏年", mobile: "199****4421" },
		{ studentId: 10022, studentName: "杜衡", mobile: "150****9234" },
	],
	9011: [
		{ studentId: 10019, studentName: "沈逸", mobile: "186****1032" },
		{ studentId: 10020, studentName: "周禾", mobile: "173****5601" },
	],
	9012: [
		{ studentId: 10023, studentName: "何沐", mobile: "139****3510" },
		{ studentId: 10024, studentName: "梁星", mobile: "157****6724" },
	],
};

const tableAttr: MyTableAttr = {
	"row-key": "id",
	border: true,
	stripe: true,
	"highlight-current-row": true,
};

const baseTableColumns: MyTableColumn[] = [
	{ prop: "lessonTimeText", label: TEXT.tableLessonTime, "min-width": 160, "show-overflow-tooltip": true },
	{ prop: "courseName", label: TEXT.tableCourse, "min-width": 120, "show-overflow-tooltip": true },
	{ prop: "className", label: TEXT.tableClassName, "min-width": 120, "show-overflow-tooltip": true },
	{ prop: "teacherNames", label: TEXT.tableTeacher, "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "courseType", label: TEXT.tableCourseType, width: "80px", align: "center" },
	{ prop: "assistantNames", label: TEXT.tableAssistant, "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "classroomName", label: TEXT.tableClassroom, "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "canReserve", label: TEXT.tableCanReserve, width: "80px", align: "center" },
	{ prop: "studentCount", label: TEXT.tableStudentCount, width: "80px", align: "center" },
	{ prop: "checkInCount", label: TEXT.tableCheckInCount, width: "80px", align: "center" },
	{ prop: "attendanceRate", label: TEXT.tableAttendanceRate, width: "80px", align: "center" },
	{ prop: "decLessonCount", label: TEXT.tableDescLessonCount, width: "80px", align: "center" },
	{ prop: "consumedCount", label: TEXT.tableConsumedCount, width: "80px", align: "center" },
	{ prop: "lessonStatus", label: TEXT.tableLessonStatus, "min-width": 100, "show-overflow-tooltip": true },
	{ prop: "lessonStatus2", label: TEXT.tableStatus, width: "80px", align: "center" },
	{ prop: "evaluationSummary", label: TEXT.tableEvaluation, "min-width": 180, "show-overflow-tooltip": true },
	{ prop: "action", label: TEXT.tableAction, width: "80px", align: "center", fixed: "right" },
];

const tableColumns = computed(() => {
	return baseTableColumns.filter((col) => visibleColumns[col.prop as keyof typeof visibleColumns] !== false);
});

const pageIndex = ref(1);
const pageSize = ref(30);
const pageData = ref(createPageDTO<CourseListVO>());
const selectedRows = ref<CourseListVO[]>([]);
const courseDetailDialogRef = ref<CourseDetailDialogInstance | null>(null);
const repeatScheduleDialogRef = ref<RepeatScheduleDialogInstance | null>(null);
const freeScheduleDialogRef = ref<FreeScheduleDialogInstance | null>(null);
const evaluationDialogVisible = ref(false);
const evaluationEditDialogVisible = ref(false);
const evaluationSubmitting = ref(false);
const currentEvaluationLesson = ref<CourseListVO>();
const evaluationDialogRows = ref<LessonEvaluationRow[]>([]);
const editingEvaluation = reactive<LessonEvaluationRow>({
	studentDisplayName: "",
	commentTimeText: "-",
});
const batchModifyDialogVisible = ref(false);
const batchModifySubmitting = ref(false);
const batchTeacherOptions = ref<SelectOption[]>([]);
const batchAssistantOptions = ref<SelectOption[]>([]);
const batchRoomOptions = ref<SelectOption[]>([]);
const batchModifyForm = reactive<{
	dayOffset?: number;
	startTime: string;
	endTime: string;
	teacherId?: number;
	assistantId?: number;
	classroomId?: number;
}>({
	dayOffset: 1,
	startTime: "",
	endTime: "",
	teacherId: undefined,
	assistantId: undefined,
	classroomId: undefined,
});
const editCourseDialogVisible = ref(false);
const editCourseSubmitting = ref(false);
const exporting = ref(false);
const editingCourseRow = ref<CourseListVO>();
const editCourseForm = reactive<{
	id?: number;
	teacherId?: number;
	assistantId?: number;
	courseDate: string;
	startTime: string;
	endTime: string;
	roomId?: number;
	decCount?: number;
	enableReserve: boolean;
	batchSyncTime: boolean;
	checkConflict: boolean;
}>({
	teacherId: undefined,
	assistantId: undefined,
	courseDate: "",
	startTime: "",
	endTime: "",
	roomId: undefined,
	decCount: undefined,
	enableReserve: false,
	batchSyncTime: false,
	checkConflict: false,
});

// 自定义列状态管理
const columnPopoverVisible = ref(false);
const defaultColumns = {
	lessonTimeText: true,
	courseName: true,
	className: true,
	teacherNames: true,
	courseType: true,
	assistantNames: true,
	classroomName: true,
	canReserve: true,
	studentCount: true,
	checkInCount: true,
	attendanceRate: true,
	decLessonCount: true,
	consumedCount: true,
	lessonStatus: true,
	lessonStatus2: true,
	evaluationSummary: true,
};
const visibleColumns = reactive({ ...defaultColumns });
const columnDraft = reactive({ ...defaultColumns });

const displayPageData = computed(() => pageData.value);
const lessonEvaluations = ref<Record<number, EvaluationVO[]>>({});

function parseLessonDate(value?: string) {
	const dateText = value?.match(/\d{4}-\d{2}-\d{2}/)?.[0];
	if (!dateText) return undefined;

	const date = new Date(`${dateText}T00:00:00`);
	if (Number.isNaN(date.getTime())) return undefined;
	return date;
}

function getWeekStart(date: Date) {
	const cloned = new Date(date);
	const day = cloned.getDay();
	const diff = day === 0 ? -6 : 1 - day;
	cloned.setDate(cloned.getDate() + diff);
	cloned.setHours(0, 0, 0, 0);
	return cloned;
}

function isSameWeek(target: Date, base: Date) {
	return getWeekStart(target).getTime() === getWeekStart(base).getTime();
}

function normalizeText(value?: string) {
	return (value || "").trim().toLowerCase();
}

function includesKeyword(source: unknown, keyword: string) {
	if (!keyword) return true;
	return String(source || "")
		.toLowerCase()
		.includes(keyword);
}

function buildMockPageData() {
	const today = new Date();
	const currentWeekStart = getWeekStart(today);
	const previousWeekStart = new Date(currentWeekStart);
	previousWeekStart.setDate(previousWeekStart.getDate() - 7);
	const classKeyword = normalizeText(filters.className);
	const courseKeyword = normalizeText(filters.courseName);
	const teacherKeyword = normalizeText(filters.teacherName);
	const studentKeyword = normalizeText(filters.studentName);

	const filteredRows = DEV_MOCK_SCHEDULE_ROWS.filter((row) => {
		const lessonDate = parseLessonDate(row.lessonTimeText);
		if (!lessonDate) return false;

		if (filters.cycle === 1 && !isSameWeek(lessonDate, today)) return false;
		if (filters.cycle === 2 && getWeekStart(lessonDate).getTime() !== previousWeekStart.getTime()) return false;
		if (filters.cycle === 3 && lessonDate.getTime() < currentWeekStart.getTime()) return false;
		if (filters.startDate && lessonDate.getTime() < new Date(`${filters.startDate}T00:00:00`).getTime()) return false;
		if (filters.endDate && lessonDate.getTime() > new Date(`${filters.endDate}T23:59:59`).getTime()) return false;
		if (!includesKeyword(row.className, classKeyword)) return false;
		if (!includesKeyword(row.courseName, courseKeyword)) return false;
		if (!includesKeyword(row.teacherNames, teacherKeyword)) return false;
		if (!includesKeyword((row as any).studentNames, studentKeyword)) return false;

		return true;
	});

	const start = (pageIndex.value - 1) * pageSize.value;
	const rows = filteredRows.slice(start, start + pageSize.value);

	return createPageDTO<CourseListVO>({
		pageIndex: pageIndex.value,
		pageSize: pageSize.value,
		total: filteredRows.length,
		rows,
	});
}

function applyMockFallback(reason: "empty" | "error") {
	pageData.value = buildMockPageData();
	selectedRows.value = [];

	if (isDev) {
		console.info(`[Schedule] Using local mock schedule data (${reason}).`);
	}
}

function canUseDevScheduleMock(rows: CourseListVO[]) {
	const mockIds = new Set(DEV_MOCK_SCHEDULE_ROWS.map((row) => row.id));
	return rows.length > 0 && rows.every((row) => typeof row.id === "number" && mockIds.has(row.id));
}

function buildEvaluationMap(rows: EvaluationVO[]) {
	const mapped: Record<number, EvaluationVO[]> = {};

	rows.forEach((item) => {
		if (typeof item.lessonId !== "number") return;
		if (!mapped[item.lessonId]) {
			mapped[item.lessonId] = [];
		}
		mapped[item.lessonId].push(item);
	});

	lessonEvaluations.value = mapped;
}

function canUseDevEvaluationMock(rows: CourseListVO[]) {
	return canUseDevScheduleMock(rows);
}

function applyMockEvaluationFallback(rows: CourseListVO[]) {
	if (!isDev || !canUseDevEvaluationMock(rows)) {
		lessonEvaluations.value = {};
		return;
	}

	buildEvaluationMap(DEV_MOCK_EVALUATIONS);
	console.info("[Schedule] Using local mock evaluation data.");
}

function getLessonEvaluations(lessonId?: number) {
	if (typeof lessonId !== "number") return [];
	return lessonEvaluations.value[lessonId] || [];
}

function getEvaluationSummary(row: CourseListVO) {
	const evaluations = getLessonEvaluations(row.id);
	if (!evaluations.length) return TEXT.evaluationEmpty;

	const totalScore = evaluations.reduce((sum, item) => sum + (item.overallScore || 0), 0);
	const averageScore = (totalScore / evaluations.length).toFixed(1);

	return `${evaluations.length}${TEXT.evaluationCountUnit} / ${TEXT.evaluationAvgPrefix}${averageScore}`;
}

function getEvaluationTooltip(row: CourseListVO) {
	const evaluations = getLessonEvaluations(row.id);
	if (!evaluations.length) return TEXT.evaluationEmpty;

	return evaluations
		.map((item, index) => {
			const score = item.overallScore ? `${item.overallScore}\u5206` : "--";
			const studentName = item.studentName || `\u5B66\u751F${index + 1}`;
			const content = item.content || TEXT.evaluationEmpty;
			return `${studentName} (${score})\n${content}`;
		})
		.join("\n\n");
}

async function loadEvaluations(rows: CourseListVO[]) {
	if (!rows.length) {
		lessonEvaluations.value = {};
		return;
	}

	// 暂时禁用点评列表接口调用，避免数据库表缺失导致的错误
	// TODO: 待后端修复 course_student 表后恢复接口调用
	applyMockEvaluationFallback(rows);
	return;

	// 以下为原接口调用代码（已禁用）
	try {
		const lessonIds = rows.map((row) => row.id).filter((id): id is number => id !== undefined);
		if (!lessonIds.length) {
			applyMockEvaluationFallback(rows);
			return;
		}

		const allEvaluations: EvaluationVO[] = [];
		for (const lessonId of lessonIds) {
			try {
				const res = await getEvaluationList({
					lessonId,
					pageIndex: 1,
					pageSize: 100,
				});
				const evaluationRows = res.data?.rows || [];
				allEvaluations.push(...evaluationRows);
			} catch (error) {
				console.error(`获取课次 ${lessonId} 的点评失败:`, error);
			}
		}

		if (allEvaluations.length) {
			buildEvaluationMap(allEvaluations);
			return;
		}

		applyMockEvaluationFallback(rows);
	} catch (error) {
		console.error(TEXT.evaluationLoadFailed, error);
		applyMockEvaluationFallback(rows);
	}
}

function splitStudentNames(value?: string) {
	return (value || "")
		.split(/[,\uFF0C]/)
		.map((item) => item.trim())
		.filter(Boolean);
}

function formatStudentDisplay(name?: string, mobile?: string) {
	return mobile ? `${name || "--"} ${mobile}` : name || "--";
}

function getCommentTimeText(item: EvaluationVO) {
	return String(item.commentTime || item.updateTime || item.createTime || item.addTime || "-");
}

function buildEvaluationDialogRows(lesson: CourseListVO) {
	const existing = getLessonEvaluations(lesson.id);
	const evaluationMap = new Map<number, EvaluationVO>();

	existing.forEach((item) => {
		if (typeof item.studentId === "number") {
			evaluationMap.set(item.studentId, item);
		}
	});

	const lessonStudents = DEV_MOCK_LESSON_STUDENTS[lesson.id as number] || [];
	if (lessonStudents.length) {
		return lessonStudents.map((student) => {
			const existingEvaluation = evaluationMap.get(student.studentId);
			return {
				...(existingEvaluation || {}),
				lessonId: lesson.id,
				teacherName: existingEvaluation?.teacherName || lesson.teacherNames,
				studentId: student.studentId,
				studentName: student.studentName,
				studentDisplayName: formatStudentDisplay(student.studentName, student.mobile),
				commentTimeText: existingEvaluation ? getCommentTimeText(existingEvaluation) : "-",
			} satisfies LessonEvaluationRow;
		});
	}

	if (existing.length) {
		return existing.map((item) => ({
			...item,
			lessonId: lesson.id,
			studentDisplayName: formatStudentDisplay(item.studentName),
			commentTimeText: getCommentTimeText(item),
		}));
	}

	return splitStudentNames((lesson as any).studentNames).map((studentName, index) => ({
		lessonId: lesson.id,
		teacherName: lesson.teacherNames,
		studentId: isDev ? -((lesson.id || 0) * 100 + index + 1) : undefined,
		studentName,
		studentDisplayName: studentName,
		commentTimeText: "-",
	}));
}

function openEvaluationDialog(row: CourseListVO) {
	currentEvaluationLesson.value = row;
	evaluationDialogRows.value = buildEvaluationDialogRows(row);
	evaluationDialogVisible.value = true;
}

function openEvaluationEditDialog(row: LessonEvaluationRow) {
	Object.assign(editingEvaluation, {
		id: row.id,
		teacherId: row.teacherId,
		teacherName: row.teacherName,
		studentId: row.studentId,
		studentName: row.studentName,
		lessonId: row.lessonId,
		courseTitle: row.courseTitle || currentEvaluationLesson.value?.courseName,
		overallScore: row.overallScore || 0,
		atmosphereScore: row.atmosphereScore || 0,
		attitudeScore: row.attitudeScore || 0,
		effectScore: row.effectScore || 0,
		content: row.content || "",
		studentDisplayName: row.studentDisplayName,
		commentTimeText: row.commentTimeText,
	});
	evaluationEditDialogVisible.value = true;
}

function syncEvaluationDialogRows() {
	if (!currentEvaluationLesson.value) return;
	evaluationDialogRows.value = buildEvaluationDialogRows(currentEvaluationLesson.value);
}

function updateMockEvaluations(payload: EvaluationSaveDTO) {
	const nextId = payload.id || Math.max(0, ...DEV_MOCK_EVALUATIONS.map((item) => item.id || 0)) + 1;
	const targetIndex = DEV_MOCK_EVALUATIONS.findIndex((item) => item.id === payload.id);
	const nextItem: EvaluationVO = {
		...payload,
		id: nextId,
	};

	if (targetIndex >= 0) {
		DEV_MOCK_EVALUATIONS.splice(targetIndex, 1, nextItem);
	} else {
		DEV_MOCK_EVALUATIONS.push(nextItem);
	}

	buildEvaluationMap(DEV_MOCK_EVALUATIONS);
}

async function handleSaveEvaluation() {
	if (!editingEvaluation.overallScore) {
		ElMessage.warning(TEXT.evaluationScoreRequired);
		return;
	}
	if (!editingEvaluation.studentId || editingEvaluation.studentId <= 0) {
		ElMessage.warning(TEXT.evaluationStudentMissing);
		return;
	}

	const currentLesson = currentEvaluationLesson.value;
	const payload: EvaluationSaveDTO = {
		id: editingEvaluation.id,
		teacherId:
			editingEvaluation.teacherId || Number(String(currentLesson?.teacherIds || "").split(",")[0]) || undefined,
		teacherName: editingEvaluation.teacherName || currentLesson?.teacherNames,
		studentId: editingEvaluation.studentId,
		studentName: editingEvaluation.studentName,
		lessonId: editingEvaluation.lessonId || currentLesson?.id,
		courseTitle: editingEvaluation.courseTitle || currentLesson?.courseName,
		overallScore: editingEvaluation.overallScore,
		atmosphereScore: editingEvaluation.atmosphereScore,
		attitudeScore: editingEvaluation.attitudeScore,
		effectScore: editingEvaluation.effectScore,
		content: editingEvaluation.content,
	};

	evaluationSubmitting.value = true;
	try {
		if (isDev && currentLesson && DEV_MOCK_LESSON_STUDENTS[currentLesson.id as number]) {
			updateMockEvaluations(payload);
		} else {
			const res = await saveEvaluation(payload);
			if (!(res.code === undefined || res.code === 0 || res.code === 10000)) {
				ElMessage.error(res.message || TEXT.evaluationSaveFailed);
				return;
			}
			await loadEvaluations(pageData.value.rows || []);
		}

		syncEvaluationDialogRows();
		evaluationEditDialogVisible.value = false;
		ElMessage.success(TEXT.evaluationSaveSuccess);
	} catch (error) {
		console.error(TEXT.evaluationSaveFailed, error);
		ElMessage.error(TEXT.evaluationSaveFailed);
	} finally {
		evaluationSubmitting.value = false;
	}
}

function isSuccessCode(code?: number) {
	return code === undefined || code === 0 || code === 10000;
}

function getSelectedCourseIds() {
	return selectedRows.value.map((row) => row.id).filter((id): id is number => typeof id === "number");
}

function getSelectedCourseCodes() {
	return selectedRows.value
		.map((row) => row.courseId)
		.filter((id): id is number => typeof id === "number")
		.map((id) => String(id));
}

async function confirmBatchAction(message: string, title: string) {
	await ElMessageBox.confirm(message, title, {
		type: "warning",
		confirmButtonText: title,
		cancelButtonText: TEXT.cancelAction,
	});
}

function removeMockCourses(ids: number[]) {
	const idSet = new Set(ids);

	for (let index = DEV_MOCK_SCHEDULE_ROWS.length - 1; index >= 0; index -= 1) {
		const rowId = DEV_MOCK_SCHEDULE_ROWS[index]?.id;
		if (typeof rowId === "number" && idSet.has(rowId)) {
			DEV_MOCK_SCHEDULE_ROWS.splice(index, 1);
		}
	}

	for (let index = DEV_MOCK_EVALUATIONS.length - 1; index >= 0; index -= 1) {
		const lessonId = DEV_MOCK_EVALUATIONS[index]?.lessonId;
		if (typeof lessonId === "number" && idSet.has(lessonId)) {
			DEV_MOCK_EVALUATIONS.splice(index, 1);
		}
	}

	ids.forEach((id) => {
		delete DEV_MOCK_LESSON_STUDENTS[id];
	});
}

function splitByComma(value?: string) {
	return (value || "")
		.split(/[,\uFF0C]/)
		.map((item) => item.trim())
		.filter(Boolean);
}

function parseIdNameOptions(idsText?: string, namesText?: string): SelectOption[] {
	const ids = splitByComma(idsText)
		.map((item) => Number(item))
		.filter((item) => Number.isFinite(item));
	const names = splitByComma(namesText);

	return ids.slice(0, names.length).map((value, index) => ({
		value,
		label: names[index],
	}));
}

function uniqueOptions(options: SelectOption[]) {
	const optionMap = new Map<number, string>();

	options.forEach((option) => {
		if (!optionMap.has(option.value)) {
			optionMap.set(option.value, option.label);
		}
	});

	return Array.from(optionMap.entries()).map(([value, label]) => ({ value, label }));
}

function buildBatchModifyOptions(rows: CourseListVO[]) {
	const teacherOptions: SelectOption[] = [];
	const assistantOptions: SelectOption[] = [];
	const roomOptions: SelectOption[] = [];

	rows.forEach((row) => {
		teacherOptions.push(...parseIdNameOptions(row.teacherIds, row.teacherNames));
		assistantOptions.push(...parseIdNameOptions(row.assistantIds, row.assistantNames));
		if (typeof row.classroomId === "number" && row.classroomName) {
			roomOptions.push({ value: row.classroomId, label: row.classroomName });
		}
	});

	batchTeacherOptions.value = uniqueOptions(teacherOptions);
	batchAssistantOptions.value = uniqueOptions(assistantOptions);
	batchRoomOptions.value = uniqueOptions(roomOptions);
}

function getOptionLabel(options: SelectOption[], value?: number) {
	if (typeof value !== "number") return undefined;
	return options.find((option) => option.value === value)?.label;
}

function resetBatchModifyForm() {
	Object.assign(batchModifyForm, {
		dayOffset: 1,
		startTime: "",
		endTime: "",
		teacherId: undefined,
		assistantId: undefined,
		classroomId: undefined,
	});
}

function applyTimeOverride(lessonTimeText: string | undefined, nextStartTime?: string, nextEndTime?: string) {
	const datePart = lessonTimeText?.match(/\d{4}-\d{2}-\d{2}/)?.[0] || "";
	const times = lessonTimeText?.match(/\d{2}:\d{2}:\d{2}/g) || [];
	const start = nextStartTime || times[0] || "00:00:00";
	const end = nextEndTime || times[1] || "00:00:00";
	if (!datePart) return lessonTimeText || "";
	return `${datePart} ${start} - ${end}`;
}

function applyDayOffset(lessonTimeText: string | undefined, dayOffset?: number) {
	if (!lessonTimeText || dayOffset === undefined || dayOffset === 0) return lessonTimeText || "";
	const dateText = lessonTimeText.match(/\d{4}-\d{2}-\d{2}/)?.[0];
	if (!dateText) return lessonTimeText;
	const date = new Date(`${dateText}T00:00:00`);
	if (Number.isNaN(date.getTime())) return lessonTimeText;
	date.setDate(date.getDate() + dayOffset);
	const nextDate = `${date.getFullYear()}-${String(date.getMonth() + 1).padStart(2, "0")}-${String(date.getDate()).padStart(2, "0")}`;
	return lessonTimeText.replace(dateText, nextDate);
}

function extractLessonDate(value?: string) {
	return value?.match(/\d{4}-\d{2}-\d{2}/)?.[0] || "";
}

function extractLessonTimes(value?: string) {
	const times = value?.match(/\d{2}:\d{2}:\d{2}/g) || [];
	return {
		startTime: times[0] || "",
		endTime: times[1] || "",
	};
}

function updateMockCourseStatus(ids: number[], isResume: boolean) {
	const idSet = new Set(ids);

	DEV_MOCK_SCHEDULE_ROWS.forEach((row) => {
		if (typeof row.id === "number" && idSet.has(row.id)) {
			row.lessonStatus2 = isResume ? "正常" : "停课";
		}
	});
}

function updateMockCourseReservation(ids: number[], enabled: boolean) {
	const idSet = new Set(ids);

	DEV_MOCK_SCHEDULE_ROWS.forEach((row) => {
		if (typeof row.id === "number" && idSet.has(row.id)) {
			row.canReserve = enabled ? "1" : "0";
		}
	});
}

function updateMockCoursesByBatch(payload: BatchUpdateCoursesDTO) {
	const idSet = new Set(payload.updateIds);

	DEV_MOCK_SCHEDULE_ROWS.forEach((row) => {
		if (typeof row.id !== "number" || !idSet.has(row.id)) return;

		let lessonTimeText = row.lessonTimeText;
		// 将时间对象转换为字符串格式 "HH:mm:ss"
		const startTimeStr = payload.startTime
			? `${String(payload.startTime.hour).padStart(2, "0")}:${String(payload.startTime.minute).padStart(2, "0")}:${String(payload.startTime.second).padStart(2, "0")}`
			: undefined;
		const endTimeStr = payload.endTime
			? `${String(payload.endTime.hour).padStart(2, "0")}:${String(payload.endTime.minute).padStart(2, "0")}:${String(payload.endTime.second).padStart(2, "0")}`
			: undefined;
		lessonTimeText = applyTimeOverride(lessonTimeText, startTimeStr, endTimeStr);
		lessonTimeText = applyDayOffset(lessonTimeText, payload.changeDays);
		row.lessonTimeText = lessonTimeText;

		if (payload.teacherIds && payload.teacherIds.length > 0) {
			row.teacherIds = payload.teacherIds.join(",");
		}
		if (payload.assistantIds && payload.assistantIds.length > 0) {
			row.assistantIds = payload.assistantIds.join(",");
		}
		if (payload.roomId) {
			row.classroomId = payload.roomId;
		}
	});
}

function updateMockCourse(row: CourseListVO, payload: UpdateCourseDTO) {
	if (payload.title) {
		row.courseName = payload.title;
	}
	if (payload.className) {
		row.className = payload.className;
	}
	if (payload.classId !== undefined) {
		row.classId = payload.classId;
	}
	if (payload.teacherId && payload.teacherName) {
		row.teacherIds = String(payload.teacherId);
		row.teacherNames = payload.teacherName;
	}
	if (payload.assistantId !== undefined) {
		row.assistantIds = payload.assistantId ? String(payload.assistantId) : "";
		row.assistantNames = payload.assistantName || "";
	}
	if (payload.roomId !== undefined) {
		row.classroomId = payload.roomId;
		row.classroomName = payload.roomName || "";
	}
	if (payload.decCount !== undefined) {
		row.decLessonCount = payload.decCount;
	}
	if (payload.enableReserve !== undefined) {
		row.canReserve = payload.enableReserve ? "1" : "0";
	}
	if (payload.startDate && payload.endDate) {
		const startTime = payload.startDate.split(" ")[1] || "00:00:00";
		const endTime = payload.endDate.split(" ")[1] || "00:00:00";
		row.lessonTimeText = `${extractLessonDate(payload.startDate)} ${startTime} - ${endTime}`;
	}
}

function getCellClass(prop: string) {
	if (prop === "lessonTimeText") return "cell-class-time";
	if (prop === "lessonStatus") return "cell-state";
	return "";
}

function handleSearch() {
	pageIndex.value = 1;
	loadData();
}

function handleReset() {
	Object.assign(filters, {
		pageIndex: 1,
		pageSize: 30,
		classId: undefined,
		courseId: undefined,
		startDate: "",
		endDate: "",
		teacherId: undefined,
		roomId: undefined,
		state: undefined,
		onTrial: undefined,
		cycle: undefined,
		className: "",
		courseName: "",
		teacherName: "",
		studentName: "",
	});
	pageIndex.value = 1;
	loadData();
}

function handleRefresh() {
	loadData();
}

function handlePrint() {
	// 获取当前可见的列
	const visibleCols = baseTableColumns.filter(
		(col) => col.prop !== "action" && visibleColumns[col.prop as keyof typeof visibleColumns] !== false,
	);

	if (visibleCols.length === 0) {
		ElMessage.warning("当前没有可打印的列");
		return;
	}

	// 生成表头
	const tableHeader = visibleCols.map((col) => `<th>${col.label}</th>`).join("");

	// 生成表格数据行
	const rowsHtml = (pageData.value.rows || [])
		.map((row) => {
			const tds = visibleCols
				.map((col) => {
					let value = (row as any)[col.prop];
					// 特殊处理某些字段
					if (col.prop === "canReserve") {
						value = value ? "是" : "否";
					}
					if (col.prop === "evaluationSummary") {
						value = getEvaluationSummary(row);
					}
					return `<td>${String(value ?? "-")}</td>`;
				})
				.join("");
			return `<tr>${tds}</tr>`;
		})
		.join("");

	// 生成完整的 HTML 文档
	const html = `
	<!doctype html>
	<html>
	<head>
		<meta charset="utf-8" />
		<title>课程表列表</title>
		<style>
			body { font-family: Arial, "Microsoft YaHei", sans-serif; padding: 20px; }
			h2 { margin: 0 0 12px; color: #303133; }
			table { border-collapse: collapse; width: 100%; }
			th, td { border: 1px solid #dcdfe6; padding: 8px; text-align: left; font-size: 12px; }
			th { background: #f5f7fa; color: #606266; font-weight: 600; }
			tr:nth-child(even) { background: #fafafa; }
			@media print {
				body { padding: 0; }
				h2 { font-size: 16px; }
				table { font-size: 10px; }
				th, td { padding: 4px; }
			}
		</style>
	</head>
	<body>
		<h2>课程表列表</h2>
		<table>
			<thead><tr>${tableHeader}</tr></thead>
			<tbody>${rowsHtml || `<tr><td colspan="${visibleCols.length}">暂无数据</td></tr>`}</tbody>
		</table>
	</body>
	</html>
	`;

	const win = window.open("", "_blank");
	if (!win) {
		ElMessage.warning("浏览器阻止了打印窗口，请允许弹窗后重试");
		return;
	}
	win.document.open();
	win.document.write(html);
	win.document.close();
	win.focus();
	win.print();
}

function handleExport() {
	const visibleCols = getScheduleExportColumns(baseTableColumns, visibleColumns);
	if (!visibleCols.length) {
		ElMessage.warning(TEXT.exportNoColumns);
		return;
	}

	const rowsToExport = selectedRows.value.length ? selectedRows.value : pageData.value.rows || [];
	if (!rowsToExport.length) {
		ElMessage.warning(TEXT.exportNoData);
		return;
	}

	exporting.value = true;
	try {
		const exportRows = buildScheduleExportRows(rowsToExport, visibleCols, (row) => getEvaluationSummary(row));
		const worksheet = XLSX.utils.json_to_sheet(exportRows);
		const workbook = XLSX.utils.book_new();
		const columnWidths = visibleCols.map((column) => {
			const headerText = String(column.label || column.prop || "");
			const maxContentLength = exportRows.reduce((max, row) => {
				const cellText = row[headerText] || "";
				return Math.max(max, cellText.length);
			}, headerText.length);
			return { wch: Math.min(Math.max(maxContentLength + 2, 10), 40) };
		});

		worksheet["!cols"] = columnWidths;
		XLSX.utils.book_append_sheet(workbook, worksheet, "schedule");
		XLSX.writeFile(workbook, buildScheduleExportFilename());
		ElMessage.success(TEXT.exportSuccess);
	} catch (error) {
		console.error(TEXT.exportFailed, error);
		ElMessage.error(TEXT.exportFailed);
	} finally {
		exporting.value = false;
	}
}

function openColumnPopover() {
	Object.assign(columnDraft, visibleColumns);
	columnPopoverVisible.value = true;
}

function restoreColumns() {
	Object.assign(columnDraft, defaultColumns);
	Object.assign(visibleColumns, defaultColumns);
	columnPopoverVisible.value = false;
}

function confirmColumns() {
	const picked = Object.values(columnDraft).some(Boolean);
	if (!picked) {
		ElMessage.warning("至少保留一列");
		return;
	}
	Object.assign(visibleColumns, columnDraft);
	columnPopoverVisible.value = false;
}

function handleScheduleCalendar() {
	router.push({ name: "scheduleCalendar" });
}

function openCourseDetailDialog(row: CourseListVO) {
	courseDetailDialogRef.value?.openDialog(row);
}

function handleRepeatSchedule() {
	const candidateRows = pageData.value.rows || [];
	if (!candidateRows.length) {
		ElMessage.warning(TEXT.repeatScheduleEmpty);
		return;
	}

	repeatScheduleDialogRef.value?.openDialog({
		selectedRow: selectedRows.value[0],
		candidateRows,
	});
}

function handleFreeSchedule() {
	const candidateRows = pageData.value.rows || [];
	if (!candidateRows.length) {
		ElMessage.warning(TEXT.freeScheduleEmpty);
		return;
	}

	freeScheduleDialogRef.value?.openDialog({
		selectedRow: selectedRows.value[0],
		candidateRows,
	});
}

async function handleBatchDelete() {
	if (!selectedRows.value.length) {
		ElMessage.warning(TEXT.deleteSelectWarning);
		return;
	}

	const ids = selectedRows.value.map((row) => row.id).filter((id): id is number => typeof id === "number");

	if (!ids.length) {
		ElMessage.warning(TEXT.deleteSelectWarning);
		return;
	}

	try {
		await ElMessageBox.confirm(
			TEXT.deleteConfirmMessage.replace("{count}", String(ids.length)),
			TEXT.deleteConfirmTitle,
			{
				type: "warning",
				confirmButtonText: TEXT.deleteAction,
				cancelButtonText: TEXT.cancelAction,
			},
		);

		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			removeMockCourses(ids);
			await loadData();
			ElMessage.success(TEXT.deleteSuccess);
			return;
		}

		const res = await deleteCourses(ids);
		if (!isSuccessCode(res.code)) {
			ElMessage.error(res.message || TEXT.deleteFailed);
			return;
		}

		await loadData();
		ElMessage.success(res.message || TEXT.deleteSuccess);
	} catch (error) {
		if (error === "cancel") {
			return;
		}

		console.error(TEXT.deleteFailed, error);
		ElMessage.error(TEXT.deleteFailed);
	}
}

function buildBatchModifyPayload(): BatchUpdateCoursesDTO | undefined {
	const lessonIds = getSelectedCourseIds();
	if (!lessonIds.length) return undefined;

	const hasChange =
		batchModifyForm.dayOffset !== undefined ||
		!!batchModifyForm.startTime ||
		!!batchModifyForm.endTime ||
		typeof batchModifyForm.teacherId === "number" ||
		typeof batchModifyForm.assistantId === "number" ||
		typeof batchModifyForm.classroomId === "number";

	if (!hasChange) {
		return undefined;
	}

	const payload: BatchUpdateCoursesDTO = {
		updateIds: lessonIds,
	};

	if (batchModifyForm.dayOffset !== undefined) {
		payload.changeDays = batchModifyForm.dayOffset;
	}
	if (batchModifyForm.startTime) {
		// 将字符串 "HH:mm:ss" 转换为时间对象
		const timeParts = batchModifyForm.startTime.split(":");
		payload.startTime = {
			hour: Number(timeParts[0]),
			minute: Number(timeParts[1]),
			second: timeParts[2] ? Number(timeParts[2]) : 0,
			nano: 0,
		};
	}
	if (batchModifyForm.endTime) {
		// 将字符串 "HH:mm:ss" 转换为时间对象
		const timeParts = batchModifyForm.endTime.split(":");
		payload.endTime = {
			hour: Number(timeParts[0]),
			minute: Number(timeParts[1]),
			second: timeParts[2] ? Number(timeParts[2]) : 0,
			nano: 0,
		};
	}
	if (typeof batchModifyForm.teacherId === "number") {
		payload.teacherIds = [batchModifyForm.teacherId];
	}
	if (typeof batchModifyForm.assistantId === "number") {
		payload.assistantIds = [batchModifyForm.assistantId];
	}
	if (typeof batchModifyForm.classroomId === "number") {
		payload.roomId = batchModifyForm.classroomId;
	}

	return payload;
}

function handleBatchModify() {
	if (!selectedRows.value.length) {
		ElMessage.warning(TEXT.batchModifySelectWarning);
		return;
	}

	buildBatchModifyOptions(pageData.value.rows || []);
	resetBatchModifyForm();
	batchModifyDialogVisible.value = true;
}

async function handleBatchModifySubmit() {
	if (batchModifyForm.startTime && batchModifyForm.endTime && batchModifyForm.startTime >= batchModifyForm.endTime) {
		ElMessage.warning(TEXT.batchModifyInvalidTime);
		return;
	}

	const payload = buildBatchModifyPayload();
	if (!payload) {
		ElMessage.warning(TEXT.batchModifyNoChangeWarning);
		return;
	}

	batchModifySubmitting.value = true;
	try {
		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			updateMockCoursesByBatch(payload);
			batchModifyDialogVisible.value = false;
			await loadData();
			ElMessage.success(TEXT.batchModifySuccess);
			return;
		}

		const res = await batchUpdateCourses(payload);
		if (!isSuccessCode(res.code)) {
			ElMessage.error(res.message || TEXT.batchModifyFailed);
			return;
		}

		batchModifyDialogVisible.value = false;
		await loadData();
		ElMessage.success(res.message || TEXT.batchModifySuccess);
	} catch (error) {
		console.error(TEXT.batchModifyFailed, error);
		ElMessage.error(TEXT.batchModifyFailed);
	} finally {
		batchModifySubmitting.value = false;
	}
}

async function handleStop() {
	const ids = getSelectedCourseIds();
	if (!ids.length) {
		ElMessage.warning(TEXT.batchSelectWarning);
		return;
	}

	try {
		await confirmBatchAction(TEXT.stopConfirmMessage.replace("{count}", String(ids.length)), TEXT.stopConfirmTitle);

		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			updateMockCourseStatus(ids, false);
			await loadData();
			ElMessage.success(TEXT.stopSuccess);
			return;
		}

		const res = await resumeCourses(ids, false);
		if (!isSuccessCode(res.code)) {
			ElMessage.error(res.message || TEXT.stopFailed);
			return;
		}

		await loadData();
		ElMessage.success(res.message || TEXT.stopSuccess);
	} catch (error) {
		if (error === "cancel") return;
		console.error(TEXT.stopFailed, error);
		ElMessage.error(TEXT.stopFailed);
	}
}

async function handleResume() {
	const ids = getSelectedCourseIds();
	if (!ids.length) {
		ElMessage.warning(TEXT.batchSelectWarning);
		return;
	}

	try {
		await confirmBatchAction(TEXT.resumeConfirmMessage.replace("{count}", String(ids.length)), TEXT.resumeConfirmTitle);

		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			updateMockCourseStatus(ids, true);
			await loadData();
			ElMessage.success(TEXT.resumeSuccess);
			return;
		}

		const res = await resumeCourses(ids, true);
		if (!isSuccessCode(res.code)) {
			ElMessage.error(res.message || TEXT.resumeFailed);
			return;
		}

		await loadData();
		ElMessage.success(res.message || TEXT.resumeSuccess);
	} catch (error) {
		if (error === "cancel") return;
		console.error(TEXT.resumeFailed, error);
		ElMessage.error(TEXT.resumeFailed);
	}
}

async function handleReservationOpen() {
	const ids = getSelectedCourseIds();
	const codes = getSelectedCourseCodes();
	if (!ids.length) {
		ElMessage.warning(TEXT.batchSelectWarning);
		return;
	}

	try {
		await confirmBatchAction(
			TEXT.reservationOpenConfirmMessage.replace("{count}", String(ids.length)),
			TEXT.reservationOpenConfirmTitle,
		);

		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			updateMockCourseReservation(ids, true);
			await loadData();
			ElMessage.success(TEXT.reservationOpenSuccess);
			return;
		}

		if (!codes.length) {
			ElMessage.error(TEXT.reservationOpenFailed);
			return;
		}

		const results = await Promise.all(codes.map((code) => switchSchedule({ id: code, status: "1" })));
		if (results.some((item) => !isSuccessCode(item.code))) {
			ElMessage.error(results.find((item) => !isSuccessCode(item.code))?.message || TEXT.reservationOpenFailed);
			return;
		}

		await loadData();
		ElMessage.success(TEXT.reservationOpenSuccess);
	} catch (error) {
		if (error === "cancel") return;
		console.error(TEXT.reservationOpenFailed, error);
		ElMessage.error(TEXT.reservationOpenFailed);
	}
}

async function handleReservationClose() {
	const ids = getSelectedCourseIds();
	const codes = getSelectedCourseCodes();
	if (!ids.length) {
		ElMessage.warning(TEXT.batchSelectWarning);
		return;
	}

	try {
		await confirmBatchAction(
			TEXT.reservationCloseConfirmMessage.replace("{count}", String(ids.length)),
			TEXT.reservationCloseConfirmTitle,
		);

		if (isDev && canUseDevScheduleMock(selectedRows.value)) {
			updateMockCourseReservation(ids, false);
			await loadData();
			ElMessage.success(TEXT.reservationCloseSuccess);
			return;
		}

		if (!codes.length) {
			ElMessage.error(TEXT.reservationCloseFailed);
			return;
		}

		const results = await Promise.all(codes.map((code) => switchSchedule({ id: code, status: "0" })));
		if (results.some((item) => !isSuccessCode(item.code))) {
			ElMessage.error(results.find((item) => !isSuccessCode(item.code))?.message || TEXT.reservationCloseFailed);
			return;
		}

		await loadData();
		ElMessage.success(TEXT.reservationCloseSuccess);
	} catch (error) {
		if (error === "cancel") return;
		console.error(TEXT.reservationCloseFailed, error);
		ElMessage.error(TEXT.reservationCloseFailed);
	}
}

function handleEdit(row: CourseListVO) {
	buildBatchModifyOptions(pageData.value.rows || []);
	editingCourseRow.value = row;

	const teacherOption = parseIdNameOptions(row.teacherIds, row.teacherNames)[0];
	const assistantOption = parseIdNameOptions(row.assistantIds, row.assistantNames)[0];
	const lessonDate = extractLessonDate(row.lessonTimeText);
	const lessonTimes = extractLessonTimes(row.lessonTimeText);

	Object.assign(editCourseForm, {
		id: row.id,
		teacherId: teacherOption?.value,
		assistantId: assistantOption?.value,
		courseDate: lessonDate,
		startTime: lessonTimes.startTime,
		endTime: lessonTimes.endTime,
		roomId: row.classroomId,
		decCount: row.decLessonCount,
		enableReserve: row.canReserve === "1",
		batchSyncTime: false,
		checkConflict: false,
	});

	editCourseDialogVisible.value = true;
}

async function handleEditCourseSubmit() {
	if (!editCourseForm.id) {
		ElMessage.error(TEXT.editCourseFailed);
		return;
	}
	if (!editCourseForm.teacherId) {
		ElMessage.warning(TEXT.editCourseRequiredTeacher);
		return;
	}
	if (!editCourseForm.courseDate) {
		ElMessage.warning(TEXT.editCourseRequiredDate);
		return;
	}
	if (!editCourseForm.startTime || !editCourseForm.endTime) {
		ElMessage.warning(TEXT.editCourseRequiredTime);
		return;
	}
	if (editCourseForm.startTime >= editCourseForm.endTime) {
		ElMessage.warning(TEXT.editCourseInvalidTime);
		return;
	}

	const payload: UpdateCourseDTO = {
		id: editCourseForm.id,
		teacherId: editCourseForm.teacherId,
		teacherName: getOptionLabel(batchTeacherOptions.value, editCourseForm.teacherId),
		assistantId: editCourseForm.assistantId,
		assistantName: getOptionLabel(batchAssistantOptions.value, editCourseForm.assistantId),
		startDate: `${editCourseForm.courseDate} ${editCourseForm.startTime}`,
		endDate: `${editCourseForm.courseDate} ${editCourseForm.endTime}`,
		roomId: editCourseForm.roomId,
		roomName: getOptionLabel(batchRoomOptions.value, editCourseForm.roomId),
		decCount: editCourseForm.decCount,
		enableReserve: editCourseForm.enableReserve,
		batchSyncTime: editCourseForm.batchSyncTime,
		checkConflict: editCourseForm.checkConflict,
	};

	editCourseSubmitting.value = true;
	try {
		if (isDev && editingCourseRow.value && canUseDevScheduleMock([editingCourseRow.value])) {
			updateMockCourse(editingCourseRow.value, payload);
			editCourseDialogVisible.value = false;
			await loadData();
			ElMessage.success(TEXT.editCourseSuccess);
			return;
		}

		const res = await updateCourse(payload);
		if (!isSuccessCode(res.code)) {
			ElMessage.error(res.message || TEXT.editCourseFailed);
			return;
		}

		editCourseDialogVisible.value = false;
		await loadData();
		ElMessage.success(res.message || TEXT.editCourseSuccess);
	} catch (error) {
		console.error(TEXT.editCourseFailed, error);
		ElMessage.error(TEXT.editCourseFailed);
	} finally {
		editCourseSubmitting.value = false;
	}
}

function handlePageChange(data: PageDTO<CourseListVO>) {
	pageIndex.value = data.pageIndex;
	pageSize.value = data.pageSize;
	loadData();
}

function handleSelectionChange(rows: CourseListVO[]) {
	selectedRows.value = rows;
}

async function loadData() {
	try {
		const res = await getCourseListPage({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			classId: filters.classId,
			courseId: filters.courseId,
			startDate: filters.startDate,
			endDate: filters.endDate,
			teacherId: filters.teacherId,
			roomId: filters.roomId,
			state: filters.state,
			onTrial: filters.onTrial,
			// 兼容旧字段
			cycle: filters.cycle,
			className: filters.className,
			courseName: filters.courseName,
			teacherName: filters.teacherName,
			studentName: filters.studentName,
		});

		if (res.data?.rows?.length) {
			pageData.value = createPageDTO<CourseListVO>({
				pageIndex: res.data.pageIndex || pageIndex.value,
				pageSize: res.data.pageSize || pageSize.value,
				total: res.data.total || 0,
				rows: res.data.rows || [],
			});
			selectedRows.value = [];
			await loadEvaluations(pageData.value.rows || []);
			return;
		}

		if (isDev) {
			applyMockFallback("empty");
			await loadEvaluations(pageData.value.rows || []);
			return;
		}

		pageData.value = createPageDTO<CourseListVO>({
			pageIndex: pageIndex.value,
			pageSize: pageSize.value,
			total: 0,
			rows: [],
		});
		selectedRows.value = [];
		lessonEvaluations.value = {};
	} catch (error) {
		console.error(TEXT.loadFailed, error);

		if (isDev) {
			applyMockFallback("error");
			await loadEvaluations(pageData.value.rows || []);
			return;
		}

		lessonEvaluations.value = {};
		ElMessage.error(TEXT.loadFailed);
	}
}

onMounted(() => {
	loadData();
});
</script>

<style scoped>
.schedule-container {
	padding: 16px;
	height: calc(100vh - 32px);
	overflow-y: auto;
}

.schedule-content {
	background: #fff;
	border-radius: 6px;
	padding: 16px;
	display: flex;
	flex-direction: column;
	gap: 16px;
	min-height: 0;
}

.filter-area {
	display: flex;
	justify-content: space-between;
	align-items: flex-start;
	gap: 16px;
}

.filter-row {
	display: flex;
	flex-wrap: wrap;
	gap: 16px;
	flex: 1;
}

.filter-item {
	display: flex;
	align-items: center;
	gap: 8px;
}

.filter-label {
	min-width: 56px;
	color: #303133;
	text-align: right;
	font-size: 14px;
}

.filter-input {
	width: 120px;
}

.filter-buttons {
	display: flex;
	align-items: center;
	gap: 8px;
	margin-left: 8px;
}

.filter-actions {
	display: flex;
	align-items: center;
	gap: 8px;
	flex-shrink: 0;
}

.batch-actions {
	display: flex;
	gap: 12px;
	flex-wrap: wrap;
	padding: 12px 0;
	border-bottom: 1px solid #ebeef5;
	align-items: center;
}

.batch-actions .el-button {
	display: inline-flex;
	align-items: center;
	justify-content: flex-start;
	gap: 6px;
	padding: 8px 12px;
}

.batch-actions .el-button .el-icon {
	display: inline-flex;
	align-items: center;
	justify-content: center;
	flex-shrink: 0;
	line-height: 1;
}

.batch-actions .el-button .el-icon svg {
	width: 14px !important;
	height: 14px !important;
	display: inline-block;
	vertical-align: middle;
}

.batch-actions .el-button span {
	display: inline-block;
	vertical-align: middle;
	line-height: 1;
	white-space: nowrap;
}

:deep(.cell-class-time) {
	color: #409eff;
	font-weight: 500;
}

:deep(.cell-state) {
	color: #67c23a;
	font-weight: 500;
}

:deep(.cell-evaluation-empty) {
	color: #909399;
}

.evaluation-dialog {
	display: flex;
	flex-direction: column;
	gap: 16px;
}

.evaluation-tip {
	font-size: 13px;
	color: #606266;
}

.batch-modify-dialog {
	display: flex;
	flex-direction: column;
	gap: 12px;
}

.batch-modify-tip {
	font-size: 13px;
	color: #606266;
	padding: 12px 16px;
	background: #f5f7fa;
	border-radius: 8px;
}

.field-tip {
	font-size: 12px;
	color: #909399;
	margin-top: 6px;
}

.column-trigger-wrap {
	display: inline-block;
}

.column-popover {
	.column-title {
		font-size: 14px;
		font-weight: 500;
		color: #303133;
		margin-bottom: 12px;
	}

	.column-options {
		display: grid;
		grid-template-columns: repeat(3, 1fr);
		gap: 12px;
		margin-bottom: 16px;

		.el-checkbox {
			margin-right: 0;
		}
	}

	.column-actions {
		display: flex;
		justify-content: flex-end;
		gap: 12px;
	}
}

@media (max-width: 1400px) {
	.filter-row {
		flex-direction: column;
	}

	.filter-item {
		width: 100%;
	}

	.filter-label {
		min-width: 80px;
	}

	.filter-input {
		flex: 1;
	}
}
</style>
