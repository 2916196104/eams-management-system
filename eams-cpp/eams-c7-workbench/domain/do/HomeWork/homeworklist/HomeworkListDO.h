#pragma once

#include "../../DoInclude.h"


class HomeworkListDO :public BaseDO
{
	MYSQL_SYNTHESIZE(long long,id,Id);
	MYSQL_SYNTHESIZE(string, title, Title);
public:
	HomeworkListDO() :BaseDO("homework")
	{
		MYSQL_ADD_FIELD_PK("id", "ll", id);
		MYSQL_ADD_FIELD("title", "s", title);
	}
};

class HomeworkListViewDO :public HomeworkListDO
{
	//班级名称
	MYSQL_SYNTHESIZE(string, className, ClassName);
	//课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	//提交人数
	MYSQL_SYNTHESIZE(int, number, Number);
};

