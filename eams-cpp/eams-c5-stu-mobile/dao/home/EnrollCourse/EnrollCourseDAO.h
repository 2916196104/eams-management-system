#pragma once





#ifndef _ENROLLCOURES_DAO_
#define _ENROLLCOURES_DAO_
#include "BaseDAO.h"
#include "../../../domain/do/home/EnrollCourse/EnrollCourseDO.h"
#include "../../../domain/query/home/EnrollCourse/EnrollCourseQuery.h"


class EnrollCourseDAO : public BaseDAO
{
private:


	inline std::string queryConditionBuilder(const EnrollCourseQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const EnrollCourseQuery::Wrapper& query);
	// 分页查询数据
	std::list<EnrollCourseDO> selectWithPage(const EnrollCourseQuery::Wrapper& query);


};





#endif