#pragma once
#include "Mapper.h"
#include "domain/do/lesson/LessonExtDO.h"

class LessonExtMapper : public Mapper<LessonExtDO>
{
public:
	LessonExtDO mapper(sql::ResultSet* res) const override
	{
		LessonExtDO t;
		// 提取基础字段
		t.setId(res->getUInt64("id"));
		t.setDate(res->getString("date").c_str());
		t.setStartTime(res->getString("start_time").c_str());
		t.setEndTime(res->getString("end_time").c_str());
		t.setState(res->getInt("state"));
		t.setBookable(res->getInt("bookable"));

		// 提取 JOIN 出来的扩展字段
		t.setCourseName(res->getString("course_name").c_str());
		t.setClassName(res->getString("class_name").c_str());
		t.setTeacherName(res->getString("teacher_name").c_str());
		t.setClassroomName(res->getString("classroom_name").c_str());

		// 如果没查到签到记录，数据库可能返回 NULL，这里需要判空
		if (!res->isNull("sign_state")) {
			t.setSignState(res->getInt("sign_state"));
		}
		else {
			t.setSignState(0); // 默认未签到
		}

		return t;
	}
};