#pragma once
#ifndef _SYSUSERROLE_DO_
#define _SYSUSERROLE_DO_
#include "../DoInclude.h"

/**
 * 用户角色关联表数据库实体类
 * 对应表: sys_user_role
 */					
class SysUserRoleDO : public BaseDO
{
	// 主键 (int)
	MYSQL_SYNTHESIZE(int, id, Id);
	// 用户ID (varchar - 这里的ID在数据库里是字符串类型)
	MYSQL_SYNTHESIZE(string, userId, UserId);
	// 角色ID (varchar - 这里的ID在数据库里是字符串类型)
	MYSQL_SYNTHESIZE(string, roleId, RoleId);

public:
	SysUserRoleDO() : BaseDO("sys_user_role")
	{
		// 注意：这里的字段类型标记要和数据库严格对应
		MYSQL_ADD_FIELD_PK("id", "i", id);      // "i" 代表 int
		MYSQL_ADD_FIELD("user_id", "s", userId); // "s" 代表 string (对应varchar)
		MYSQL_ADD_FIELD("role_id", "s", roleId); // "s" 代表 string (对应varchar)
	}
};

// 定义智能指针别名
typedef std::shared_ptr<SysUserRoleDO> PtrSysUserRoleDO;

#endif // !_SYS_USER_ROLE_DO_