#pragma once
#ifndef _SYSROLEDO_
#define _SYSROLEDO_
#include "../DoInclude.h"

/**
 * 角色表数据库实体类
 * 对应表: sys_role
 */
class SysRoleDO : public BaseDO
{
	// 主键 (int)
	MYSQL_SYNTHESIZE(int, id, Id);
	// 角色名称 (varchar - 如：超级管理员、家长、老师)
	MYSQL_SYNTHESIZE(string, name, Name);
	// 角色编码 (varchar - 系统的唯一识别码，如：superadmin, parent)
	MYSQL_SYNTHESIZE(string, code, Code);

public:
	SysRoleDO() : BaseDO("sys_role")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);    // "i" 代表 int
		MYSQL_ADD_FIELD("name", "s", name);   // "s" 代表 string
		MYSQL_ADD_FIELD("code", "s", code);   // "s" 代表 string
	}
};

// 定义智能指针别名
typedef std::shared_ptr<SysRoleDO> PtrSysRoleDO;

#endif // !_SYS_ROLE_DO_