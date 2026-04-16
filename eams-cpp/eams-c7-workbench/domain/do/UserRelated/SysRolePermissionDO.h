#pragma once

#ifndef _SYSROLEPERMSISSION_H_
#define _SYSROLEPERMSISSION_H_
#include "../DoInclude.h"

class SysRolePermissionDO : public BaseDO
{
    // 自增id（主键）
    MYSQL_SYNTHESIZE(int, id, Id);

    // 角色id
    MYSQL_SYNTHESIZE(string, roleId, RoleId);

    // 权限id（菜单id）
    MYSQL_SYNTHESIZE(string, permissionId, PermissionId);

public:
    SysRolePermissionDO() : BaseDO("sys_role_permission")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("role_id", "s", roleId);
        MYSQL_ADD_FIELD("permission_id", "s", permissionId);
    }
};

typedef std::shared_ptr<SysRolePermissionDO> SysRolePermissionDOPtr;

#endif // !_SYSROLEPERMSISSION_H_
