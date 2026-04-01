#include "stdafx.h"
#include "StclassRecordDAO.h"
#include "StclassRecordMapper.h"

inline std::string StclassRecordDAO::queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params)
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

std::list<StclassRecordViewDO> StclassRecordDAO::selectWithPage(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
    lesson.`start_time`,
    lesson.`end_time`,
    lesson.`title`,
    lesson.`state`,
    lesson_student.`sign_type`
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
	return sqlSession->executeQuery<StclassRecordViewDO>(sql, StclassRecordViewMapper(), params);
}


uint64_t StclassRecordDAO::count(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
    COUNT(lesson.`title`)
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