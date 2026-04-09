export interface GiftList extends Record<string, any> {
	name?: string;
	pageIndex?: number;
	pageSize?: number;
	state?: number | string;
	id?: number | string;
	giftName?: string;
	schoolName?: string;
	points?: number;
	redeemedCount?: number;
	viewCount?: number;
	lastEditTime?: string;
	image?: string;
	materialId?: string | number;
	materialName?: string;
	category?: string;
	rows?: GiftList[];
	total?: number;
}

export interface SaveGiftParams extends Record<string, any> {
	id?: number | string;
	categoryId?: number;
	content?: string;
	cover?: string;
	credit?: number;
	materialId?: string;
	name?: string;
}

export interface UseOrbanGiftParams extends Record<string, any> {
	name?: string[];
	ids?: Array<number | string>;
	status?: number;
}

export interface GetGiftDetailParams {
	id: string;
}

export interface DeleteGiftParams {
	name?: string[];
}
