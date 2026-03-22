#pragma once
#ifndef _COURSEEVALUATE_DAO_H_
#define _COURSEEVALUATE_DAO_H_

#include "BaseDAO.h"
#include "../../domain/do/CourseEvaluateDO.h"
#include "../../domain/query/CourseEvaluate/CourseEvaluateQuery.h"

class CourseEvaluateDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const CourseEvaluateQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const CourseEvaluateQuery::Wrapper& query);
	// 分页查询数据
	std::list<CourseEvaluateDO> selectWithPage(const CourseEvaluateQuery::Wrapper& query);
	// 新增评价
	uint64_t insert(const CourseEvaluateDO& obj);
};

#endif // !_COURSEEVALUATE_DAO_H_
