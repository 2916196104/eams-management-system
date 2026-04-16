#pragma once
#ifndef _USER_DO_
#define _USER_DO_

#include "../DoInclude.h"
#include "SqlHelper.h"

/**
 * 学生表对应的数据库实体类
 * 数据库表：student
 */
class UserDO : public BaseDO
{   
    // 主键ID
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, mobile, Mobile);
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);


public:
    UserDO() : BaseDO("user")
    {
        // 注册主键
        MYSQL_ADD_FIELD_PK("id", "ull", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("mobile", "s", mobile);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("creator", "ull", creator);
        
    }
};

typedef shared_ptr<UserDO> PtrUserDO;
#endif // _USER_DO_