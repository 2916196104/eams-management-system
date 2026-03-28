#pragma once


#ifndef _SYSUSERROLEDO_H_
#define _SYSUSERROLEDO_H_
#include "../DoInclude.h"


/*
* 用户角色DO，主要对应表sys_user_role，主要用途，获取用户的角色id
*/

class SysUserRoleDO : public BaseDO
{
    // 自增id（主键）
    MYSQL_SYNTHESIZE(int, id, Id);

    // 用户id
    MYSQL_SYNTHESIZE(string, userId, UserId);

    // 角色id
    MYSQL_SYNTHESIZE(string, roleId, RoleId);

public:
    SysUserRoleDO() : BaseDO("sys_user_role")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("user_id", "s", userId);
        MYSQL_ADD_FIELD("role_id", "s", roleId);
    }
};

typedef std::shared_ptr<SysUserRoleDO> SysUserRoleDOPtr;
#endif // _SYSUSERROLEDO_H_