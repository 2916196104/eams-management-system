#include "stdafx.h"
#include "ClassStudentDAO.h"
#include "ClassStudentMapper.h"

std::string ClassStudentDAO::queryConditionBuilder(const ClassStudentQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    if (query->class_id)
    {
        sqlCondition << " AND cs.class_id = ?";
        SQLPARAMS_PUSH(params, "i", uint64_t, query->class_id.getValue(0));
    }

    return sqlCondition.str();
}

std::list<ClassStudentDO> ClassStudentDAO::selectAll(const ClassStudentQuery::Wrapper& query)
{
    SqlParams params;

    string sql = R"(
        SELECT s.name, s.gender
        FROM class_student cs
        LEFT JOIN student s ON cs.student_id = s.id
    )";

    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY cs.add_time DESC, cs.id DESC";

    return sqlSession->executeQuery<ClassStudentDO>(sql, ClassStudentMapper(), params);
}