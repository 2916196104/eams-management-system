#include "stdafx.h"
#include "SelectClassDAO.h"
#include "SelectClassWrapper.h"

std::list<SelectClassViewDOPtr> SelectClassDAO::selectWithPage(const SelectClassQuery::Wrapper& query, uint32_t pageIndex, uint32_t pageSize)
{
    SqlParams params;
    std::string sql = R"(
    SELECT
    *
    FROM class
    WHERE class.be_over = 0
    )";

    if (query->name) {
        sql += " AND class.name LIKE ?";
        std::string namePattern = "%" + query->name.getValue("") + "%";
        SQLPARAMS_PUSH(params, "s", std::string, namePattern);
    }

    sql += " ORDER BY class.id DESC";
    sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

    return sqlSession->executeQuery<SelectClassViewDOPtr>(sql, SelectClassWrapperPtr(), params);
}

uint64_t SelectClassDAO::count(const SelectClassQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = R"(
    SELECT
    COUNT(*)
    FROM class
    WHERE 1=1
    AND class.be_over = 0
    )";

    if (query->name) {
        sql += " AND class.name LIKE ?";
        std::string namePattern = "%" + query->name.getValue("") + "%";
        SQLPARAMS_PUSH(params, "s", std::string, namePattern);
    }

    return sqlSession->executeQueryNumerical(sql, params);
}