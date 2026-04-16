#pragma once
#ifndef CLASSGRADE_DO_
#define CLASSGRADE_DO_

#include "../DoInclude.h"

class ClassGradeDO : public BaseDO
{
	// 班级年级唯一ID
	MYSQL_SYNTHESIZE(int, id, Id);
	// 班级年级名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 入学年份
	MYSQL_SYNTHESIZE(int, year, Year);
	//备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//排序值
	MYSQL_SYNTHESIZE(int, sort, Sort);
	//创建人
	MYSQL_SYNTHESIZE(int, creator, Creator);
	//编辑人
	MYSQL_SYNTHESIZE(int, editor, Editor);
	//添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	//编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//删除标志
	MYSQL_SYNTHESIZE(int, deleted, Deleted);

public:
	ClassGradeDO() : BaseDO("class_grade")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name,false);
		MYSQL_ADD_FIELD_NULLABLE("year", "i", year,false);
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark,true);
		MYSQL_ADD_FIELD_NULLABLE("sort_num", "i", sort,false);
		MYSQL_ADD_FIELD_NULLABLE("creator", "i", creator,false);
		MYSQL_ADD_FIELD_NULLABLE("editor", "i", editor,false);
		MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime,false);
		MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime,false);
		MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleted,false);
	}
};
typedef shared_ptr<ClassGradeDO> ClassGradeDOPtr;
#endif // !CLASSGRADE_DO_
