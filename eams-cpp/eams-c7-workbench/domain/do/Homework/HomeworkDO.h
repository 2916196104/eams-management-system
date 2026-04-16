#pragma once

#ifndef _HOMEWORK_DO_H_
#define _HOMEWORK_DO_H_

#include "../DoInclude.h"

/**
 * 作业表数据对象（对应 homework 表）
 */
class HomeworkDO : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 班级ID
    MYSQL_SYNTHESIZE(int64_t, classId, ClassId);
    // 作业标题
    MYSQL_SYNTHESIZE(string, title, Title);
    // 作业内容
    MYSQL_SYNTHESIZE(string, content, Content);
    // 创建人（教师ID）
    MYSQL_SYNTHESIZE(int64_t, creator, Creator);
    // 修改人（教师ID）
    MYSQL_SYNTHESIZE(int64_t, editor, Editor);
    // 添加时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);
    // 编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
    // 删除标记
    MYSQL_SYNTHESIZE(bool, deleted, Deleted);
    // 创建者所属组织ID
    MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
    HomeworkDO() : BaseDO("homework")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);
        MYSQL_ADD_FIELD("class_id", "i", classId);
        MYSQL_ADD_FIELD("title", "s", title);
        MYSQL_ADD_FIELD("content", "s", content);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("editor", "i", editor);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("edit_time", "s", editTime);
        MYSQL_ADD_FIELD("deleted", "b", deleted);
        MYSQL_ADD_FIELD("org_id", "i", orgId);
    }
};

typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;

#endif // _HOMEWORK_DO_H_