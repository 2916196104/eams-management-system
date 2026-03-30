#pragma once
#ifndef _INSTITUTION_DO_
#define _INSTITUTION_DO_

#include "SqlHelper.h"

/**
 * 机构数据库实体类
 * 对应数据库表: org
 */
class InstitutionDO : public BaseDO {
    // 使用宏自动生成 protected 变量和 get/set 方法
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    MYSQL_SYNTHESIZE(uint64_t, pid, Pid);
    MYSQL_SYNTHESIZE(std::string, name, Name);
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
    MYSQL_SYNTHESIZE(int, level, Level);
    MYSQL_SYNTHESIZE(std::string, shortname, Shortname);
    MYSQL_SYNTHESIZE(std::string, contactName, ContactName);    
    MYSQL_SYNTHESIZE(std::string, phone, Phone);        
    MYSQL_SYNTHESIZE(std::string, fax, Fax);            
    MYSQL_SYNTHESIZE(std::string, email, Email);        
    MYSQL_SYNTHESIZE(int, sortNum, SortNum);                  
    MYSQL_SYNTHESIZE(int, state, State);             
    MYSQL_SYNTHESIZE(std::string, info, Info);

public:
    // 构造函数：指定表名 "org"
    InstitutionDO() : BaseDO("org") {
        // 注册主键和字段 (第一个参数是数据库列名，第二个是类型标识符，第三个是变量名)
        MYSQL_ADD_FIELD_PK("id", "i", id);
        MYSQL_ADD_FIELD("pid", "i", pid);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("level", "i", level);
        MYSQL_ADD_FIELD("shortname", "s", shortname);
        MYSQL_ADD_FIELD("contact_name", "s", contactName);
        MYSQL_ADD_FIELD("phone", "s", phone);
        MYSQL_ADD_FIELD("fax", "s", fax);
        MYSQL_ADD_FIELD("email", "s", email);
        MYSQL_ADD_FIELD("sort_num", "i", sortNum);
        MYSQL_ADD_FIELD("state", "i", state);
        MYSQL_ADD_FIELD("info", "s", info);
    }
};

// 定义智能指针别名
typedef std::shared_ptr<InstitutionDO> PtrInstitutionDO;

#endif // _INSTITUTION_DO_