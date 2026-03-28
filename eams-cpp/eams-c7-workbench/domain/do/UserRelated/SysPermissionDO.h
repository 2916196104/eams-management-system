#pragma once

#ifndef _SYSPERMISSION_H_
#define _SYSPERMISSION_H_
#include "../DoInclude.h"

class SysPermissionDO : public BaseDO
{
    // 自增id（主键）
    MYSQL_SYNTHESIZE(int, id, Id);

    // 菜单名称
    MYSQL_SYNTHESIZE(string, name, Name);

    // 父级id（用于树结构）
    MYSQL_SYNTHESIZE(string, parentId, ParentId);

    // 接口URL
    MYSQL_SYNTHESIZE(string, url, Url);

    // 权限编码
    MYSQL_SYNTHESIZE(string, code, Code);

    // 前端路由路径
    MYSQL_SYNTHESIZE(string, path, Path);

    // 是否启用（1启用 0禁用）
    MYSQL_SYNTHESIZE(int, enabled, Enabled);

    // 分组
    MYSQL_SYNTHESIZE(string, groupName, GroupName);

public:
    SysPermissionDO() : BaseDO("sys_permission")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("parent_id", "s", parentId);
        MYSQL_ADD_FIELD("url", "s", url);
        MYSQL_ADD_FIELD("code", "s", code);
        MYSQL_ADD_FIELD("path", "s", path);
        MYSQL_ADD_FIELD("enabled", "i", enabled);
        MYSQL_ADD_FIELD("group_name", "s", groupName);
    }
};

typedef std::shared_ptr<SysPermissionDO> PtrSysPermissionDO;

#endif // !_SYSPERMISSION_H
