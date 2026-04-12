/**
 * 授权登录响应数据对象
 */
export interface Oauth2TokenDTO {
	/** 访问令牌 */
	token: string;
	/** 刷新令牌 */
	refreshToken: string;
	/** 访问令牌头前缀 */
	tokenHead: string;
}

/**
 * 用户登录传输数据
 */
export interface LoginDTO {
	/** 用户名 */
	username: string;
	/** 密码 */
	password: string;
	/** 验证码 */
	code?: string;
	/** 终端类型，可选值为manager/user，默认manager */
	terminalType?: string;
}

/**
 * 用户信息类型定义
 */
export interface UserInfo {
	/** 唯一id */
	id: string;
	/** 用户名 */
	username: string;
	/** 头像 */
	avatar?: string;
	/** 角色 */
	roles?: Array<string>;
}

/**
 * 菜单类型定义
 */
export interface Menu {
	/** 菜单唯一标识 */
	id: string;
	/** 菜单名称 */
	text: string;
	/** 菜单图标 */
	icon: string;
	/** 菜单路径 */
	href?: string;
	/** 菜单父节点 */
	pid?: string;
	/** 子菜单 */
	children?: Array<Menu>;
}
