



#include "stdafx.h"
#include "EnrollCourseDAO.h"
#include "EnrollCourseMapper.h"

std::string EnrollCourseDAO::queryConditionBuilder(const EnrollCourseQuery::Wrapper& query, SqlParams& params)
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

uint64_t EnrollCourseDAO::count(const EnrollCourseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM student_course ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<EnrollCourseDO> EnrollCourseDAO::selectWithPage(const EnrollCourseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT sc.*, c.name AS course_name, s.name AS subject_name FROM student_course sc LEFT JOIN course c ON sc.course_id = c.id LEFT JOIN subject s ON sc.subject_id = s.id ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY IFNULL(sc.edit_time, sc.add_time) DESC, sc.id DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<EnrollCourseDO>(sql, EnrollCourseMapper(), params);
}
