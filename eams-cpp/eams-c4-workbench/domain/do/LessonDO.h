#pragma once
#ifndef LESSONDO_H
#define LESSONDO_H
#include "../DoInclude.h"

/**
 * lesson表数据库实体类
 */
class LessonDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(int, id, Id);
	// 课程标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 课节数 第几节课
	MYSQL_SYNTHESIZE(int, sn, Sn);
	// 课程id
	MYSQL_SYNTHESIZE(int, courseId, CourseId);
	// 编排计划id
	MYSQL_SYNTHESIZE(int, scheduleId, ScheduleId);
	// 班级id
	MYSQL_SYNTHESIZE(int, classId, ClassId);
	// 教室id
	MYSQL_SYNTHESIZE(int, roomId, RoomId);
	// 上课日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 开始时间
	MYSQL_SYNTHESIZE(string, startTime, StartTime);
	// 结束时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
	// 创建人
	MYSQL_SYNTHESIZE(int, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(int, editor, Editor);
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
	MYSQL_SYNTHESIZE(int, closeOperator, CloseOperator);
	// 主讲人(只用于数据权限)
	MYSQL_SYNTHESIZE(int, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	// 老师所属学校ID
	MYSQL_SYNTHESIZE(int, schoolId, SchoolId);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(int, orgId, OrgId);

public:
	LessonDO() : BaseDO("lesson")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 课程标题
		MYSQL_ADD_FIELD("title", "s", title);
		// 课节数 第几节课
		MYSQL_ADD_FIELD("sn", "i", sn);
		// 课程id
		MYSQL_ADD_FIELD("course_id", "i", courseId);
		// 编排计划id
		MYSQL_ADD_FIELD("schedule_id", "i", scheduleId);
		// 班级id
		MYSQL_ADD_FIELD("class_id", "i", classId);
		// 教室id
		MYSQL_ADD_FIELD("room_id", "i", roomId);
		// 上课日期
		MYSQL_ADD_FIELD("date", "s", date);
		// 开始时间
		MYSQL_ADD_FIELD("start_time", "s", startTime);
		// 结束时间
		MYSQL_ADD_FIELD("end_time", "s", endTime);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 编辑者
		MYSQL_ADD_FIELD("editor", "i", editor);
		// 添加时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 修改时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 应扣课次数
		MYSQL_ADD_FIELD("dec_count", "i", decCount);
		// 备注
		MYSQL_ADD_FIELD("remark", "s", remark);
		// 授课方式
		MYSQL_ADD_FIELD("teach_type", "i", teachType);
		// 是否开启试听
		MYSQL_ADD_FIELD("on_trial", "i", onTrial);
		// 试听结果
		MYSQL_ADD_FIELD("trial_result", "s", trialResult);
		// 课次状态
		MYSQL_ADD_FIELD("state", "i", state);
		// 结课时间
		MYSQL_ADD_FIELD("close_time", "s", closeTime);
		// 结课人
		MYSQL_ADD_FIELD("close_operator", "i", closeOperator);
		// 主讲人(只用于数据权限)
		MYSQL_ADD_FIELD("teacher_id", "i", teacherId);
		// 是否开放预约
		MYSQL_ADD_FIELD("bookable", "i", bookable);
		// 老师所属学校ID
		MYSQL_ADD_FIELD("school_id", "i", schoolId);
		// 创建者所属组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};
typedef std::shared_ptr<LessonDO> PtrLessonDO;

#endif