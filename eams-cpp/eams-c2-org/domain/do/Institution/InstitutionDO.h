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

public:
    // 构造函数：指定表名 "org"
    InstitutionDO() : BaseDO("org") {
        // 注册主键和字段 (第一个参数是数据库列名，第二个是类型标识符，第三个是变量名)
        // 类型标识："s"=string, "i"=int (文档默认只写了 sidf，对于 bigint 用 i 或 s 视底层驱动而定)
        MYSQL_ADD_FIELD_PK("id", "i", id);
        MYSQL_ADD_FIELD("pid", "i", pid);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("level", "i", level);
    }
};

// 定义智能指针别名
typedef std::shared_ptr<InstitutionDO> PtrInstitutionDO;

#endif // _INSTITUTION_DO_