#pragma once
#ifndef _LessonSchedule_DO_
#define _LessonSchedule_DO_
#include "../DoInclude.h"

/**
 * 根据数据库表生成的实体类
 */
class LessonScheduleDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 班级编号
	MYSQL_SYNTHESIZE(string, classId, ClassId);
	// 课程编号
	MYSQL_SYNTHESIZE(string, courseId, CourseId);
	// 任课教师
	MYSQL_SYNTHESIZE(string, teacherIds, TeacherIds);
	// 助教
	MYSQL_SYNTHESIZE(string, assistantIds, AssistantIds);
	// 开始日期
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	// 结束日期
	MYSQL_SYNTHESIZE(string, endDate, EndDate);
	// 课次
	MYSQL_SYNTHESIZE(int, decLessonCount, DecLessonCount);
	// 上课时间
	MYSQL_SYNTHESIZE(string, times, Times);
	// 是否排除节假日
	MYSQL_SYNTHESIZE(int, excludeHoliday, ExcludeHoliday);
	// 是否生成课表
	MYSQL_SYNTHESIZE(int, state, State);
	// 创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(string, editor, Editor);
	// 创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 冲突 id 列表
	MYSQL_SYNTHESIZE(string, conflictIds, ConflictIds);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(string, orgId, OrgId);
public:
	LessonScheduleDO() : BaseDO("LessonScheduleDO")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("class_id", "s", classId);
		MYSQL_ADD_FIELD("course_id", "s", courseId);
		MYSQL_ADD_FIELD("teacher_ids", "s", teacherIds);
		MYSQL_ADD_FIELD("assistant_ids", "s", assistantIds);
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		MYSQL_ADD_FIELD("end_date", "s", endDate);
		MYSQL_ADD_FIELD("dec_lesson_count", "i", decLessonCount);
		MYSQL_ADD_FIELD("times", "s", times);
		MYSQL_ADD_FIELD("exclude_holiday", "i", excludeHoliday);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("conflict_ids", "s", conflictIds);
		MYSQL_ADD_FIELD("org_id", "s", orgId);
		
	}
};

// 给 LessonScheduleDO 智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonScheduleDO> LessonScheduleDO;
#endif // !_LessonSchedule_DO_