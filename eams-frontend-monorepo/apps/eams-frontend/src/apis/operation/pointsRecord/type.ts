export interface PointsRecordListItem extends Record<string, any> {
	name?: string;
	pageIndex?: number;
	pageSize?: number;
	phone?: string | number;
	reason?: string;
	studentName?: string;
	phoneNumber?: string;
	changePoints?: number;
	remainingPoints?: number;
	description?: string;
	changeTime?: string;
	student?: string;
}

export interface AdjustPointsRecordRequest {
	name?: string;
	point?: number;
	content?: string;
}
