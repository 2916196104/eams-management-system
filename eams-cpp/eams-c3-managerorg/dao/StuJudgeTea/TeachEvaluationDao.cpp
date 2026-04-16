#include "stdafx.h"      
#include "TeachEvaluationDao.h"
#include "TeachEvaluationMapper.h"

std::string StuJudgeTeaDao::queryConditionBuilder(const StuJudgeTeaQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->teacherId) {

		sqlCondition << " AND `teach_evaluation.teacher_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->teacherId.getValue(0));
	}
	if (query->studentId) {

		sqlCondition << " AND `teach_evaluation.student_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->studentId.getValue(0));
	}
	if (query->lessonId) {

		sqlCondition << " AND `teach_evaluation.lesson_id`=?";
		SQLPARAMS_PUSH(params, "ull", uint64_t, query->lessonId.getValue(0));
	}
	if (query->anonymity) {

		sqlCondition << " AND `teach_evaluation.anonymity`=?";
		SQLPARAMS_PUSH(params, "i", int, query->anonymity.getValue(0));
	}
	if (query->startEvaluateTime) {

		sqlCondition << " AND `teach_evaluation.add_time`>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startEvaluateTime.getValue(""));
	}
	if (query->endEvaluateTime) {

		sqlCondition << " AND `teach_evaluation.add_time`<=?";
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

std::list<PtrStuJudgeTeaDO> StuJudgeTeaDao::selectWithPage(const StuJudgeTeaQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT teach_evaluation.id,lesson_id,lesson.title AS lesson_title,teach_evaluation.teacher_id,staff.name AS teacher_name,score1,score2,score3,score4,content,teach_evaluation.add_time,student_id,user.name AS student_name,anonymity,teach_evaluation.org_id,org.name AS org_name FROM teach_evaluation ";
	sql += "INNER JOIN user ON teach_evaluation.student_id = user.id ";
	sql += "INNER JOIN org ON teach_evaluation.org_id = org.id ";
	sql += "INNER JOIN lesson ON teach_evaluation.lesson_id = lesson.id ";
	sql += "INNER JOIN staff ON teach_evaluation.teacher_id = staff.id ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY add_time DESC, `id` DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<PtrStuJudgeTeaDO>(sql, StuJudgeTeaMapper(), params);
}