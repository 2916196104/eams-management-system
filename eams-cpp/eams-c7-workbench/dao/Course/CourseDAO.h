#pragma once
#ifndef _COURSEDAO_H_
#define _COURSEDAO_H_
#include "../../domain/query/Course/CourseQuery.h"
#include "../../domain/do/Course/CourseDO.h"
#include "../../../lib-mysql/include/BaseDAO.h"
class CourseDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const CourseQuery::Wrapper& query, SqlParams& params);
public:
	uint64_t count(const CourseQuery::Wrapper& query);
	std::list<CourseDO> selectWithPage(const CourseQuery::Wrapper& query);
	std::list<CourseDO> selectById(const string& courseId);
};
#endif