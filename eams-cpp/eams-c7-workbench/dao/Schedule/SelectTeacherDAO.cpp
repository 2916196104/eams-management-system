#include "stdafx.h"
#include "SelectTeacherDAO.h"
#include "SelectTeacherWrapper.h"

std::list<SelectTeacherViewDOPtr> SelectTeacherDAO::selectWithPage(const SelectTeacherQuery::Wrapper& query, uint32_t pageIndex, uint32_t pageSize)
{
    SqlParams params;
    std::string sql = R"(
    SELECT
    *
    FROM staff
    WHERE staff.state = 1
    )";

    if (query->name) {
        sql += " AND staff.name LIKE ?";
        std::string namePattern = "%" + query->name.getValue("") + "%";
        SQLPARAMS_PUSH(params, "s", std::string, namePattern);
    }

    sql += " ORDER BY staff.id DESC";
    sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

    return sqlSession->executeQuery<SelectTeacherViewDOPtr>(sql, SelectTeacherWrapperPtr(), params);
}

uint64_t SelectTeacherDAO::count(const SelectTeacherQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = R"(
    SELECT
    COUNT(*)
    FROM staff
    WHERE 1=1
    AND staff.state = 1
    )";

    if (query->name) {
        sql += " AND staff.name LIKE ?";
        std::string namePattern = "%" + query->name.getValue("") + "%";
        SQLPARAMS_PUSH(params, "s", std::string, namePattern);
    }

    return sqlSession->executeQueryNumerical(sql, params);
}