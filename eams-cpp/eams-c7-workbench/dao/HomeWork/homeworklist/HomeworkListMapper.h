#pragma once

#include "Mapper.h"
#include "domain/do/Homework/homeworklist/HomeworkListDO.h"

class HomeworkListViewMapper :public Mapper<HomeworkListViewDO>
{
public:
	HomeworkListViewDO mapper(ResultSet* res) const override
	{
		HomeworkListViewDO data;
		data.setTitle(res->getString("title"));
		data.setClassName(res->getString("class_name"));
		data.setCourseName(res->getString("course_name"));
		data.setNumber(res->getInt("number"));		
		return data;
	}
};