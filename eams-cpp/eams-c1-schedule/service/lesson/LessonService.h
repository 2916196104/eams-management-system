#pragma once
#ifndef _LESSON_SERVICE_
#define _LESSON_SERVICE_

#include "domain/query/lesson/LessonQuery.h"
#include "domain/vo/lesson/LessonVO.h"
#include "domain/do/lesson/LessonDO.h"
#include "domain/do/lesson/LessonExtDO.h"
#include "domain/dto/PayloadDTO.h"

class LessonService
{
public:
	// 分页获取课表
	LessonPageDTO::Wrapper listLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload);

	// 学生签到
	bool signLesson(uint64_t lessonId, const PayloadDTO& payload);

private:
	// 辅助函数：将单个 DO 转换为 VO
	LessonVO::Wrapper convertDoToVo(const LessonExtDO& doItem);
};

#endif // !_LESSON_SERVICE_