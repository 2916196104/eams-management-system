#pragma once
#ifndef _LESSON_DAO_H_
#define _LESSON_DAO_H_
#include "BaseDAO.h"
#include "domain/do/Schedule/lesson/LessonDO.h"
#include "domain/do/Schedule/lesson/ConflictInfo.h"
#include <set>

class LessonDAO : public BaseDAO
{
public:
	//如果需要检查冲突，则查询数据库中冲突的课程信息
	std::list<ConflictInfo> checkConflict(int64_t roomId, const std::string& date, const std::string& startTime, const std::string& endTime);
	std::list<ConflictInfo> checkConflictBatch(int64_t roomId, const std::set<std::string>& dates, const std::string& startTime, const std::string& endTime);
	//查询班级中某课程的最大节次
	int getMaxSnByClassIdAndCourseId(int64_t classId, int64_t courseId);
};

#endif
