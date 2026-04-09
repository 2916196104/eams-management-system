<script setup lang="ts">
import TeacherEmptyState from "@/components/teacher/TeacherEmptyState.vue";
import TeacherNavBar from "@/components/teacher/TeacherNavBar.vue";

definePage({
	name: "teacherSignupRecordDetail",
	style: {
		navigationBarTitleText: "报名记录详情",
		titleNView: false,
	},
});

interface DetailBlock {
	title: string;
	lines: string[];
}

const route = useRoute() as { query?: Record<string, string | string[] | undefined> };

const loading = ref(false);
const detailBlocks = ref<DetailBlock[]>([]);

const headerTitle = computed(() => readQuery("title") || "报名记录详情");
const headerSubtitle = computed(() => readQuery("subtitle"));
const headerMeta = computed(() => readQuery("meta"));

function readQuery(key: string) {
	const value = route.query?.[key];
	if (Array.isArray(value)) return value[0] || "";
	return value || "";
}

function formatLabel(key: string) {
	const map: Record<string, string> = {
		id: "记录ID",
		recordId: "记录ID",
		orderNo: "订单号",
		name: "姓名",
		studentName: "学员姓名",
		student_name: "学员姓名",
		mobile: "手机号",
		phone: "手机号",
		courseName: "课程名称",
		course_name: "课程名称",
		title: "标题",
		state: "状态",
		status: "状态",
		verifyState: "审核状态",
		addTime: "报名时间",
		add_time: "报名时间",
		createTime: "创建时间",
		remark: "备注",
	};

	return map[key] || key;
}

function stringifyValue(value: unknown) {
	if (value === null || value === undefined || value === "") return "--";
	if (typeof value === "string") return value;
	if (typeof value === "number" || typeof value === "boolean") return String(value);
	return JSON.stringify(value);
}

function objectToLines(record: Record<string, unknown>) {
	return Object.entries(record)
		.filter(([, value]) => value !== undefined)
		.map(([key, value]) => `${formatLabel(key)}：${stringifyValue(value)}`);
}

function buildBlocks(payload: any): DetailBlock[] {
	if (typeof payload === "string") {
		const lines = payload
			.split(/\r?\n/)
			.map((item) => item.trim())
			.filter(Boolean);

		return lines.length ? [{ title: "接口返回内容", lines }] : [];
	}

	const rows = Array.isArray(payload)
		? payload
		: Array.isArray(payload?.rows)
			? payload.rows
			: Array.isArray(payload?.list)
				? payload.list
				: Array.isArray(payload?.records)
					? payload.records
					: null;

	if (rows) {
		if (!rows.length) return [];

		return rows.map((item: any, index: number) => {
			if (typeof item === "string") {
				return {
					title: `详情 ${index + 1}`,
					lines: [item],
				};
			}

			return {
				title: item?.title || item?.courseName || item?.name || `详情 ${index + 1}`,
				lines: objectToLines(item || {}),
			};
		});
	}

	if (payload && typeof payload === "object") {
		return [
			{
				title: "详情信息",
				lines: objectToLines(payload),
			},
		];
	}

	return [];
}

async function loadDetail() {
	loading.value = true;

	try {
		const res: any = await (Apis as any).workbench.get_workbench_enrollment_detail({
			params: {
				pageIndex: Number(readQuery("pageIndex") || 1),
				pageSize: Number(readQuery("pageSize") || 10),
				id: readQuery("id") || undefined,
			},
		});

		const payload = res?.data?.data ?? res?.data ?? res;
		detailBlocks.value = buildBlocks(payload);
	} catch {
		detailBlocks.value = [];
		uni.showToast({ title: "报名详情加载失败", icon: "none" });
	} finally {
		loading.value = false;
	}
}

async function refreshPage() {
	await loadDetail();
	uni.showToast({ title: "已刷新", icon: "none" });
}

onShow(() => {
	void loadDetail();
});
</script>

<template>
	<view class="teacher-detail-page">
		<teacher-nav-bar title="报名记录详情" @refresh="refreshPage" />

		<view class="teacher-detail-page__content">
			<view class="teacher-detail-header">
				<view class="teacher-detail-header__title">{{ headerTitle }}</view>
				<view v-if="headerSubtitle" class="teacher-detail-header__subtitle">{{ headerSubtitle }}</view>
				<view v-if="headerMeta" class="teacher-detail-header__meta">{{ headerMeta }}</view>
			</view>

			<view v-if="detailBlocks.length" class="teacher-detail-list">
				<view v-for="(block, index) in detailBlocks" :key="`${block.title}-${index}`" class="teacher-detail-card">
					<view class="teacher-detail-card__title">{{ block.title }}</view>
					<view class="teacher-detail-card__body">
						<text v-for="(line, lineIndex) in block.lines" :key="`${index}-${lineIndex}`" class="teacher-detail-card__line">
							{{ line }}
						</text>
					</view>
				</view>
			</view>

			<teacher-empty-state v-else :title="loading ? '加载中...' : '暂无详情内容'" compact />
		</view>
	</view>
</template>

<style scoped>
.teacher-detail-page {
	min-height: 100vh;
	background: #f5f6fa;
}

.teacher-detail-page__content {
	padding: 12px;
}

.teacher-detail-header {
	border-radius: 16px;
	background: linear-gradient(135deg, #f6fffd 0%, #ffffff 100%);
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-detail-header__title {
	font-size: 18px;
	font-weight: 600;
	color: #101828;
}

.teacher-detail-header__subtitle {
	margin-top: 8px;
	font-size: 14px;
	color: #667085;
}

.teacher-detail-header__meta {
	margin-top: 8px;
	font-size: 12px;
	color: #98a2b3;
}

.teacher-detail-list {
	display: flex;
	flex-direction: column;
	gap: 10px;
	margin-top: 12px;
}

.teacher-detail-card {
	border-radius: 16px;
	background: #fff;
	padding: 16px;
	box-shadow: 0 6px 18px rgba(64, 86, 122, 0.04);
}

.teacher-detail-card__title {
	font-size: 15px;
	font-weight: 600;
	color: #111827;
}

.teacher-detail-card__body {
	display: flex;
	flex-direction: column;
	gap: 8px;
	margin-top: 12px;
}

.teacher-detail-card__line {
	font-size: 14px;
	line-height: 1.5;
	color: #475467;
	word-break: break-all;
}
</style>
