#pragma once
#ifndef _CLASS_STUDENT_MAPPER_H_
#define _CLASS_STUDENT_MAPPER_H_
#include "Mapper.h"
#include "domain/do/Schedule/class_student/ClassStudentDO.h"

class ClassStudentMapper : public Mapper<ClassStudentDO>
{
public:
	ClassStudentDO mapper(ResultSet* resultSet) const override
	{
		ClassStudentDO data;
		data.setId(resultSet->getInt64(1));
		data.setClassId(resultSet->getInt64(2));
		data.setStudentId(resultSet->getInt64(3));
		data.setAddTime(resultSet->getString(4));
		data.setCreator(resultSet->getInt64(5));
		data.setReason(resultSet->getInt(6));
		data.setDeleted(resultSet->getInt(7));
		data.setRemark(resultSet->getString(8));
		data.setConsumeCourseId(resultSet->getInt64(9));
		return data;
	}
};

class ClassStudentIdMapper : public Mapper<int64_t>
{
public:
	int64_t mapper(ResultSet* resultSet) const override
	{
		return resultSet->getInt64(1);
	}
};

class ClassStudentCountMapper : public Mapper<int>
{
public:
	int mapper(ResultSet* resultSet) const override
	{
		return resultSet->getInt(1);
	}
};

#endif
