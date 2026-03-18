#pragma once

#ifndef _SCHEDULE_VO_H_
#define _SCHEDULE_VO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 单节课表视图对象
 */
class ScheduleVO : public oatpp::DTO
{
	DTO_INIT(ScheduleVO, DTO);

	// 核心主键
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("schedule.field.id"));

	// --- 时间与状态 ---
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("schedule.field.startTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("schedule.field.endTime"));
	API_DTO_FIELD_DEFAULT(String, courseStatusText, ZH_WORDS_GETTER("schedule.field.courseStatusText"));

	// --- 课程信息 ---
	API_DTO_FIELD_DEFAULT(Int32, scheduleType, ZH_WORDS_GETTER("schedule.field.scheduleType"));
	API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("schedule.field.className"));
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("schedule.field.courseName"));

	// --- 人员与场地 ---
	API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("schedule.field.teacherName"));
	API_DTO_FIELD_DEFAULT(String, classroomName, ZH_WORDS_GETTER("schedule.field.classroomName"));

	// --- 签到状态 ---
	API_DTO_FIELD_DEFAULT(String, signInStatusText, ZH_WORDS_GETTER("schedule.field.signInStatusText"));

	// --- 动态按钮控制 ---
	API_DTO_FIELD_DEFAULT(Boolean, canSignIn, ZH_WORDS_GETTER("schedule.field.canSignIn"));
	API_DTO_FIELD_DEFAULT(Boolean, canLeave, ZH_WORDS_GETTER("schedule.field.canLeave"));
	API_DTO_FIELD_DEFAULT(Boolean, canReserve, ZH_WORDS_GETTER("schedule.field.canReserve"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SCHEDULE_VO_H_