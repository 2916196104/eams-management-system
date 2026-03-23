#pragma once
#pragma once
#ifndef _Timetable_DO_
#define _Timetable_DO_

#include "../DoInclude.h"

/**
 * 课表主表数据实体
 * 对应表：lesson
 */
class LessonDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课程标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 第几节课
	MYSQL_SYNTHESIZE(int, sn, Sn);
	// 班级ID
	MYSQL_SYNTHESIZE(string, classId, ClassId);
	// 教室ID
	MYSQL_SYNTHESIZE(string, roomId, RoomId);
	// 上课日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 开始时间
	MYSQL_SYNTHESIZE(string, startTime, StartTime);
	// 结束时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 课次状态
	MYSQL_SYNTHESIZE(int, state, State);
	// 主讲老师ID
	MYSQL_SYNTHESIZE(string, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);

public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("sn", "i", sn);
		MYSQL_ADD_FIELD("class_id", "s", classId);
		MYSQL_ADD_FIELD("room_id", "s", roomId);
		MYSQL_ADD_FIELD("date", "s", date);
		MYSQL_ADD_FIELD("start_time", "s", startTime);
		MYSQL_ADD_FIELD("end_time", "s", endTime);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("teacher_id", "s", teacherId);
		MYSQL_ADD_FIELD("bookable", "i", bookable);
	}
};

// 智能指针别名
typedef std::shared_ptr<LessonDO> PtrLessonDO;

/**
 * 学员课次签到实体类
 * 对应表：lesson_student
 */
class LessonStudentDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课次ID
	MYSQL_SYNTHESIZE(string, lessonId, LessonId);
	// 学员ID
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	// 签到时间
	MYSQL_SYNTHESIZE(string, signTime, SignTime);
	// 签到方式
	MYSQL_SYNTHESIZE(int, signType, SignType);
	// 签到状态
	MYSQL_SYNTHESIZE(int, signState, SignState);
	// 教师ID
	MYSQL_SYNTHESIZE(string, teacherId, TeacherId);

public:
	LessonStudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("lesson_id", "s", lessonId);
		MYSQL_ADD_FIELD("student_id", "s", studentId);
		MYSQL_ADD_FIELD("sign_time", "s", signTime);
		MYSQL_ADD_FIELD("sign_type", "i", signType);
		MYSQL_ADD_FIELD("sign_state", "i", signState);
		MYSQL_ADD_FIELD("teacher_id", "s", teacherId);
	}
};

typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

#endif // !_Timetable_DO_
