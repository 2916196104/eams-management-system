#include "stdafx.h"
#include "StprofileDetailsDAO.h"
#include "StprofileDetailsMapper.h"

inline std::string StprofileDetailsDAO::queryConditionBuilder(const StlistQuery::Wrapper& query, SqlParams& params)
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

std::list<StprofileDetailsViewDO> StprofileDetailsDAO::selectWithPage(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql =R"(
	SELECT
    student.`name`,
    student.`gender`,
    student.`family_rel`,
    student.`birthday`,
    student.`add_time`,
    student.`idcard`,
    student.`credit`,
    student.`stage`,
    student.`grade`,  
	student.`join_date`,
    user.`name` as family_name ,
    course_trial_record.`lesson_count`,
    class_grade.`name` as class_name,
    TIMESTAMPDIFF(HOUR, NOW(), lesson.`close_time`) AS close_time,
    user.`mobile`
	FROM student
	INNER JOIN lesson_student ON student.`id` = lesson_student.`student_id`
	INNER JOIN lesson ON lesson_student.`lesson_id` = lesson.`id`
	INNER JOIN user ON user.`id` = student.`user_id`
	LEFT JOIN course_trial_record ON course_trial_record.`student_id` = student.`id`
	LEFT JOIN class_grade ON class_grade.`id` = student.`grade_id` 
	)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<StprofileDetailsViewDO>(sql, StprofileDetailsViewMapper(), params);
}


uint64_t StprofileDetailsDAO::count(const StlistQuery::Wrapper& query)
{
	SqlParams params;
	string sql = R"(
	SELECT
    COUNT(student.`name`)
	FROM student
	INNER JOIN lesson_student ON student.`id` = lesson_student.`student_id`
	INNER JOIN lesson ON lesson_student.`lesson_id` = lesson.`id`
	INNER JOIN user ON user.`id` = student.`user_id`
	LEFT JOIN course_trial_record ON course_trial_record.`student_id` = student.`id`
	LEFT JOIN class_grade ON class_grade.`id` = student.`grade_id` 
	)";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}