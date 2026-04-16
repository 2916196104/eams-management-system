#pragma once
#ifndef _TIMETABLE_SERVICE_
#define _TIMETABLE_SERVICE_

#include "domain/vo/timetable/TimetableVO.h"
#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include "../../domain/do/timetable/TimetableDO.h"

/**
 * 家长端课表服务
 */
class TimetableService
{
private:	
	//将课程视图DO转换为课程卡片DTO
	oatpp::Object<TimetableCourseItemDTO> buildCourseItemDTO(const TimetableCourseViewDO& data);
	
	//构建课表分组DTO
	oatpp::Object<TimetableSectionDTO> buildLessonSectionDTO(
		const oatpp::String& queryDate,
		const std::list<TimetableCourseViewDO>& datas);
	
	//构建预约分组DTO
	oatpp::Object<TimetableSectionDTO> buildReserveSectionDTO(
		const oatpp::String& queryDate,
		const std::list<TimetableCourseViewDO>& datas);
	
    //构建通用动作响应DTO
	oatpp::Object<TimetableActionResultDTO> buildActionResult(
		bool success,
		const oatpp::String& lessonId,
		const oatpp::String& actionType,
		const oatpp::String& message);

	// 构建签到专用响应DTO
	oatpp::Object<TimetableSignResultDTO> buildSignResult(
		bool success,
		const oatpp::String& lessonId,
		v_int32 signType,
		v_int32 signState,
		const oatpp::String& signStateText,
		const oatpp::String& signTime,
		const oatpp::String& message);

public:
	
	//按天查询课表	
	TimetableVO::Wrapper getDayTimetable(const TimetableDayQuery::Wrapper& query);
	
	//按月查询月历统计
	TimetableMonthVO::Wrapper getMonthTimetable(const TimetableMonthQuery::Wrapper& query);
	
	//提交预约
	ReserveVO::Wrapper reserveLesson(const ReserveDTO::Wrapper& dto);
	
	//学员签到
	TimetableSignVO::Wrapper signLesson(const TimetableSignDTO::Wrapper& dto);
	
	//学员请假
	LeaveVO::Wrapper leaveLesson(const LeaveDTO::Wrapper& dto);
};

#endif // !_TIMETABLE_SERVICE_
