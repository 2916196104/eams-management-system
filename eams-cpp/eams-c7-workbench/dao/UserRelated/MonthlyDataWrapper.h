#pragma once
#ifndef _SELECTTEACHERWRAPPER_H_
#define _SELECTTEACHERWRAPPER_H_
#include "Mapper.h"
#include "domain/do/UserRelated/MonthlyDataDO.h"

class MonthlyDataWrapperPtr : public Mapper<MonthlyDataViewDOPtr>
{
public:
	MonthlyDataViewDOPtr mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<MonthlyDataViewDO>();
		data->setRollcall_count(resultSet->getDouble("rollcall_count"));
		data->setLesson_count(resultSet->getDouble("lesson_count"));
		data->setStudent_count(resultSet->getDouble("student_count"));
		data->setCourse_count(resultSet->getDouble("course_count"));
		return data;
	}
};

#endif

