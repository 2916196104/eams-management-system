#pragma once
#ifndef _COURSEEVALUATE_SERVICE_H_
#define _COURSEEVALUATE_SERVICE_H_

#include "domain/vo/CourseEvaluate/CourseEvaluateVO.h"
#include "domain/query/CourseEvaluate/CourseEvaluateQuery.h"
#include "domain/dto/CourseEvaluate/CourseEvaluateDTO.h"

/**
 * 课程评价服务实现
 */
class CourseEvaluateService
{
public:
	// 分页查询课程评价
	CourseEvaluatePageDTO::Wrapper listAll(const CourseEvaluateQuery::Wrapper& query);
	// 保存课程评价
	uint64_t saveData(const CourseEvaluateDTO::Wrapper& dto);
};

#endif // !_COURSEEVALUATE_SERVICE_H_
