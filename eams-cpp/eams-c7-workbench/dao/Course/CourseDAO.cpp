#include "stdafx.h"
#include "CourseDAO.h"
#include "CourseMapper.h"

// 条件构造
std::string CourseDAO::queryConditionBuilder(const CourseQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    if (query->name) {
        std::string nameValue = query->name.getValue("");
        if (!nameValue.empty()) {
            sqlCondition << " AND c.`name` LIKE CONCAT('%',?,'%')";
            SQLPARAMS_PUSH(params, "s", std::string, nameValue);
        }
    }
    return sqlCondition.str();
}

// 计数
uint64_t CourseDAO::count(const CourseQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM course c ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CourseDO> CourseDAO::selectWithPage(const CourseQuery::Wrapper& query)
{
    SqlParams params;
    string sql = R"(
        SELECT 
            c.id,
            c.name,
            c.subject_id,      
            s.name AS subject_name,
            c.lesson_type,
            c.lesson_count,
            c.price,
            c.expire_months,
            c.add_time,        
            c.close_date,     
            c.description
        FROM course c
        LEFT JOIN subject s ON c.subject_id = s.id
    )";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY c.price DESC, c.lesson_count DESC ";
    sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize)
        + "," + std::to_string(query->pageSize);
    return sqlSession->executeQuery<CourseDO>(sql, CourseMapper(), params);
}

std::list<CourseDO> CourseDAO::selectById(const string& courseId)
{
    string sql = R"(
        SELECT 
            c.id,
            c.name,
            c.subject_id,
            s.name AS subject_name,
            c.lesson_type,
            c.lesson_count,
            c.price,
            c.expire_months,
            c.add_time,
            c.close_date,
            c.description
        FROM course c
        LEFT JOIN subject s ON c.subject_id = s.id
        WHERE c.id = ?
    )";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, courseId);
    return sqlSession->executeQuery<CourseDO>(sql, CourseMapper(), params);
}