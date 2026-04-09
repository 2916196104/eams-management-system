export interface TrialCard extends Record<string, any> {
	courseId?: number;
	pageIndex?: number;
	pageSize?: number;
	state?: string;
	title?: string;
	id?: number | string;
	name?: string;
	courseName?: string;
	classHours?: number;
	issueCount?: number;
	claimedCount?: number;
	validDays?: number;
	endDate?: string;
	enabled?: string | boolean;
	rows?: TrialCard[];
	total?: number;
}

export interface TrialCardDetail {
	id: number;
}

export interface TrialCardRecord extends Record<string, any> {
	pageIndex?: number;
	pageSize?: number;
	studentId?: number;
	trialId?: number;
	list?: Array<Record<string, any>>;
}

export interface SaveCard {
	courseId: number;
	endDate?: string;
	id: number;
	isActive?: boolean;
	lessonCount: number;
	name: string;
	totalIssue: number;
	validDays: number;
}

export interface deleteCard {
	value?: Array<number | string>;
	mediaType?: {
		present?: boolean;
	};
}
