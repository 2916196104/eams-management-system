#pragma once
#ifndef _REGISTER_DO_H_
#define _REGISTER_DO_H_
#include "../DoInclude.h"

/**
 * 用户表数据库实体类（适配注册功能）
 */
class RegisterDO : public BaseDO
{
	// 主键ID（自增，注册时无需赋值）
	MYSQL_SYNTHESIZE(string, id, Id);
	// 手机号（注册核心字段，唯一）
	MYSQL_SYNTHESIZE(string, telephoneNumber, TelephoneNumber);
	// 姓名（注册核心字段）
	MYSQL_SYNTHESIZE(string, name, Name);
	// 密码（注册核心字段，加密存储）
	MYSQL_SYNTHESIZE(string, password, Password);
	// 账号状态（注册时赋默认值1：正常）
	MYSQL_SYNTHESIZE(int, status, Status);
	// 创建人（注册时默认赋值为手机号或系统标识）
	MYSQL_SYNTHESIZE(string, createBy, CreateBy);
	// 创建时间（注册时赋值为当前时间）
	MYSQL_SYNTHESIZE(string, createTime, CreateTime);
	// 修改人（注册时默认与创建人一致）
	MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
	// 修改时间（注册时默认与创建时间一致）
	MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);
	// 登录次数（注册时默认0）
	MYSQL_SYNTHESIZE(int, loginTimes, LoginTimes);
	// 上次登录时间（注册时为空）
	MYSQL_SYNTHESIZE(string, latestLoginTime, LatestLoginTime);
	// 上次登录IP（注册时为空）
	MYSQL_SYNTHESIZE(string, latestLoginIp, LatestLoginIp);
public:
	// 构造函数：指定数据库表名 + 映射字段
	RegisterDO() : BaseDO("user") // 假设用户表名是 t_user，需替换为实际表名
	{
		// 主键字段：id（类型s=字符串）
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 手机号（数据库字段名telephone_number，类型s）
		MYSQL_ADD_FIELD("telephone_number", "s", telephoneNumber);
		// 姓名（数据库字段名name，类型s）
		MYSQL_ADD_FIELD("name", "s", name);
		// 密码（数据库字段名password，类型s）
		MYSQL_ADD_FIELD("password", "s", password);
		// 账号状态（数据库字段名status，类型i=整数）
		MYSQL_ADD_FIELD("status", "i", status);
		// 创建人（数据库字段名create_by，类型s）
		MYSQL_ADD_FIELD("create_by", "s", createBy);
		// 创建时间（数据库字段名create_time，类型s）
		MYSQL_ADD_FIELD("create_time", "s", createTime);
		// 修改人（数据库字段名update_by，类型s）
		MYSQL_ADD_FIELD("update_by", "s", updateBy);
		// 修改时间（数据库字段名update_time，类型s）
		MYSQL_ADD_FIELD("update_time", "s", updateTime);
		// 登录次数（数据库字段名login_times，类型i）
		MYSQL_ADD_FIELD("login_times", "i", loginTimes);
		// 上次登录时间（数据库字段名latest_login_time，类型s）
		MYSQL_ADD_FIELD("latest_login_time", "s", latestLoginTime);
		// 上次登录IP（数据库字段名latest_login_ip，类型s）
		MYSQL_ADD_FIELD("latest_login_ip", "s", latestLoginIp);
	}
};

// 定义智能指针别名，方便使用
typedef std::shared_ptr<RegisterDO> PtrRegisterDO;

#endif // !_REGISTER_DO_H_