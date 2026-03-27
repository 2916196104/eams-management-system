#include "stdafx.h"
#include "StlistDAO.h"
#include "StlistMapper.h"

inline std::string StlistDAO::queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND student.`name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->mobile)
	{
		sqlCondition << " AND user.`mobile`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->mobile.getValue(""));
	}
	return sqlCondition.str();
}

std::list<StlistViewDO> StlistDAO::selectWithPage(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
    student.`name`,
    student.`gender`,
    TIMESTAMPDIFF(HOUR, NOW(), lesson.`close_time`) AS close_time,
    user.`mobile`
	FROM student
	INNER JOIN lesson_student ON student.`id`= lesson_student.`student_id`
	INNER JOIN lesson ON lesson_student.`lesson_id` = lesson.`id`
	INNER JOIN user ON user.`id` = student.`user_id`
		)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<StlistViewDO>(sql, StlistViewMapper(), params);
}

uint64_t StlistDAO::count(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
    COUNT(student.`name`)
	FROM student
	INNER JOIN lesson_student ON student.`id`= lesson_student.`student_id`
	INNER JOIN lesson ON lesson_student.`lesson_id` = lesson.`id`
	INNER JOIN user ON user.`id` = student.`user_id`
	)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}
