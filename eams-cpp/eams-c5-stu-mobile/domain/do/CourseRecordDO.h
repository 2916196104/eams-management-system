#pragma once
#ifndef _COURSE_RECORD_DO_H_
#define _COURSE_RECORD_DO_H_

#include "DoInclude.h"

class CourseRecordDO : public BaseDO
{
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课节标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 第几节课
	MYSQL_SYNTHESIZE(int, sn, Sn);
	MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
	MYSQL_SYNTHESIZE(uint64_t, scheduleId, ScheduleId);
	MYSQL_SYNTHESIZE(uint64_t, classId, ClassId);
	MYSQL_SYNTHESIZE(uint64_t, roomId, RoomId);
	// 上课日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 开始时间
	MYSQL_SYNTHESIZE(string, startTime, StartTime);
	// 结束时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 应扣课次数
	MYSQL_SYNTHESIZE(int, decCount, DecCount);
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
	MYSQL_SYNTHESIZE(uint64_t, closeOperator, CloseOperator);
	// 主讲人ID
	MYSQL_SYNTHESIZE(uint64_t, teacherId, TeacherId);
	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
	// 关联查询字段（来自 course.name，非表字段，不注册 FIELD）
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
public:
	CourseRecordDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "bi", id);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("sn", "i", sn);
		MYSQL_ADD_FIELD("course_id", "bi", courseId);
		MYSQL_ADD_FIELD("schedule_id", "bi", scheduleId);
		MYSQL_ADD_FIELD("class_id", "bi", classId);
		MYSQL_ADD_FIELD("room_id", "bi", roomId);
		MYSQL_ADD_FIELD("date", "dt", date);
		MYSQL_ADD_FIELD("start_time", "s", startTime);
		MYSQL_ADD_FIELD("end_time", "s", endTime);
		MYSQL_ADD_FIELD("creator", "bi", creator);
		MYSQL_ADD_FIELD("editor", "bi", editor);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("dec_count", "i", decCount);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("teach_type", "i", teachType);
		MYSQL_ADD_FIELD("on_trial", "i", onTrial);
		MYSQL_ADD_FIELD("trial_result", "s", trialResult);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("close_time", "dt", closeTime);
		MYSQL_ADD_FIELD("close_operator", "bi", closeOperator);
		MYSQL_ADD_FIELD("teacher_id", "bi", teacherId);
		MYSQL_ADD_FIELD("bookable", "i", bookable);
		MYSQL_ADD_FIELD("school_id", "bi", schoolId);
		MYSQL_ADD_FIELD("org_id", "bi", orgId);
	}
};
typedef std::shared_ptr<CourseRecordDO> PtrCourseRecordDO;

#endif // !_COURSE_RECORD_DO_H_
