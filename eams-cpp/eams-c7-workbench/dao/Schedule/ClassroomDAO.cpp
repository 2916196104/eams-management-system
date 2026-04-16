#include "stdafx.h"
#include "dao/Schedule/ClassroomDAO.h"
#include "dao/Schedule/ClassroomMapper.h"

// 获取数据条数
uint64_t ClassroomDAO::count(const ClassroomQuery::Wrapper& query)
{
    string sql = "SELECT COUNT(id) FROM classroom";
    SqlParams params;

    //对查询参数判空
    if (query->name) {
        sql += " WHERE name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name + "%");
    }

    return sqlSession->executeQueryNumerical(sql, params);
}
// 获取教室列表
std::list<PtrClassroomDO> ClassroomDAO::selectAll(const ClassroomQuery::Wrapper& query)
{
    string sql = R"(
            SELECT 
                id, name, address
            FROM 
                classroom
        )";
    SqlParams params;

    if (query->name) {
        sql += " WHERE name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name + "%");
    }

    // 添加分页
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex - 1) * query->pageSize);
    SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize);

    return sqlSession->executeQuery<PtrClassroomDO>(sql, ClassroomMapper(), params);
}
