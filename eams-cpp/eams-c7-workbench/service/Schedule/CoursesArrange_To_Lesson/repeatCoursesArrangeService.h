#pragma once
#ifndef _REPEAT_COURSES_ARRANGE_SERVICE_H_
#define _REPEAT_COURSES_ARRANGE_SERVICE_H_
#include "domain/dto/Schedule/repeatCoursesArrangeDTO.h"

/**
 * 重复排课服务实现
 */
class RepeatCoursesArrangeService
{
public:
	// 保存重复排课数据
	int64_t saveRepeatCoursesArrange(const repeatCoursesArrangeDTO::Wrapper& dto);
};

#endif // !_REPEAT_COURSES_ARRANGE_SERVICE_H_
