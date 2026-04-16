#pragma once
#ifndef _LESSON_MAPPER_
#define _LESSON_MAPPER_

#include "Mapper.h"
#include "domain/do/lesson/LessonDO.h"

class LessonMapper : public Mapper<LessonDO>
{
public:
	LessonDO mapper(sql::ResultSet* res) const override
	{
		LessonDO t;
		t.setId(res->getUInt64("id"));
		t.setCourseId(res->getUInt64("course_id"));
		t.setClassId(res->getUInt64("class_id"));
		t.setRoomId(res->getUInt64("room_id"));
		t.setTeacherId(res->getUInt64("teacher_id"));

		t.setDate(res->getString("date").c_str());
		t.setStartTime(res->getString("start_time").c_str());
		t.setEndTime(res->getString("end_time").c_str());

		t.setState(res->getInt("state"));
		t.setBookable(res->getInt("bookable"));
		return t;
	}
};

#endif // !_LESSON_MAPPER_