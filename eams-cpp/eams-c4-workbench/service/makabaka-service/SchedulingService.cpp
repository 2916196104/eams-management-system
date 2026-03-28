#include"stdafx.h"
#include "SchedulingService.h"
#include"id/SnowFlake.h"
#include"domain/do/LessonScheduleDO.h"
#include"BaseDAO.h"
#include"SimpleDateTimeFormat.h"

bool SchedulingService::addRepeatScheduling(const RepeatedSchedulingDTO::Wrapper& dto, const PayloadDTO& payload) {
	//执行标志
	bool success = true;
	//组装lesson_schedule表的DO对象
	LessonScheduleDO lessonScheduleDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleDO, dto, ClassId, classId, CourseId, courseId, TeacherIds, teacherId, AssistantIds, assistantId, StartDate, startDate, \
		EndDate, endDate, ExcludeHoliday, skipHoliday, ConflictIds, checkConflict);
	//生成唯一id
	SnowFlake uf(1, 1);
	lessonScheduleDO.setId(std::to_string(uf.nextId()));
	//设置创建人
	//lessonScheduleDO.setCreator(dto->getPayload()->getUsername());
	//设置创建时间
	lessonScheduleDO.setAddTime(SimpleDateTimeFormat::format());
	//插入数据库
	BaseDAO dao;
	if(dao.insert(lessonScheduleDO) <= 0) {
		success = false;
	}
	return success;
}

bool SchedulingService::addFreeScheduling(const FreeSchedulingDTO::Wrapper& dto, const PayloadDTO& payload) {
	//构建返回值
	bool success = true;
	//组装lesson_schedule表的DO对象
	LessonScheduleDO lessonScheduleDO;
	ZO_STAR_DOMAIN_DTO_TO_DO(lessonScheduleDO, dto, ClassId, classId, CourseId, courseId, TeacherIds, teacherId, AssistantIds, assistantId, StartDate, startDate, \
		 ConflictIds, checkConflict,EndDate,startDate);
	//生成唯一id
	SnowFlake uf(1, 1);
	lessonScheduleDO.setId(std::to_string(uf.nextId()));
	//设置创建人
	//lessonScheduleDO.setCreator(dto->getPayload()->getUsername());
	lessonScheduleDO.setAddTime(SimpleDateTimeFormat::format());
	//插入数据库
	BaseDAO dao;
	if(dao.insert(lessonScheduleDO) <= 0) {
		success = false;
	}
	return success;
}