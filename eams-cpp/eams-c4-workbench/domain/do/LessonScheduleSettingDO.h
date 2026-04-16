#pragma once
#ifndef _LessonScheduleSetting_DO_
#define _LessonScheduleSetting_DO_
#include "DoInclude.h"

/**
 * 示例数据库实体类
 */
class LessonScheduleSettingDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(string, id, Id);
	//编排计划id
	MYSQL_SYNTHESIZE(string, schedule_id, Schedule_id);
	//星期
	MYSQL_SYNTHESIZE(string, weeks, Weeks);
	//开始时间
	MYSQL_SYNTHESIZE(string, start_time, Start_time);
	//结束时间
	MYSQL_SYNTHESIZE(string, end_time, End_time);
	//教室ID
	MYSQL_SYNTHESIZE(string, room_id, Room_id);
public:
	LessonScheduleSettingDO() : BaseDO("lesson_schedule_setting")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("schedule_id", "s", schedule_id);
		MYSQL_ADD_FIELD("weeks", "s", weeks);
		MYSQL_ADD_FIELD("start_time", "s", start_time);
		MYSQL_ADD_FIELD("end_time", "s", end_time);
		MYSQL_ADD_FIELD("room_id", "s", room_id);
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonScheduleSettingDO> PtrLessonScheduleSettingDO;
#endif // !_LessonScheduleSetting_DO_
