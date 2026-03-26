#include "stdafx.h"
#include "HomeworkDAO.h"
#include "HomeworkMapper.h"

std::string HomeworkDAO::queryConditionBuilder(const HomeworkQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 过滤未删除
    sqlCondition << " AND h.deleted = 0 AND c.deleted = 0 ";

    if (query->class_id)
    {
        sqlCondition << " AND h.class_id = ?";
        SQLPARAMS_PUSH(params, "i", uint64_t, query->class_id.getValue(0));
    }

    return sqlCondition.str();
}

uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;
    string sql = R"(
        SELECT COUNT(DISTINCT h.id)
        FROM homework h
        JOIN class c ON h.class_id = c.id
    )";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<HomeworkDO> HomeworkDAO::selectWithPage(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;

    // 这里和学生表一模一样！！！
    string sql = R"(
        SELECT
            c.name AS class_name,
            h.title,
            CASE WHEN hr.id IS NOT NULL THEN 1 ELSE 0 END AS submit_status
        FROM homework h
        JOIN class c ON h.class_id = c.id
        LEFT JOIN homework_record hr ON h.id = hr.homework_id
    )";

    // 拼接条件（和学生一样）
    sql += queryConditionBuilder(query, params);

    // 排序（和学生一样）
    sql += " ORDER BY h.add_time DESC, h.id DESC ";

    // ↓↓↓↓ 只有这里不一样！因为作业要分页！学生不需要！↓↓↓↓
    sql += " LIMIT ?, ?";

    // 分页参数（必须加，不然报错）
    int offset = (query->pageIndex - 1) * query->pageSize;
    int size = query->pageSize.getValue(0);
    SQLPARAMS_PUSH(params, "i", int, offset);
    SQLPARAMS_PUSH(params, "i", int, size);

    // 执行（和学生一样）
    return sqlSession->executeQuery<HomeworkDO>(sql, HomeworkMapper(), params);
}