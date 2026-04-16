// d:\01项目\zero-one-eams2603\eams-frontend-monorepo\apps\eams-frontend\src\apis\material\materialManagement\type.ts

export interface MaterialRecordQuery {
	changeType?: number;
	materialId?: number;
	pageIndex: number;
	pageSize: number;
	staffId?: number;
	studentId?: number;
}

export interface MaterialRecordItem {
	addTime?: string;
	amount?: number;
	changeTargetId?: number;
	changeType?: number;
	id?: number;
	materialId?: number;
	reason?: string;
	remark?: string;
	staffId?: number;
	studentId?: number;
	// Some environments may return denormalized display fields in addition to the documented ids.
	materialName?: string;
	staffName?: string;
	studentName?: string;
}

export interface MaterialPageQuery {
	changeType?: number;
	materialId?: number;
	pageIndex: number;
	pageSize: number;
	staffId?: number;
	studentId?: number;
}

export interface MaterialItem {
	categoryId?: number;
	cover?: string;
	id?: number;
	info?: string;
	name?: string;
	schoolId?: number;
	state?: boolean;
}

export type MaterialDetail = MaterialItem;

export type MaterialStateValue = 0 | 1;

export interface MaterialSaveDTO {
	categoryId: number;
	cover?: string;
	id?: number;
	info?: string;
	name: string;
	schoolId: number;
	state?: boolean;
}
