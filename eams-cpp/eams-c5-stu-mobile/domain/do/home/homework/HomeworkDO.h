#pragma once

#ifndef _HOMEWORK_DO_
#define _HOMEWORK_DO_
#include "../../DoInclude.h"

class HomeworkDO : public BaseDO
{
    // ===================== 1. 定义属性 + 自动生成get/set方法 =====================
    // 主键ID（bigint unsigned → uint64_t，非空自增）
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 班级ID（bigint → uint64_t，NOT NULL）
    MYSQL_SYNTHESIZE(uint64_t, classId, ClassId);
    // 标题（varchar(255) → string，NOT NULL，utf8mb4）
    MYSQL_SYNTHESIZE(string, title, Title);
    // 内容（text → string，NOT NULL，utf8mb4）
    MYSQL_SYNTHESIZE(string, content, Content);
    // 创建人（bigint → uint64_t，DEFAULT NULL）
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑人（bigint → uint64_t，DEFAULT NULL）
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 添加时间（datetime → string，DEFAULT NULL）
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 编辑时间（datetime → string，DEFAULT NULL）
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 删除标记（tinyint(1) → int，DEFAULT '0'，0=未删/1=已删）
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
    // 创建者所属组织ID（bigint → uint64_t，DEFAULT NULL）
    MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);

public:
    // ===================== 2. 构造函数：绑定表名 + 字段映射 =====================
    HomeworkDO() : BaseDO("homework") // 严格绑定数据库表名：homework
    {
        // 主键字段映射（字段名，类型标识，类属性）
        MYSQL_ADD_FIELD_PK("id", "i", id);

        // 普通字段映射（严格对应数据库字段名+类型，按表字段顺序排列）
        MYSQL_ADD_FIELD("class_id", "i", classId);    // bigint → 类型标识"i"
        MYSQL_ADD_FIELD("title", "s", title);         // varchar → 类型标识"s"
        MYSQL_ADD_FIELD("content", "s", content);     // text → 类型标识"s"
        MYSQL_ADD_FIELD("creator", "i", creator);     // bigint → 类型标识"i"
        MYSQL_ADD_FIELD("editor", "i", editor);       // bigint → 类型标识"i"
        MYSQL_ADD_FIELD("add_time", "s", addTime);    // datetime → 类型标识"s"
        MYSQL_ADD_FIELD("edit_time", "s", editTime);  // datetime → 类型标识"s"
        MYSQL_ADD_FIELD("deleted", "i", deleted);     // tinyint(1) → 类型标识"i"
        MYSQL_ADD_FIELD("org_id", "i", orgId);        // bigint → 类型标识"i"
    }
};

// ===================== 3. 定义智能指针别名（简化使用） =====================
typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;

#endif // !_HOMEWORK_DO_