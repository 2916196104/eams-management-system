export interface CourseItemDTO {
	id?: string;
	name?: string;
	code?: string;
	[property: string]: any;
}

export interface ClassSummaryQueryDTO {
	gradeId?: number;
	name?: string;
	mobile?: string;
	stage?: string;
	status?: string;
	courseId?: number;
	pageIndex?: number;
	pageSize?: number;
}

export interface ClassSummaryItemDTO {
	id?: number;
	classId?: number;
	studentId?: string;
	name?: string;
	mobile?: string;
	lessonId?: number;
	lessonCount?: number;
	decLessonCount?: number;
	teacherId?: number;
	signState?: number;
	signTime?: string;
	signType?: number;
	[property: string]: any;
}

export interface SignupRecordQueryDTO {
	callbackId?: number;
	callBackId?: number;
	changeType?: number;
	courseName?: string;
	endTime?: string;
	pageIndex?: number;
	pageSize?: number;
	startTime?: string;
	studentName?: string;
	operatorName?: string;
}

export interface SignupRecordItemDTO {
	id?: number;
	addTime?: string;
	amount?: number;
	countLessonComplete?: number;
	countLessonTotal?: number;
	courseName?: string;
	operatorName?: string;
	remainingLessons?: number;
	studentName?: string;
	studentId?: string;
	subjectName?: string;
	verifyState?: number;
	[property: string]: any;
}

export interface BatchSignupRequest {
	ids: number[];
}

export interface BatchDeleteRequest {
	ids: number[];
}

export interface ExportSignupRecordRequest {
	studentName?: string;
	startTime?: string;
	endTime?: string;
	courseName?: string;
	operatorName?: string;
}

export interface CampusItemDTO {
	id?: string;
	name?: string;
	code?: string;
	[property: string]: any;
}

export interface FollowRecordQueryDTO {
	creator?: string;
	endTime?: string;
	keyword?: string;
	pageIndex?: number;
	pageSize?: number;
	stage?: number;
	startTime?: string;
	studentId?: number;
}

export interface FollowRecordItemDTO {
	id?: number;
	addTime?: string;
	contactNextTime?: string;
	contactPhone?: string;
	contactTime?: string;
	contactType?: number;
	creator?: number;
	creatorName?: string;
	info?: string;
	orgId?: number;
	stage?: number;
	studentId?: number;
	studentName?: string;
	[property: string]: any;
}

export interface FollowStageItemDTO {
	id?: string;
	name?: string;
	[property: string]: any;
}

export interface FollowRecordImportRequest {
	data?: FollowRecordItemDTO[];
	[property: string]: any;
}

export interface StudentConsoleQueryDTO {
	pageIndex?: number;
	pageSize?: number;
	keyword?: string;
	gradeId?: number;
	branchSchool?: string;
	teacherName?: string;
	stage?: string;
	[property: string]: any;
}

export interface StudentConsoleRowDTO {
	id?: number;
	studentId?: string;
	name?: string;
	schoolName?: string;
	parentName?: string;
	userName?: string;
	familyRel?: number | string;
	mobile?: string;
	counselorName?: string;
	gradeName?: string;
	countLessonRemaining?: number;
	credit?: number;
	gender?: number | string;
	age?: number;
	remark?: string;
	stage?: number | string;
	headImg?: string;
	[property: string]: any;
}

export interface StudentConsolePageDTO {
	pageIndex?: number;
	pageSize?: number;
	total?: number;
	totalCount?: number;
	totalElements?: number;
	rows?: StudentConsoleRowDTO[];
	list?: StudentConsoleRowDTO[];
	records?: StudentConsoleRowDTO[];
	content?: StudentConsoleRowDTO[];
	data?: unknown;
	[property: string]: any;
}

export interface StudentStageUpdateDTO {
	id?: number | string;
	studentId?: string;
	stage?: number;
	[property: string]: any;
}

export interface StudentCourseTimesQueryDTO {
	studentId: string;
}

export interface StudentCourseTimesItemDTO {
	countLessonComplet?: number;
	countLessonRefund?: number;
	countLessonTotal?: number;
	courseAmount?: number;
	courseName?: string;
	expireDate?: string;
	paidAmount?: number;
	progress?: string;
	remainingTimes?: number;
	startDate?: string;
	studentId?: string;
	studentName?: string;
}

export interface StudentCourseTimesSummaryDTO {
	studentId?: string;
	studentName?: string;
	courseTimes?: number;
	remainingTimes?: number;
	details?: StudentCourseTimesItemDTO[];
}

export interface StudentCourseQueryDTO {
	pageIndex?: number;
	pageSize?: number;
	name?: string;
}

export interface StudentCourseRowDTO {
	id?: string | number;
	courseName?: string;
	courseTimes?: number;
	unitPrice?: number;
	totalPrice?: number;
	unitName?: string;
	[property: string]: any;
}

export interface StudentCoursePageDTO {
	pageIndex?: number;
	pageSize?: number;
	total?: number;
	totalCount?: number;
	totalElements?: number;
	rows?: StudentCourseRowDTO[];
	list?: StudentCourseRowDTO[];
	records?: StudentCourseRowDTO[];
	content?: StudentCourseRowDTO[];
	data?: unknown;
	[property: string]: any;
}

export interface StudentEnrollRequestDTO {
	amount?: number;
	countLessonTotal?: number;
	courseId: number | string;
	expireDate?: string;
	paidAmount?: number;
	remark?: string;
	staffId?: number;
	startDate?: string;
	studentId: number | string;
	[property: string]: any;
}

export interface StudentDetailDTO extends StudentConsoleRowDTO {
	admissionTime?: string;
	birthday?: string;
	counselor?: number;
	courseId?: number;
	gradeId?: number;
	avatar?: string;
	idCard?: string;
	joinDate?: string;
	orgId?: number;
	schoolId?: number;
	source?: string;
	userId?: number;
	studentName?: string;
}

export interface StudentGraduationExportQueryDTO {
	graduationDateEnd?: string;
	graduationDateStart?: string;
	graduationState?: 0 | 1;
	name?: string;
	schoolId?: number;
}

export interface ResultDTO<T> {
	errMsg?: string;
	errMsgParams?: unknown[];
	result?: T;
}
