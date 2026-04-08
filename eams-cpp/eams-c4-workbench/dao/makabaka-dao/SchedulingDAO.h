#pragma once
#ifndef _SCHEDULINGDAO_H_
#define _SCHEDULINGDAO_H_
#include"BaseDAO.h"
#include"../../domain/do/LessonScheduleDO.h"
#include"../../domain/do/LessonScheduleSettingDO.h"
#include"../../domain/dto/makabaka-dto/RepeatedSchedulingDTO.h"
#include"../../domain/dto/makabaka-dto/FreeSchedulingDTO.h"

class SchedulingDAO : public BaseDAO {
private:
	inline std::string RepeateSchedulingConditionBuilder(const RepeatedSchedulingDTO::Wrapper& dto, SqlParams& params);
	inline std::string FreeSchedulingConditionBuilder(const FreeSchedulingDTO::Wrapper& dto, SqlParams& params);
public:
	//获取重复排课课程冲突数据条数
	uint64_t RepeateSchedulingCount(const RepeatedSchedulingDTO::Wrapper& dto);
	//获取自由排课课程冲突数据条数
	uint64_t FreeSchedulingCount(const FreeSchedulingDTO::Wrapper& dto);
	//获取重复排课课程冲突数据的id列表
	list<std::string> selectRepeatedSchedulingConflictIds(const RepeatedSchedulingDTO::Wrapper& dto);
	//获取自由排课课程冲突数据的id列表
	list<std::string> selectFreeSchedulingConflictIds(const FreeSchedulingDTO::Wrapper& dto);
};

#endif //!_SCHEDULINGDAO_H_