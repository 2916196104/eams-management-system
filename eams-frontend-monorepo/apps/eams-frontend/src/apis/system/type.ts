export interface DictionaryCategory {
	id: string;
	label: string;
	code?: string;
	itemCount: number;
	remark?: string;
	sortNum?: number;
}

export interface DictionaryItem {
	id: string;
	categoryId: string;
	name: string;
	info?: string;
	sortNum?: number;
}

export interface DictTypeDTO {
	id: number;
	code?: string;
	name?: string;
	remark?: string;
	sortNum?: string | number;
}

export interface DatadictVO {
	id: number;
	dictId?: number;
	info?: string;
	name?: string;
	softNum?: number;
}

export interface NoticeSettingDTO {
	id?: number;
	emailon: boolean;
	messageId_eg?: string;
	messageon: boolean;
	noticewechatId?: string;
	tips?: string;
	wechaton: boolean;
	name?: string;
}
