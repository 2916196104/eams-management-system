<script setup lang="ts">
import { computed, reactive, ref } from "vue";
import ParentNavBar from "@/components/parent/ParentNavBar.vue";
import { useUserStore } from "@/store/userStore";

definePage({
	name: "studentEdit",
	style: {
		navigationBarTitleText: "学生资料",
		titleNView: false,
	},
});

interface StudentDetailPayload {
	name?: string;
	gender?: string;
	relation?: string;
	grade?: string;
	idCard?: string;
	birthday?: string;
}

const route = useRoute();
const userStore = useUserStore();
const gradeOptions = ref<Array<string>>([]);
const loading = ref(false);
const saving = ref(false);

const studentId = computed(() => String((route.query?.id as string) || ""));
const isEditMode = computed(() => Boolean(studentId.value));
const student = computed(() => userStore.students.find((item) => item.id === studentId.value));

const form = reactive({
	name: "",
	gender: "男" as "男" | "女",
	relation: "妈妈",
	grade: "",
	idCard: "",
	birthday: "2026-03-27",
});

function applyStudentDetail(detail?: StudentDetailPayload | null) {
	if (!detail) return;
	form.name = detail.name || form.name;
	form.gender = detail.gender === "女" ? "女" : detail.gender === "男" ? "男" : form.gender;
	form.relation = detail.relation || form.relation;
	form.grade = detail.grade || form.grade;
	form.idCard = detail.idCard || form.idCard;
	form.birthday = detail.birthday || form.birthday;
}

function fillFormFromStore() {
	if (!student.value) return;
	applyStudentDetail({
		name: student.value.name,
		gender: student.value.gender,
		relation: student.value.relation,
		grade: student.value.grade,
		idCard: student.value.idCard,
		birthday: student.value.birthday,
	});
}

function normalizeDetail(raw: any): StudentDetailPayload | null {
	if (!raw) return null;

	let detail = raw;
	if (typeof raw === "string") {
		try {
			detail = JSON.parse(raw);
		}
		catch {
			return { name: raw };
		}
	}

	if (typeof detail !== "object" || Array.isArray(detail)) return null;

	return {
		name: detail.name || detail.studentName || detail.nickName || "",
		gender: detail.gender || detail.sex || detail.genderText || "",
		relation: detail.relation || detail.identity || detail.identityName || "",
		grade: detail.grade || detail.gradeName || detail.grade_level || "",
		idCard: detail.idCard || detail.idNumber || detail.cardNo || "",
		birthday: detail.birthday || detail.birthDate || detail.birth || "",
	};
}

function buildStudentPayload() {
	return {
		id: studentId.value || undefined,
		name: form.name.trim(),
		gender: form.gender,
		relation: form.relation,
		grade: form.grade,
		idCard: form.idCard.trim(),
		birthday: form.birthday,
	};
}

function resolveSavedStudentId(raw: any) {
	if (typeof raw === "string" && raw.trim()) return raw.trim();
	if (typeof raw === "number") return String(raw);
	if (raw && typeof raw === "object") {
		return String(raw.id || raw.studentId || raw.data || studentId.value || "");
	}
	return studentId.value || "";
}

async function loadStudentDetail() {
	if (!studentId.value) return;

	loading.value = true;
	try {
		const res: any = await (Apis as any).me.get_me_currentStudentQueryOne({
			params: {
				id: studentId.value,
			},
		});
		const detail = normalizeDetail(res?.data);
		if (detail) {
			applyStudentDetail(detail);
			userStore.upsertStudent({
				id: studentId.value,
				name: detail.name || form.name,
				gender: detail.gender === "女" ? "女" : "男",
				relation: detail.relation || form.relation,
				grade: detail.grade || form.grade,
				idCard: detail.idCard || form.idCard,
				birthday: detail.birthday || form.birthday,
			});
		}
		else {
			fillFormFromStore();
		}
	}
	catch {
		fillFormFromStore();
	}
	finally {
		loading.value = false;
	}
}

async function loadGrades() {
	try {
		const res: any = await (Apis as any).me.get_me_getOptionalGrade({
			params: {
				pageIndex: 1,
				pageSize: 50,
			},
		});
		const rows = Array.isArray(res?.data?.rows) ? res.data.rows : [];
		gradeOptions.value = rows.map((item: any) => item?.name).filter(Boolean);
		if (!form.grade && gradeOptions.value.length) {
			form.grade = gradeOptions.value[0];
		}
	}
	catch {
		gradeOptions.value = ["2027级"];
		if (!form.grade) form.grade = gradeOptions.value[0];
	}
}

function selectGender() {
	uni.showActionSheet({
		itemList: ["男", "女"],
		success: ({ tapIndex }) => {
			form.gender = tapIndex === 1 ? "女" : "男";
		},
	});
}

function selectRelation() {
	uni.showActionSheet({
		itemList: ["妈妈", "爸爸", "其他监护人"],
		success: ({ tapIndex }) => {
			form.relation = ["妈妈", "爸爸", "其他监护人"][tapIndex] || "妈妈";
		},
	});
}

function selectGrade() {
	const items = gradeOptions.value.length ? gradeOptions.value : ["2027级"];
	uni.showActionSheet({
		itemList: items,
		success: ({ tapIndex }) => {
			form.grade = items[tapIndex] || items[0];
		},
	});
}

