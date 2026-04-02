#pragma once
#ifndef _LESSON_DO_H_
#define _LESSON_DO_H_
#include "../../DoInclude.h"

/**
 * 课程数据库实体类
 */
class LessonDO : public BaseDO
{
	// 编号（主键）
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 课节数 第几节课
	MYSQL_SYNTHESIZE(int, sn, Sn);
	// 课程id
	MYSQL_SYNTHESIZE(int64_t, courseId, CourseId);
	// 编排计划id
	MYSQL_SYNTHESIZE(int64_t, scheduleId, ScheduleId);
	// 班级id
	MYSQL_SYNTHESIZE(int64_t, classId, ClassId);
	// 教室id
	MYSQL_SYNTHESIZE(int64_t, roomId, RoomId);
	// 上课日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 开始时间
	MYSQL_SYNTHESIZE(string, startTime, StartTime);
	// 结束时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
	// 创建人
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 修改时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 应扣课次数
	MYSQL_SYNTHESIZE(int, decCount, DecCount);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 授课方式
	MYSQL_SYNTHESIZE(int, teachType, TeachType);
	// 是否开启试听
	MYSQL_SYNTHESIZE(int, onTrial, OnTrial);
	// 试听结果
	MYSQL_SYNTHESIZE(string, trialResult, TrialResult);
	// 课次状态
	MYSQL_SYNTHESIZE(int, state, State);
	// 结课时间
	MYSQL_SYNTHESIZE(string, closeTime, CloseTime);
	// 结课人
	MYSQL_SYNTHESIZE(int64_t, closeOperator, CloseOperator);
	// 主讲人(只用于数据权限)
	MYSQL_SYNTHESIZE(int64_t, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	// 老师所属学校ID
	MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("title", "s", title);	//可为空
		MYSQL_ADD_FIELD("sn", "i", sn);
		MYSQL_ADD_FIELD("course_id", "ll", courseId);//非空
		MYSQL_ADD_FIELD("schedule_id", "ll", scheduleId);
		MYSQL_ADD_FIELD("class_id", "ll", classId);
		MYSQL_ADD_FIELD("room_id", "ll", roomId);
		MYSQL_ADD_FIELD("date", "s", date);      //date占位符为s，time占位符为s
		MYSQL_ADD_FIELD("start_time", "s", startTime);
		MYSQL_ADD_FIELD("end_time", "s", endTime);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("dec_count", "i", decCount);
		MYSQL_ADD_FIELD("remark", "s", remark);	
		MYSQL_ADD_FIELD("teach_type", "i", teachType);
		MYSQL_ADD_FIELD("on_trial", "i", onTrial);
		MYSQL_ADD_FIELD("trial_result", "s", trialResult);	//非空
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("close_time", "s", closeTime);
		MYSQL_ADD_FIELD("close_operator", "ll", closeOperator);
		MYSQL_ADD_FIELD("teacher_id", "ll", teacherId);//非空
		MYSQL_ADD_FIELD("bookable", "i", bookable);//非空
		MYSQL_ADD_FIELD("school_id", "ll", schoolId);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
	}
};

// 给LessonDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonDO> PtrLessonDO;

#endif // !_LESSON_DO_H_
