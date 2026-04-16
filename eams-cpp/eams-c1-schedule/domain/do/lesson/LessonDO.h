#pragma once
#ifndef _LESSON_DO_
#define _LESSON_DO_

#include "BaseDO.h"
#include "SqlHelper.h"
#include <cstdint>
#include <string>

class LessonDO : public BaseDO
{
public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);

		MYSQL_ADD_FIELD("course_id", "ull", courseId);
		MYSQL_ADD_FIELD("class_id", "ull", classId);
		MYSQL_ADD_FIELD("room_id", "ull", roomId);
		MYSQL_ADD_FIELD("teacher_id", "ull", teacherId);

		MYSQL_ADD_FIELD("date", "s", date);
		MYSQL_ADD_FIELD("start_time", "s", startTime);
		MYSQL_ADD_FIELD("end_time", "s", endTime);

		MYSQL_ADD_FIELD("state", "i", state); // 课次状态
		MYSQL_ADD_FIELD("bookable", "i", bookable);

		// 其他字段按需添加
	}

	MYSQL_SYNTHESIZE(uint64_t, id, Id)
	MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId)
	MYSQL_SYNTHESIZE(uint64_t, classId, ClassId)
	MYSQL_SYNTHESIZE(uint64_t, roomId, RoomId)
	MYSQL_SYNTHESIZE(uint64_t, teacherId, TeacherId)

	MYSQL_SYNTHESIZE(std::string, date, Date)
	MYSQL_SYNTHESIZE(std::string, startTime, StartTime)
	MYSQL_SYNTHESIZE(std::string, endTime, EndTime)

	MYSQL_SYNTHESIZE(int, state, State)
	MYSQL_SYNTHESIZE(int, bookable, Bookable)
};

#endif // !_LESSON_DO_