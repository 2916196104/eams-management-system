#pragma once
#ifndef HOMEWORKDO_H
#define HOMEWORKDO_H

#include "DoInclude.h"

/**
 * homework表数据库实体类
 */
class HomeworkDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 班级ID
	MYSQL_SYNTHESIZE(long long, classId, ClassId);
	// 作业标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 作业内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(long long, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 组织ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);

public:
	HomeworkDO() : BaseDO("homework")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 班级ID
		MYSQL_ADD_FIELD("class_id", "i", classId);
		// 作业标题
		MYSQL_ADD_FIELD("title", "s", title);
		// 作业内容
		MYSQL_ADD_FIELD("content", "s", content);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 编辑人
		MYSQL_ADD_FIELD("editor", "i", editor);
		// 添加时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 编辑时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};

typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;

#endif // HOMEWORKDO_H