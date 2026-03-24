#pragma once
#ifndef _REGISTER_DO_H_
#define _REGISTER_DO_H_
#include "../DoInclude.h"

/**
 * 用户表数据库实体类（适配注册功能）
 */
class RegisterDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 手机号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 密码
	MYSQL_SYNTHESIZE(string, password, Password);
	
public:
	RegisterDO() : BaseDO("user") 
	{
		// 主键字段：id（类型s=字符串）
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 手机号（数据库字段名mobile，类型s）
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		// 姓名（数据库字段名name，类型s）
		MYSQL_ADD_FIELD("name", "s", name);
		// 密码（数据库字段名password，类型s）
		MYSQL_ADD_FIELD("password", "s", password);
	}
};

// 定义智能指针别名，方便使用
typedef std::shared_ptr<RegisterDO> PtrRegisterDO;

#endif // !_REGISTER_DO_H_