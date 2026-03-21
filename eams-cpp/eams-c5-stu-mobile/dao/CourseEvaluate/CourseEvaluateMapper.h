#pragma once
#ifndef _COURSEEVALUATE_MAPPER_H_
#define _COURSEEVALUATE_MAPPER_H_

#include "Mapper.h"
#include "../../domain/do/CourseEvaluateDO.h"

class CourseEvaluateMapper : public Mapper<CourseEvaluateDO>
{
public:
	CourseEvaluateDO mapper(ResultSet* resultSet) const override
	{
		CourseEvaluateDO data;
		data.setId(resultSet->getUInt64(1));
		data.setCourseId(resultSet->getUInt64(2));
		data.setStudentId(resultSet->getUInt64(3));
		data.setOrderId(resultSet->getUInt64(4));
		data.setContent(resultSet->getString(5));
		data.setScore(resultSet->getInt(6));
		data.setState(resultSet->getInt(7));
		data.setCreator(resultSet->getUInt64(8));
		data.setEditor(resultSet->getUInt64(9));
		data.setAddTime(resultSet->getString(10));
		data.setEditTime(resultSet->getString(11));
		data.setDeleted(resultSet->getInt(12));
		return data;
	}
};

#endif // !_COURSEEVALUATE_MAPPER_H_
