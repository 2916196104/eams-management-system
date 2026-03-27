#pragma once
#ifndef _APPOINTMENTDO_H_
#define _APPOINTMENTDO_H_

#include "../DoInclude.h"

class AppointmentDO : public BaseDO
{
	// 预约id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 试听课次id, 用于分辨是预约的是哪一天的课
	MYSQL_SYNTHESIZE(string, lessonId, LessonId);
	// 预约学生id
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	// 预约时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 预约课程id
	MYSQL_SYNTHESIZE(string, courseId, CourseId);
	// 学生顾问id
	MYSQL_SYNTHESIZE(string, counselorId, CounselorId);
public:
	AppointmentDO() : BaseDO("appointment")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("lesson_id", "s", lessonId);
		MYSQL_ADD_FIELD("student_id", "s", studentId);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("course_id", "s", courseId);
		MYSQL_ADD_FIELD("counselor", "s", counselorId);

	}
};
typedef std::shared_ptr<AppointmentDO> PtrAppointmentDO;
#endif // !_APPOINTMENTDO_H_