#pragma once
#ifndef _TIMETABLE_DO_
#define _TIMETABLE_DO_

#include "../DoInclude.h"

/**
 * 课表主表数据实体
 * 对应表：lesson
 */
class LessonDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课程名称
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
	MYSQL_SYNTHESIZE(string, state, State);
	// 主讲老师ID
	MYSQL_SYNTHESIZE(string, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);

public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD_NULLABLE("sn", "i", sn, true);
		MYSQL_ADD_FIELD_NULLABLE("class_id", "s", classId, true);
		MYSQL_ADD_FIELD_NULLABLE("room_id", "s", roomId, true);
		MYSQL_ADD_FIELD_NULLABLE("date", "s", date, true);
		MYSQL_ADD_FIELD_NULLABLE("start_time", "s", startTime, true);
		MYSQL_ADD_FIELD_NULLABLE("end_time", "s", endTime, true);
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
		MYSQL_ADD_FIELD_NULLABLE("state", "s", state, true);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "s", teacherId, true);
		MYSQL_ADD_FIELD_NULLABLE("bookable", "i", bookable, true);
	}
};

// 智能指针别名
typedef std::shared_ptr<LessonDO> PtrLessonDO;

/**
 * 课表视图对象
 * 补联表查询得到的课表信息，包含了老师姓名、教室名称、班级名称字段
 */
class LessonViewDO : public LessonDO
{
	// 老师姓名
	MYSQL_SYNTHESIZE(string, teacherName, TeacherName);
	// 教室名称
	MYSQL_SYNTHESIZE(string, classroomName, ClassroomName);
	// 班级名称
	MYSQL_SYNTHESIZE(string, className, ClassName);
	// 当前学生签到状态
	MYSQL_SYNTHESIZE(int, signState, SignState);
};

// 智能指针别名
typedef std::shared_ptr<LessonViewDO> PtrLessonViewDO;

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
	// 班级ID
	MYSQL_SYNTHESIZE(string, classId, ClassId);
	// 学员ID
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	// 签到时间
	MYSQL_SYNTHESIZE(string, signTime, SignTime);
	// 签到方式
	MYSQL_SYNTHESIZE(int, signType, SignType);
	// 签到状态
	MYSQL_SYNTHESIZE(string, signState, SignState);
	// 点名教师ID
	MYSQL_SYNTHESIZE(string, teacherId, TeacherId);

public:
	LessonStudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("lesson_id", "s", lessonId);
		MYSQL_ADD_FIELD_NULLABLE("class_id", "s", classId, true);
		MYSQL_ADD_FIELD("student_id", "s", studentId);
		MYSQL_ADD_FIELD_NULLABLE("sign_time", "s", signTime, true);
		MYSQL_ADD_FIELD_NULLABLE("sign_type", "i", signType, true);
		MYSQL_ADD_FIELD_NULLABLE("sign_state", "s", signState, true);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "s", teacherId, true);
	}
};

typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

#endif // !_TIMETABLE_DO_
