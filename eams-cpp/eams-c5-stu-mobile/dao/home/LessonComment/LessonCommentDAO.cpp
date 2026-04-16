

#include "stdafx.h"
#include "LessonCommentDAO.h"
#include "LessonCommentMapper.h"

std::string LessonCommentDAO::queryConditionBuilder(const LessonCommentQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->student_id)
	{
		sqlCondition << " AND student_id =?";
		SQLPARAMS_PUSH(params, "i", int, query->student_id.getValue(0));
	}
	return sqlCondition.str();
}


uint64_t LessonCommentDAO::count(const LessonCommentQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM lesson_student ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<LessonCommentDO> LessonCommentDAO::selectWithPage(const LessonCommentQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT ls.*, s.name AS teacher_name FROM lesson_student ls LEFT JOIN staff s ON ls.evaluate_teacher = s.id";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY `add_time` DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<LessonCommentDO>(sql, LessonCommentMapper(), params);
}