async function saveStudent() {
	if (!form.name.trim()) {
		uni.showToast({ title: "请输入姓名", icon: "none" });
		return;
	}

	saving.value = true;
	try {
		const payload = buildStudentPayload();
		const res: any = await (Apis as any).me.post_me_addStudent({
			data: payload,
		});
		const savedId = resolveSavedStudentId(res?.data) || payload.id;

		userStore.upsertStudent({
			...payload,
			id: savedId || undefined,
		});

		uni.showToast({ title: "保存成功", icon: "success" });
		setTimeout(() => {
			uni.navigateBack();
		}, 400);
	}
	catch {
		uni.showToast({ title: "保存失败", icon: "none" });
	}
	finally {
		saving.value = false;
	}
}

function removeStudent() {
	if (!studentId.value) return;
	uni.showModal({
		title: "提示",
		content: "确认移除该学生吗？",
		success: async (result) => {
			if (!result.confirm) return;

			try {
				await (Apis as any).me.get_me_removeStudent({
					params: {
						id: Number(studentId.value),
					},
				});
				userStore.removeStudent(studentId.value);
				uni.showToast({ title: "已移除", icon: "success" });
				setTimeout(() => {
					uni.navigateBack();
				}, 400);
			}
			catch {
				uni.showToast({ title: "移除失败", icon: "none" });
			}
		},
	});
}

onMounted(async () => {
	fillFormFromStore();
	await Promise.all([loadGrades(), loadStudentDetail()]);
});
</script>

<template>
	<view class="page-shell">
		<ParentNavBar title="学生资料" />
		<view class="page-content">
			<view class="student-edit-card">
				<view class="student-edit-card__avatar">
					<view class="i-carbon:user-avatar-filled-alt text-76px text-#d9d9d9" />
				</view>

				<view v-if="loading" class="student-edit-card__loading">加载中...</view>

				<view class="student-edit-card__row">
					<text>姓名</text>
					<input v-model="form.name" class="student-edit-card__input" placeholder="请输入内容" />
				</view>
				<view class="student-edit-card__row student-edit-card__row--action" @click="selectGender">
					<text>性别</text>
					<view class="student-edit-card__row-right">
						<text>{{ form.gender }}</text>
						<view class="i-carbon:chevron-down text-16px text-#b4bcc9" />
					</view>
				</view>
				<view class="student-edit-card__row student-edit-card__row--action" @click="selectRelation">
					<text>您的身份</text>
					<view class="student-edit-card__row-right">
						<text>{{ form.relation }}</text>
						<view class="i-carbon:chevron-down text-16px text-#b4bcc9" />
					</view>
				</view>
				<view class="student-edit-card__row student-edit-card__row--action" @click="selectGrade">
					<text>所在年级</text>
					<view class="student-edit-card__row-right">
						<text>{{ form.grade || "请选择" }}</text>
						<view class="i-carbon:chevron-down text-16px text-#b4bcc9" />
					</view>
				</view>
				<view class="student-edit-card__row">
					<text>身份证号</text>
					<input v-model="form.idCard" class="student-edit-card__input" placeholder="请输入内容" />
				</view>
				<view class="student-edit-card__row">
					<text>出生年月</text>
					<picker mode="date" :value="form.birthday" @change="form.birthday = $event.detail.value">
						<view class="student-edit-card__row-right">
							<text>{{ form.birthday }}</text>
						</view>
					</picker>
				</view>

				<view class="student-edit-card__btn student-edit-card__btn--primary" @click="saveStudent">
					{{ saving ? "保存中..." : "保存" }}
				</view>
				<view v-if="isEditMode" class="student-edit-card__btn student-edit-card__btn--plain" @click="removeStudent">移除</view>
			</view>
		</view>
	</view>
</template>

<style scoped>
.page-shell {
	min-height: 100vh;
	background: #f5f7fb;
}

.page-content {
	padding: 12px 0 20px;
}

.student-edit-card {
	background: #fff;
}

.student-edit-card__avatar {
	height: 180px;
	display: flex;
	align-items: center;
	justify-content: center;
}

.student-edit-card__loading {
	padding: 0 18px 12px;
	font-size: 13px;
	color: #94a3b8;
}

.student-edit-card__row {
	padding: 16px 18px;
	display: flex;
	align-items: center;
	justify-content: space-between;
	border-top: 1px solid #eef2f7;
	font-size: 15px;
	color: #111827;
}

.student-edit-card__row--action {
	cursor: pointer;
}

.student-edit-card__row-right {
	display: flex;
	align-items: center;
	gap: 6px;
	color: #111827;
}

.student-edit-card__input {
	flex: 1;
	margin-left: 16px;
	text-align: right;
	font-size: 15px;
	color: #111827;
}

.student-edit-card__btn {
	margin: 16px 12px 0;
	height: 44px;
	display: flex;
	align-items: center;
	justify-content: center;
	border-radius: 999px;
	font-size: 18px;
}

.student-edit-card__btn--primary {
	background: linear-gradient(135deg, #31c7a5 0%, #28c39f 100%);
	color: #fff;
}

.student-edit-card__btn--plain {
	margin-bottom: 20px;
	border: 1px solid #31c7a5;
	color: #31c7a5;
	background: #fff;
}
</style>
