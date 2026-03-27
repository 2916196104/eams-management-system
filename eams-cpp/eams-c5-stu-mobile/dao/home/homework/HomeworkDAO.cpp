#include "stdafx.h"
#include "HomeworkDAO.h"
#include "HomeworkMapper.h"

std::string HomeworkDAO::queryConditionBuilder(const HomeworkQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 逻辑删除过滤
    sqlCondition << " AND h.deleted = 0 AND cs.deleted = 0 ";

    // 按学生ID查询
    if (query->student_id)
    {
        sqlCondition << " AND cs.student_id = ? ";
        SQLPARAMS_PUSH(params, "i", uint64_t, query->student_id.getValue(0));
    }

    return sqlCondition.str();
}

uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;
    string sql = R"(
        SELECT COUNT(DISTINCT h.id)
        FROM homework h
        JOIN class_student cs ON h.class_id = cs.class_id
    )";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<HomeworkDO> HomeworkDAO::selectWithPage(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;

    // ? 完全适配你 4 张表的终极 SQL
    string sql = R"(
        SELECT
            c.name AS class_name,
            h.title,
            CASE WHEN hr.id IS NOT NULL THEN 1 ELSE 0 END AS submit_status
        FROM homework h
        JOIN class c ON h.class_id = c.id
        JOIN class_student cs ON h.class_id = cs.class_id
        LEFT JOIN homework_record hr 
            ON h.id = hr.homework_id 
            AND hr.student_id = ?
    )";

    // 绑定学生ID，用于查询提交记录
    SQLPARAMS_PUSH(params, "i", uint64_t, query->student_id.getValue(0));

    // 拼接查询条件
    sql += queryConditionBuilder(query, params);

    // 排序 + 分页
    sql += " ORDER BY h.add_time DESC, h.id DESC ";
    sql += " LIMIT ?, ?";

    int offset = (query->pageIndex - 1) * query->pageSize;
    int size = query->pageSize.getValue(0);
    SQLPARAMS_PUSH(params, "i", int, offset);
    SQLPARAMS_PUSH(params, "i", int, size);

    return sqlSession->executeQuery<HomeworkDO>(sql, HomeworkMapper(), params);
}