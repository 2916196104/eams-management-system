#include "stdafx.h"
#include "CourseEvaluateDAO.h"
#include "CourseEvaluateMapper.h"

std::string CourseEvaluateDAO::queryConditionBuilder(const CourseEvaluateQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE deleted=0";
	if (query->student_id)
	{
		sqlCondition << " AND student_id=?";
		SQLPARAMS_PUSH(params, "bi", uint64_t, query->student_id.getValue(0));
	}
	if (query->course_id)
	{
		sqlCondition << " AND course_id=?";
		SQLPARAMS_PUSH(params, "bi", uint64_t, query->course_id.getValue(0));
	}
	return sqlCondition.str();
}

uint64_t CourseEvaluateDAO::count(const CourseEvaluateQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM course_comment";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CourseEvaluateDO> CourseEvaluateDAO::selectWithPage(const CourseEvaluateQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT * FROM course_comment";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC";
	sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<CourseEvaluateDO>(sql, CourseEvaluateMapper(), params);
}

uint64_t CourseEvaluateDAO::insert(const CourseEvaluateDO& obj)
{
	return insertAutoPk(obj);
}
