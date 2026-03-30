/** 设置分类（列表接口返回） */
export interface SysParamDTO {
	/** 分类编码 */
	code: string;
	/** 分类 ID */
	id: number;
	/** 分类名称 */
	name: string;
	/** 备注 */
	remark?: string;
	/** 排序号 */
	sortNum: number;
}

/** 设置选项（详情/保存接口使用） */
export interface SysParamOptionDTO {
	/** 分类编码 */
	code: string;
	/** 选项 ID */
	id: number;
	/** 描述信息 */
	info?: string;
	/** 选项名称 */
	name: string;
	/** 所属分类 ID */
	settingId: number;
	/** 排序号 */
	sortNum: number;
	/** 参数值 */
	value: boolean | number | string;
	/** 值类型 */
	valueType: string;
}
