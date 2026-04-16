#pragma once

#ifndef _SYSROLEDO_H_
#define _SYSROLEDO_H_
#include "../DoInclude.h"

/*
* 角色权限DO，主要对应表sys_role，主要用途，获取角色编码
*/

class SysRoleDO : public BaseDO
{
    // 自增id（主键）
    MYSQL_SYNTHESIZE(int, id, Id);

    // 角色名称
    MYSQL_SYNTHESIZE(string, name, Name);

    // 角色编码
    MYSQL_SYNTHESIZE(string, code, Code);

public:
    SysRoleDO() : BaseDO("sys_role")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("code", "s", code);
    }
};

typedef std::shared_ptr<SysRoleDO> PtrSysRoleDO;
#endif