#pragma once
#ifndef _NOTICE_DO_H_
#define _NOTICE_DO_H_

#include "../DoInclude.h"

/**
 * 公告实体类 - 对应 notice 表
 */
class NoticeDO : public BaseDO
{
    // ID（主键）
    MYSQL_SYNTHESIZE(oatpp::UInt64, id, Id);
    // 标题
    MYSQL_SYNTHESIZE(std::string, title, Title);
    // 内容（HTML）
    MYSQL_SYNTHESIZE(std::string, content, Content);
    // 阅读次数
    MYSQL_SYNTHESIZE(int, viewNum, ViewNum);
    // 创建人 ID
    MYSQL_SYNTHESIZE(oatpp::UInt64, creator, Creator);
    // 编辑人 ID
    MYSQL_SYNTHESIZE(oatpp::UInt64, editor, Editor);
    // 添加时间
    MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
    // 修改时间
    MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
    // 是否删除（0-未删，1-已删）
    MYSQL_SYNTHESIZE(int, deleted, Deleted);

public:
    NoticeDO() : BaseDO("notice")
    {
        MYSQL_ADD_FIELD_PK("id", "bi", id);
        MYSQL_ADD_FIELD("title", "s", title);
        MYSQL_ADD_FIELD("content", "s", content);
        MYSQL_ADD_FIELD("view_num", "i", viewNum);
        MYSQL_ADD_FIELD("creator", "bi", creator);
        MYSQL_ADD_FIELD("editor", "bi", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
    }
};

// 智能指针别名
typedef std::shared_ptr<NoticeDO> PtrNoticeDO;

#endif // !_NOTICE_DO_H_