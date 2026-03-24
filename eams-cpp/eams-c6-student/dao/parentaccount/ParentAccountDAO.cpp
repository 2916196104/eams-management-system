#include "stdafx.h"
#include "dao/parentaccount/ParentAccountDAO.h"
#include "dao/parentaccount/ParentAccountMapper.h"

uint64_t ParentAccountDAO::countParentAccount(const ParentAccountQuery::Wrapper& query)
{
    string sql =
        "SELECT COUNT(1) "
        "FROM `user` u "
        "LEFT JOIN `wx_access` w ON u.wx_access_id = w.id "
        "WHERE 1=1 ";
    SqlParams params;

    if (query->wxName && query->wxName.getValue("") != "") {
        sql += "AND w.nickname LIKE CONCAT('%',?,'%') ";
        SQLPARAMS_PUSH(params, "s", string, query->wxName.getValue(""));
    }

    if (query->keyword && query->keyword.getValue("") != "") {
        auto keyword = query->keyword.getValue("");
        sql += "AND (u.name LIKE CONCAT('%',?,'%') OR u.mobile = ?) ";
        SQLPARAMS_PUSH(params, "s", string, keyword);
        SQLPARAMS_PUSH(params, "s", string, keyword);
    }

    return sqlSession->executeQueryNumerical(sql, params);
}

list<ParentAccountQueryDO> ParentAccountDAO::listParentAccount(const ParentAccountQuery::Wrapper& query)
{
    string sql =
        "SELECT "
        "u.id AS user_id, "
        "u.mobile AS mobile, "
        "u.name AS name, "
        "IFNULL(GROUP_CONCAT(DISTINCT s.name ORDER BY s.id SEPARATOR '??'), '') AS student_name, "
        "IFNULL(w.nickname, '') AS wx_name, "
        "IFNULL(u.login_times, 0) AS login_times, "
        "IFNULL(DATE_FORMAT(u.latest_login_time, '%Y-%m-%d %H:%i:%s'), '') AS latest_login_time, "
        "IFNULL(u.latest_login_ip, '') AS latest_login_ip, "
        "IFNULL(DATE_FORMAT(u.add_time, '%Y-%m-%d %H:%i:%s'), '') AS add_time, "
        "IFNULL(u.state, 0) AS state "
        "FROM `user` u "
        "LEFT JOIN `wx_access` w ON u.wx_access_id = w.id "
        "LEFT JOIN `student` s ON s.user_id = u.id AND s.deleted = 0 "
        "WHERE 1=1 ";
    SqlParams params;

    if (query->wxName && query->wxName.getValue("") != "") {
        sql += "AND w.nickname LIKE CONCAT('%',?,'%') ";
        SQLPARAMS_PUSH(params, "s", string, query->wxName.getValue(""));
    }

    if (query->keyword && query->keyword.getValue("") != "") {
        auto keyword = query->keyword.getValue("");
        sql += "AND (u.name LIKE CONCAT('%',?,'%') OR u.mobile = ?) ";
        SQLPARAMS_PUSH(params, "s", string, keyword);
        SQLPARAMS_PUSH(params, "s", string, keyword);
    }

    sql +=
        "GROUP BY u.id, u.mobile, u.name, w.nickname, "
        "u.login_times, u.latest_login_time, u.latest_login_ip, u.add_time, u.state "
        "ORDER BY u.add_time DESC "
        "LIMIT ?, ? ";

    uint64_t pageIndex = query->pageIndex.getValue(1);
    uint64_t pageSize = query->pageSize.getValue(10);
    uint64_t offset = (pageIndex - 1) * pageSize;

    SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
    SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

    return sqlSession->executeQuery<ParentAccountQueryDO>(sql, ParentAccountPageQueryMapper(), params);
}