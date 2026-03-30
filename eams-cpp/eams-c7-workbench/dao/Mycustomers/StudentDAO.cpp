#include "stdafx.h"
#include "StudentDAO.h"
#include "StudentMapper.h"

std::string StudentDAO::queryConditionBuilder(const MyCustomersQuery::Wrapper& query, SqlParams& params)
{
    stringstream sql;
    sql << " WHERE s.deleted = 0 ";

    if (query->counselor_id) {
        sql << " AND s.counselor = ? ";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->counselor_id.getValue(0));
    }
    if (query->name) {
        sql << " AND s.name LIKE ? ";
        SQLPARAMS_PUSH(params, "s", string, "%" + query->name.getValue("") + "%");
    }
    return sql.str();
}

uint64_t StudentDAO::count(const MyCustomersQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM student s ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<StudentDO> StudentDAO::selectPage(const MyCustomersQuery::Wrapper& query)
{
    SqlParams params;
    string sql
        =
        R"(
        SELECT 
          s.*, 
          u.mobile AS mobile,
          TIMESTAMPDIFF(YEAR, s.birthday, CURDATE()) AS age
        FROM student s
        LEFT JOIN `user` u ON s.user_id = u.id
    )";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY s.add_time DESC ";

    int page = query->pageIndex.getValue(1);
    int size = query->pageSize.getValue(10);
    sql += " LIMIT " + to_string((page - 1) * size) + "," + to_string(size);

    return sqlSession->executeQuery<StudentDO>(sql, StudentMapper(), params);
}

PtrStudentDO StudentDAO::selectById(uint64_t id)
{
    string sql
        =
        R"(
        SELECT 
          s.*, 
          u.mobile,
          TIMESTAMPDIFF(YEAR, s.birthday, CURDATE()) AS age
        FROM student s
        LEFT JOIN `user` u ON s.user_id = u.id
        WHERE s.id = ? AND s.deleted = 0
        )";
    return sqlSession->executeQueryOne<PtrStudentDO>(sql, PtrStudentMapper(), "ll", id);
}