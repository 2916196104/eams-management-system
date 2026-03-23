#pragma once
#ifndef STAFFPOSITIONDO_H
#define STAFFPOSITIONDO_H

#include "../do/DoInclude.h"

/**
 * staff_position表数据库实体类
 */
class StaffPositionDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 职位名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 创建者
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(long long, editor, Editor);

public:
	StaffPositionDO() : BaseDO("staff_position")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 职位名称
		MYSQL_ADD_FIELD("name", "s", name);
		// 添加时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 编辑时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 创建者
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 编辑者
		MYSQL_ADD_FIELD("editor", "i", editor);
	}
};

typedef std::shared_ptr<StaffPositionDO> PtrStaffPositionDO;

#endif // STAFFPOSITIONDO_H
