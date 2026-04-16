#pragma once
#ifndef _CLASSGRADE_DO_
#define _CLASSGRADE_DO_
#include "../DoInclude.h"

/**
 * 年级表数据库实体类
 * 对应表: class_grade
 */
class ClassGradeDO : public BaseDO
{
	// 主键 (bigint unsigned - 64位无符号整数)
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 年级名称 (varchar)
	MYSQL_SYNTHESIZE(string, name, Name);
	// 入学年份 (int)
	MYSQL_SYNTHESIZE(int, year, Year);
	// 备注 (varchar)
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 排序 (int)
	MYSQL_SYNTHESIZE(int, sortNum, SortNum);
	// 创建人 (bigint unsigned - 关联staff.id，存储用户ID而非姓名)
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑人 (bigint unsigned - 关联staff.id，存储用户ID而非姓名)
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 添加时间 (datetime)
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间 (datetime)
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记 (tinyint - 0未删除 1已删除)
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
public:
	ClassGradeDO() : BaseDO("class_grade")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("year", "i", year);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("sort_num", "i", sortNum);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("editor", "ull", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
	}
};
// 给ClassGradeDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ClassGradeDO> PtrClassGradeDO;
#endif // !_CLASSGRADE_DO_