#include "stdafx.h"      
#include "StuJudgeTeaDao.h"
#include "StuJudgeTeaMapper.h"

std::string StuJudgeTeaDao::queryConditionBuilder(const StuJudgeTeaQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->teacherId) {

		sqlCondition << " AND `teacher_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->teacherId.getValue(0));
	}
	if (query->studentId) {

		sqlCondition << " AND `student_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	}
	if (query->lessonId) {

		sqlCondition << " AND `lesson_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->lessonId.getValue(0));
	}
	if (query->anonymity) {

		sqlCondition << " AND `anonymity`=?";
		SQLPARAMS_PUSH(params, "i", bool, query->anonymity.getValue(0));
	}
	if (query->startEvaluateTime) {

		sqlCondition << " AND `add_time`>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startEvaluateTime.getValue(""));
	}
	if (query->endEvaluateTime) {

		sqlCondition << " AND `add_time`<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endEvaluateTime.getValue(""));
	}

    return sqlCondition.str();
}

uint64_t StuJudgeTeaDao::count(const StuJudgeTeaQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM teach_evaluation ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<StuJudgeTeaDO> StuJudgeTeaDao::selectWithPage(const StuJudgeTeaQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,lesson_id,teacher_id,score1,score2,score3,score4,content,add_time,student_id,anonymity,org_id FROM teach_evaluation ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY add_time DESC, `id` DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<StuJudgeTeaDO>(sql, StuJudgeTeaMapper(), params);
}