/** 角色信息 */
export interface RolepermDTO {
	/** 角色 ID */
	id?: number;
	/** 角色编码 */
	code?: string;
	/** 角色名称 */
	name?: string;
}

/** 角色查询参数 */
export interface RolepermQuery {
	/** 角色 ID */
	id?: number;
	/** 页码 */
	pageIndex?: number;
	/** 每页条数 */
	pageSize?: number;
}

/** 角色员工信息 */
export interface RolepermStaffDTO {
	/** 员工 ID */
	staffId?: number;
	/** 角色 ID */
	roleId?: number;
	/** 员工姓名 */
	name?: string;
	/** 员工手机号 */
	mobile?: string;
}

/** 当前可选员工 */
export interface RolepermOperatorDTO {
	/** 员工 ID */
	id?: number;
	/** 员工姓名 */
	name?: string;
	/** 职位名称 */
	positionName?: string;
}

/** 权限描述对象 */
export interface QuanXianMiaoShuDuiXiang {
	/** 权限 ID */
	id?: number;
	/** 权限编码 */
	code?: string;
	/** 权限名称 */
	name?: string;
	/** 分组名称 */
	groupName?: string;
	/** 父级 ID */
	parentId?: string;
	/** 前端路由路径 */
	path?: string;
	/** 接口请求 URL */
	url?: string;
	/** 是否启用 */
	enabled?: 0 | 1;
}

/** 权限分组 VO */
export interface QuanXianFenZuVo {
	/** 分组名称 */
	groupName?: string;
	/** 该分组下的权限列表 */
	permissions?: QuanXianMiaoShuDuiXiang[];
	/** 该分组下已选中的权限列表 */
	selectedPermissions?: QuanXianMiaoShuDuiXiang[];
}
