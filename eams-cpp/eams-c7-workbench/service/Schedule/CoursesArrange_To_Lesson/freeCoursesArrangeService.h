#pragma once
#ifndef _FREE_COURSES_ARRANGE_SERVICE_H_
#define _FREE_COURSES_ARRANGE_SERVICE_H_
#include "domain/dto/Schedule/freeCoursesArrangeDTO.h"
#include <unordered_map>

/**
 * 自由排课服务实现
 */
class FreeCoursesArrangeService
{
public:
	// 保存自由排课数据，返回排课成功次数
	uint64_t saveFreeCoursesArrange(const freeCoursesArrangeDTO::Wrapper& dto);
};

#endif // !_FREE_COURSES_ARRANGE_SERVICE_H_
