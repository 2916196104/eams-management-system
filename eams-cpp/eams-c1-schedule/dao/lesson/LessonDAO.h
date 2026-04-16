#pragma once
#ifndef _LESSON_DAO_
#define _LESSON_DAO_

#include "BaseDAO.h"
#include "domain/do/lesson/LessonDO.h"
#include "domain/do/lesson/LessonExtDO.h"
#include "domain/query/lesson/LessonQuery.h"
#include <list>

class LessonDAO : public BaseDAO
{
public:
	// 统计总数 (用于分页)
	uint64_t countByQuery(const LessonQuery::Wrapper& query);

	// 联表分页查询课表 (返回 LessonExtDO)
	std::list<LessonExtDO> selectExtByPage(const LessonQuery::Wrapper& query, uint64_t studentId);

	// 根据 ID 查询单条基础课表
	LessonDO selectById(uint64_t id);

	// ==========================================================
	// 以下为原 LessonStudentDAO 的功能，现合并至此
	// ==========================================================

	// 查询指定学生在指定课程的签到状态
	int selectSignState(uint64_t lessonId, uint64_t studentId);

	// 更新签到状态
	int updateSignState(uint64_t lessonId, uint64_t studentId, int state);
};

#endif // !_LESSON_DAO_