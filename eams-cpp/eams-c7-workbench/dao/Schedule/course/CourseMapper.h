#pragma once
#ifndef _COURSE_MAPPER_H_
#define _COURSE_MAPPER_H_
#include "Mapper.h"
#include "domain/do/Schedule/course/CourseDO.h"

class CourseMapper : public Mapper<CourseDO>
{
public:
	CourseDO mapper(ResultSet* resultSet) const override
	{
		CourseDO data;
		data.setId(resultSet->getInt64(1));
		data.setName(resultSet->getString(2));
		data.setSubjectId(resultSet->getInt64(3));
		return data;
	}
};

class PtrCourseMapper : public Mapper<PtrCourseDO>
{
public:
	PtrCourseDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CourseDO>();
		data->setId(resultSet->getInt64(1));
		data->setName(resultSet->getString(2));
		data->setSubjectId(resultSet->getInt64(3));
		return data;
	}
};

class CourseNameMapper : public Mapper<std::string>
{
public:
	std::string mapper(ResultSet* resultSet) const override
	{
		return resultSet->getString(1);
	}
};

#endif
