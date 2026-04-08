#include"stdafx.h"
#include "SchedulingService.h"
#include"id/SnowFlake.h"
#include"id/UuidFacade.h"
#include"domain/do/LessonScheduleDO.h"
#include"domain/do/LessonScheduleSettingDO.h"
#include"dao/makabaka-dao/SchedulingDAO.h"
#include"BaseDAO.h"
#include"SimpleDateTimeFormat.h"
#include"domain/do/CourseDO.h"


//将id列表转换为逗号分隔的字符串
static std::string joinIds(const std::list<std::string>& ids) {
	std::stringstream ss;
	bool first = true;
	for (const auto& id : ids) {
		if (!first) {
			ss << ",";
		}
		ss << id;
		first = false;
	}
	return ss.str();
}

std::string SchedulingService::addRepeatScheduling(const RepeatedSchedulingDTO::Wrapper& dto, const PayloadDTO& payload) {
	
	SchedulingDAO schedulingDAO;
	//定义返回值
	std::string result= "";
	//组装lesson_schedule表的DO对象
	LessonScheduleDO lessonScheduleDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleDO, dto, ClassId, classId, CourseId, courseId, TeacherIds, teacherId, AssistantIds, assistantId, StartDate, startDate, \
		EndDate, endDate, ExcludeHoliday, skipHoliday);
	//生成唯一id
	SnowFlake uf(1, 1);
	std::string ScheduleId = std::to_string(uf.nextId());
	lessonScheduleDO.setId(ScheduleId);
	//设置创建人
	//lessonScheduleDO.setCreator(dto->getPayload()->getUsername());
	//设置创建时间
	lessonScheduleDO.setAddTime(SimpleDateTimeFormat::format());
	//添加编辑时间
	lessonScheduleDO.setEditTime(SimpleDateTimeFormat::format());

	//冲突检查
	uint64_t conflictCount = schedulingDAO.RepeateSchedulingCount(dto);
	if(dto->checkConflict&&conflictCount>0) {
		result = "add RepeatScheduling fail, conflict with other scheduling.";
		return result;
	}
	else {
		//不检查冲突但设置了冲突检查字段，说明用户强制添加排课计划，记录日志
		//设置冲突id列表
		std::list<std::string> conflictIds = schedulingDAO.selectRepeatedSchedulingConflictIds(dto);
		lessonScheduleDO.setConflictIds(joinIds(conflictIds));
	}

	//插入数据库
	if(schedulingDAO.insert(lessonScheduleDO) <= 0) {
		result = "add RepeatScheduling fail.";
		return result;
	}

	//组装LessonScheduleSettingDO表的DO对象
	LessonScheduleSettingDO lessonScheduleSettingDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleSettingDO,dto,Room_id,classroomId);
	//设置排课计划id
	lessonScheduleSettingDO.setSchedule_id(ScheduleId);
	for(auto& period : *dto->periods) {
		std::string weeks = period->weekDaysToString();
		for (char day : weeks) {
			//生成唯一id
			lessonScheduleSettingDO.setId(std::to_string(uf.nextId()));
			//设置周几
			lessonScheduleSettingDO.setWeeks(std::string()+day);
			//设置上课时间
			lessonScheduleSettingDO.setStart_time(period->startTime);
			//设置下课时间
			lessonScheduleSettingDO.setEnd_time(period->endTime);
			//插入数据库
			if (schedulingDAO.insert(lessonScheduleSettingDO) <= 0) {
				result = "add RepeatScheduling fail.";
				break;
			}
		}
	}

	//组装course表的DO对象
	CourseDO courseDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(courseDO,dto,Id,courseId,Storage,limitNum,Bookable,enableBooking);
	BaseDAO dao;
	if (dao.update(courseDO) <= 0) {
		result = "add RepeatScheduling fail";
		return result;
	}
	
	return result;
}

std::string SchedulingService::addFreeScheduling(const FreeSchedulingDTO::Wrapper& dto, const PayloadDTO& payload) {
	SchedulingDAO schedulingDAO;
	//定义返回值
	std::string result = "";
	//组装lesson_schedule表的DO对象
	LessonScheduleDO lessonScheduleDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleDO, dto, ClassId, classId, CourseId, courseId,\
		TeacherIds, teacherId, AssistantIds, assistantId);
	//生成唯一id
	SnowFlake uf(1, 1);
	std::string ScheduleId = std::to_string(uf.nextId());
	lessonScheduleDO.setId(ScheduleId);
	//设置创建人
	//lessonScheduleDO.setCreator(dto->getPayload()->getUsername());
	//创建时间
	lessonScheduleDO.setAddTime(SimpleDateTimeFormat::format());
	//添加编辑时间
	lessonScheduleDO.setEditTime(SimpleDateTimeFormat::format());
	//冲突检测
	uint64_t conflictCount = schedulingDAO.FreeSchedulingCount(dto);
	if (dto->checkConflict&&conflictCount>0) {
		result = "add RepeatScheduling fail, conflict with other scheduling.";
		return result;
	}
	else {
		//不检查冲突但设置了冲突检查字段，说明用户强制添加排课计划，记录日志
		//设置冲突id列表
		std::list<std::string> conflictIds = schedulingDAO.selectFreeSchedulingConflictIds(dto);
		lessonScheduleDO.setConflictIds(joinIds(conflictIds));
	}
	//插入数据库
	for (auto& date:*dto->startDate) {
		lessonScheduleDO.setStartDate(date);
		lessonScheduleDO.setEndDate(date);
		if (schedulingDAO.insert(lessonScheduleDO) <= 0) {
			result = "add RepeatScheduling fail";
			return result;
		}
	}

	//组装LessonScheduleSettingDO表的DO对象
	LessonScheduleSettingDO lessonScheduleSettingDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleSettingDO, dto, Room_id, classroomId,Start_time,startTime,End_time,endTime);
	//设置排课id
	lessonScheduleSettingDO.setSchedule_id(ScheduleId);
	//设置唯一id
	lessonScheduleSettingDO.setId(std::to_string(uf.nextId()));
	//插入数据库
	for(auto& day:*dto->weeks){
		lessonScheduleSettingDO.setWeeks(std::string() + day);
		if (schedulingDAO.insert(lessonScheduleSettingDO) <= 0) {
			result = "add RepeatScheduling fail";
			return result;
		}
	}

	//组装course表的DO对象
	CourseDO courseDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(courseDO, dto, Id, courseId, Storage, limitNum, Bookable, enableBooking);
	BaseDAO dao;
	if (dao.update(courseDO) <= 0) {
		result = "add RepeatScheduling fail";
		return result;
	}
	return result;
}