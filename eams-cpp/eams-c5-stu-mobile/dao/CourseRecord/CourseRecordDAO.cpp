#include "stdafx.h"
#include "CourseRecordDAO.h"
#include "CourseRecordMapper.h"

std::string CourseRecordDAO::queryConditionBuilder(const CourseRecordQuery::Wrapper& query, SqlParams& params)
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

uint64_t CourseRecordDAO::count(const CourseRecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM lesson";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CourseRecordDO> CourseRecordDAO::selectWithPage(const CourseRecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT * FROM lesson";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY `date` DESC, `start_time` ASC";
	sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<CourseRecordDO>(sql, CourseRecordMapper(), params);
}
