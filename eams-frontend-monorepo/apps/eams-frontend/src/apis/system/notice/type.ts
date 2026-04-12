export interface INoticeList {
	type?: string;
	title?: string;
	creator?: number | string;
	publisher?: string;
	pageSize?: number;
	pageNum?: number;
	isTop?: number;
	isEnable?: number;
}

export interface INoticeSave {
	id: number;
	title: string;
	content: string;
}

export interface INoticeDel {
	ids: number[];
}
