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
	MYSQL_SYNTHESIZE(int, state, State);
	// 主讲老师ID
	MYSQL_SYNTHESIZE(string, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	// 课程ID，外键，关联课程表course的id字段
	MYSQL_SYNTHESIZE(string, courseId, CourseId);

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
		MYSQL_ADD_FIELD_NULLABLE("state", "i", state, true);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "s", teacherId, true);
		MYSQL_ADD_FIELD_NULLABLE("bookable", "i", bookable, true);
		MYSQL_ADD_FIELD_NULLABLE("course_id", "s", courseId, true);
	}
};
// 智能指针别名
typedef std::shared_ptr<LessonDO> PtrLessonDO;

/**
* 统一课程卡片查询结果
* DAO 查询时直接查成“页面展示对象”
*/
class TimetableCourseViewDO : public LessonDO
{
	MYSQL_SYNTHESIZE(string, teacherName, TeacherName);
	MYSQL_SYNTHESIZE(string, classroomName, ClassroomName);
	MYSQL_SYNTHESIZE(string, className, ClassName);

	// 页面状态
	MYSQL_SYNTHESIZE(int, lessonState, LessonState);
	MYSQL_SYNTHESIZE(string, lessonStateText, LessonStateText);

	// 0未签到 1已签到 2补签 3请假 4旷课
	MYSQL_SYNTHESIZE(int, signState, SignState);
	MYSQL_SYNTHESIZE(string, signStateText, SignStateText);

	// 控制按钮
	MYSQL_SYNTHESIZE(int, canSign, CanSign);
	MYSQL_SYNTHESIZE(int, canLeave, CanLeave);
	MYSQL_SYNTHESIZE(int, canReserve, CanReserve);

	// lesson/reservable
	MYSQL_SYNTHESIZE(string, cardType, CardType);

	// sign/leave/reserve/none
	MYSQL_SYNTHESIZE(string, actionType, ActionType);
	MYSQL_SYNTHESIZE(string, actionText, ActionText);
};
typedef std::shared_ptr<TimetableCourseViewDO> PtrTimetableCourseViewDO;

/**
 * 月历计数查询结果
 * count 只统计课表分组展示数量
 */
class TimetableCalendarCountDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, date, Date);
	MYSQL_SYNTHESIZE(int, count, Count);

public:
	TimetableCalendarCountDO() : BaseDO("")
	{
	}
};
typedef std::shared_ptr<TimetableCalendarCountDO> PtrTimetableCalendarCountDO;

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
	MYSQL_SYNTHESIZE(int, signState, SignState);
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
		MYSQL_ADD_FIELD_NULLABLE("sign_state", "i", signState, true);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "s", teacherId, true);
	}
};

typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

/**
 * 预约记录实体类
 * 对应表：appointment
 */
class AppointmentDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 预约课次ID
	MYSQL_SYNTHESIZE(string, lessonId, LessonId);
	// 学员ID
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	// 预约时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 审核状态：1待审核 2审核通过 -1已驳回
	MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
	// 审核时间
	MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime);
	// 审核人
	MYSQL_SYNTHESIZE(string, verifyStaff, VerifyStaff);
	// 审核备注
	MYSQL_SYNTHESIZE(string, verifyRemark, VerifyRemark);
	// 所属课程ID
	MYSQL_SYNTHESIZE(string, courseId, CourseId);
	// 学员所属学校ID
	MYSQL_SYNTHESIZE(string, schoolId, SchoolId);
	// 学员所属顾问ID
	MYSQL_SYNTHESIZE(string, counselor, Counselor);

public:
	AppointmentDO() : BaseDO("appointment")
	{
		// 映射主键字段
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 映射预约课次ID
		MYSQL_ADD_FIELD("lesson_id", "s", lessonId);
		// 映射学员ID
		MYSQL_ADD_FIELD("student_id", "s", studentId);
		// 映射预约时间
		MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, true);
		// 映射备注
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
		// 映射审核状态
		MYSQL_ADD_FIELD_NULLABLE("verify_state", "i", verifyState, true);
		// 映射审核时间
		MYSQL_ADD_FIELD_NULLABLE("verify_time", "s", verifyTime, true);
		// 映射审核人
		MYSQL_ADD_FIELD_NULLABLE("verify_staff", "s", verifyStaff, true);
		// 映射审核备注
		MYSQL_ADD_FIELD_NULLABLE("verify_remark", "s", verifyRemark, true);
		// 映射所属课程ID
		MYSQL_ADD_FIELD_NULLABLE("course_id", "s", courseId, true);
		// 映射学员所属学校ID
		MYSQL_ADD_FIELD_NULLABLE("school_id", "s", schoolId, true);
		// 映射学员所属顾问ID
		MYSQL_ADD_FIELD_NULLABLE("counselor", "s", counselor, true);
	}
};
// AppointmentDO 智能指针别名
typedef std::shared_ptr<AppointmentDO> PtrAppointmentDO;

#endif // !_TIMETABLE_DO_
