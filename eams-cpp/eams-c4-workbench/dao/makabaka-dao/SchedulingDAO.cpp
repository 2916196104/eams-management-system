#include"stdafx.h"
#include"SchedulingDAO.h"
#include"SchedulingMapper.h"
#include"domain/do/ConflictIdDO.h"

std::string SchedulingDAO::RepeateSchedulingConditionBuilder(const RepeatedSchedulingDTO::Wrapper& dto, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1 ";
	//课程冲突条件
	sqlCondition << "AND a.class_id = ? ";
	SQLPARAMS_PUSH(params, "s", std::string , dto->classId.getValue(""));
	sqlCondition << "AND a.teacher_ids = ? ";
	SQLPARAMS_PUSH(params, "s", std::string, dto->teacherId.getValue(""));
	if(!dto->assistantId->empty()){
		sqlCondition << "AND a.assistant_ids = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, dto->assistantId.getValue(""));
	}
	sqlCondition << "AND ((a.start_date <= ? AND a.end_date >= ?) OR (a.start_date <= ? AND a.end_date >= ?)) ";
	SQLPARAMS_PUSH(params, "s", std::string, dto->startDate.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->startDate.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->endDate.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->endDate.getValue(""));
	if(!dto->classroomId->empty()){
		sqlCondition << "AND b.room_id = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, dto->classroomId.getValue(""));
	}
	return sqlCondition.str();
}

std::string SchedulingDAO::FreeSchedulingConditionBuilder(const FreeSchedulingDTO::Wrapper& dto, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1 ";
	//课程冲突条件
	sqlCondition << "AND a.class_id = ? ";
	SQLPARAMS_PUSH(params, "s", std::string, dto->classId.getValue(""));
	sqlCondition << "AND a.teacher_ids = ? ";
	SQLPARAMS_PUSH(params, "s", std::string, dto->teacherId.getValue(""));
	if (!dto->assistantId->empty()) {
		sqlCondition << "AND a.assistant_ids = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, dto->assistantId.getValue(""));
	}

	if (!dto->classroomId->empty()) {
		sqlCondition << "AND b.room_id = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, dto->classroomId.getValue(""));
	}
	sqlCondition<< " AND ((b.start_time <= ? AND b.end_time >= ?) OR (b.start_time <= ? AND b.end_time >= ?))";
	SQLPARAMS_PUSH(params, "s", std::string, dto->startTime.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->startTime.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->endTime.getValue(""));
	SQLPARAMS_PUSH(params, "s", std::string, dto->endTime.getValue(""));
	return sqlCondition.str();
}

uint64_t SchedulingDAO::RepeateSchedulingCount(const RepeatedSchedulingDTO::Wrapper& dto) {
	//定义返回结果
	uint64_t count = 0;
	for (auto& period : *dto->periods) {
		std::string weekDaysStr = period->weekDaysToString();
		for (auto& day : weekDaysStr) {
			SqlParams params;
			string sql = "SELECT COUNT(*)\
						FROM lesson_schedule a\
						LEFT JOIN lesson_schedule_setting b\
						ON a.id = b.schedule_id";
			sql += RepeateSchedulingConditionBuilder(dto, params);
			sql += " AND b.weeks = ? AND ((b.start_time <= ? AND b.end_time >= ?) OR (b.start_time <= ? AND b.end_time >= ?))";
			SQLPARAMS_PUSH(params, "s", std::string, std::to_string((int)day-int('0')));
			SQLPARAMS_PUSH(params, "s", std::string, period->startTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->startTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->endTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->endTime.getValue(""));
			count = sqlSession->executeQueryNumerical(sql,params);
			if (count > 0) return count;
		}
	}
	return count;
}

list<std::string> SchedulingDAO::selectRepeatedSchedulingConflictIds(const RepeatedSchedulingDTO::Wrapper& dto) {
	//定义返回结果
	list<std::string> conflictIds;
	for (auto& period : *dto->periods) {
		std::string weekDaysStr = period->weekDaysToString();
		for (auto& day : weekDaysStr) {
			SqlParams params;
			std::string sql = "SELECT a.id\
						FROM lesson_schedule a\
						LEFT JOIN lesson_schedule_setting b\
						ON a.id = b.schedule_id";
			sql += RepeateSchedulingConditionBuilder(dto, params);
			sql += " AND b.weeks = ? AND ((b.start_time <= ? AND b.end_time >= ?) OR (b.start_time <= ? AND b.end_time >= ?))";
			SQLPARAMS_PUSH(params, "s", std::string, std::to_string((int)day-int('0')));
			SQLPARAMS_PUSH(params, "s", std::string, period->startTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->startTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->endTime.getValue(""));
			SQLPARAMS_PUSH(params, "s", std::string, period->endTime.getValue(""));
			auto result = sqlSession->executeQuery<ConflictIdDO>(sql,ConflictIdDOMapper(), params);
			for(auto& item : result){
				conflictIds.push_back(item.getId());
			}
		}
	}
	return conflictIds;
}

uint64_t SchedulingDAO::FreeSchedulingCount(const FreeSchedulingDTO::Wrapper& dto) {
	//定义返回结果
	uint64_t count = 0;
	SqlParams params;
	std::string sql = "SELECT COUNT(*)\
					FROM lesson_schedule a\
					LEFT JOIN lesson_schedule_setting b\
					ON a.id = b.schedule_id";
	sql += FreeSchedulingConditionBuilder(dto, params);
	for (auto& date : *dto->startDate) {
		sql+="AND (a.start_date = ? AND a.end_date = ?) ";
		SQLPARAMS_PUSH(params, "s", std::string, date.getValue(""));
		SQLPARAMS_PUSH(params, "s", std::string, date.getValue(""));
		count = sqlSession->executeQueryNumerical(sql, params);
		if (count > 0) {
			return count;
		}
	}
	return count;
}


list<std::string> SchedulingDAO::selectFreeSchedulingConflictIds(const FreeSchedulingDTO::Wrapper& dto) {
	//定义返回结果
	list<std::string> conflictIds;
	SqlParams params;
	std::string sql="SELECT a.id\
					FROM lesson_schedule a\
					LEFT JOIN lesson_schedule_setting b\
					ON a.id = b.schedule_id";
	sql += FreeSchedulingConditionBuilder(dto, params);
	for (auto& date : *dto->startDate) {
		sql += "AND (a.start_date = ? AND a.end_date = ?) ";
		SQLPARAMS_PUSH(params, "s", std::string, date.getValue(""));
		SQLPARAMS_PUSH(params, "s", std::string, date.getValue(""));
		auto result = sqlSession->executeQuery<ConflictIdDO>(sql, ConflictIdDOMapper(), params);
		for (auto& item : result) {
			conflictIds.push_back(item.getId());
		}
	}
	return conflictIds;
}