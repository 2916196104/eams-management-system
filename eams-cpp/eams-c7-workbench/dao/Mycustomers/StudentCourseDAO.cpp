#include "stdafx.h"
#include "StudentCourseDAO.h"
#include "StudentCourseMapper.h"

std::string StudentCourseDAO::queryConditionBuilder(const StudentCourseQuery::Wrapper& query, SqlParams& params)
{
    stringstream sql;
    sql << " WHERE deleted = 0 ";

    if (query->student_id) {
        sql << " AND student_id = ? ";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(0));
    }
    return sql.str();
}

uint64_t StudentCourseDAO::count(const StudentCourseQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM student_course ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<StudentCourseDO> StudentCourseDAO::selectPage(const StudentCourseQuery::Wrapper& query)
{
    SqlParams params;
    string sql = R"(
        SELECT 
            sc.*,
            c.name AS course_name
        FROM student_course sc
        LEFT JOIN course c ON sc.course_id = c.id
        WHERE sc.deleted = 0
    )";

    if (query->student_id) {
        sql += " AND sc.student_id = ? ";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(0));
    }

    sql += " ORDER BY sc.add_time DESC ";

    int page = query->pageIndex.getValue(1);
    int size = query->pageSize.getValue(10);
    sql += " LIMIT " + to_string((page - 1) * size) + "," + to_string(size);

    return sqlSession->executeQuery<StudentCourseDO>(sql, StudentCourseMapper(), params);
}

std::list<StudentCourseDO> StudentCourseDAO::selectByStudentId(uint64_t id)
{
    string sql = R"(
    SELECT sc.*, c.name AS course_name 
    FROM student_course sc
    LEFT JOIN course c ON sc.course_id = c.id
    WHERE sc.student_id = ? AND sc.deleted = 0
    )";
    return sqlSession->executeQuery<StudentCourseDO>(sql, StudentCourseMapper(), "ll", id);
}