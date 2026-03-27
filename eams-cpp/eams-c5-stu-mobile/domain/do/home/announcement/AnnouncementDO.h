#pragma once
#ifndef _ANNOUNCEMENT_DO_
#define _ANNOUNCEMENT_DO_
#include "../../DoInclude.h"

/**
 * 示例数据库实体类
 */
class AnnouncementDO : public BaseDO
{
    // ========== 字段定义（严格对齐表结构） ==========
    // 编号（bigint → 64位，对应表中 id）
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 标题（varchar(255) → 对应表中 title）
    MYSQL_SYNTHESIZE(std::string, title, Title);
    // 类型（tinyint → 对应表中 type）
    MYSQL_SYNTHESIZE(int, type, Type);
    // 内容（text → 对应表中 content）
    MYSQL_SYNTHESIZE(std::string, content, Content);
    // 添加时间（datetime → 对应表中 add_time）
    MYSQL_SYNTHESIZE(std::string, add_time, Add_time);
    // 编辑时间（datetime → 对应表中 edit_time）
    MYSQL_SYNTHESIZE(std::string, edit_time, Edit_time);
    // 编辑人（bigint → 对应表中 editor）
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    //图片地址
    MYSQL_SYNTHESIZE(std::string, cover, Cover);

public:
    AnnouncementDO() : BaseDO("announcement") // 表名修正为 announcement（非 sample）
    {
        // ========== 数据库映射（严格对齐表字段名+类型） ==========
        MYSQL_ADD_FIELD_PK("id", "ll", id);                // bigint → "ll"
        MYSQL_ADD_FIELD("title", "s", title);             // varchar(255) → "s"
        MYSQL_ADD_FIELD("type", "i", type);               // tinyint → "i"
        MYSQL_ADD_FIELD("content", "s", content);         // text → "s"
        MYSQL_ADD_FIELD("add_time", "s", add_time);       // datetime → "s"
        MYSQL_ADD_FIELD("edit_time", "s", edit_time);     // datetime → "s"
        MYSQL_ADD_FIELD("editor", "i", editor);          // bigint → "ll"
        MYSQL_ADD_FIELD("cover", "s", cover);//varchar(255) → "s"
    }
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<AnnouncementDO> PtrAnnouncementDO;
#endif // !_ANNOUNCEMENT_DO_
