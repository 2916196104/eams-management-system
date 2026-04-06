#include "stdafx.h"
#include "StudentDAO.h"
#include "StudentMapper.h"
#include "SqlSession.h"
#include <cstdint>

// 分页查询学员列表
std::list<PtrStudentDO> StudentDAO::selectAll(const StudentQuery::Wrapper& query)
{
    string sql = "SELECT * FROM student WHERE deleted = 0 ";
    SqlParams params;

    // 拼接分页条件
    sql += " LIMIT ?,?";
    SQLPARAMS_PUSH(params, "ull", uint64_t, (uint64_t)(query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
    SQLPARAMS_PUSH(params, "ull", uint64_t, (uint64_t)query->pageSize.getValue(10));

    return sqlSession->executeQuery<PtrStudentDO>(sql, StudentMapper(), params);
}

// 统计学员总数
uint64_t StudentDAO::count(const StudentQuery::Wrapper& query)
{
    string sql = "SELECT count(id) FROM student WHERE deleted = 0 ";
    SqlParams params;
    return sqlSession->executeQueryNumerical(sql, params);
}

// 检查学员是否存在（切换学员）
bool StudentDAO::findById(uint64_t id)
{
    string sql = "SELECT count(id) FROM student WHERE id=? AND deleted=0 ";
    SqlParams params;
    SQLPARAMS_PUSH(params, "ull", uint64_t, id);

    auto count = sqlSession->executeQueryNumerical(sql, params);
    return count > 0;
}

// 软删除学员
bool StudentDAO::deleteById(uint64_t id)
{
    string sql = "UPDATE student SET deleted=1 WHERE id=? ";
    SqlParams params;
    SQLPARAMS_PUSH(params, "ull", uint64_t, id);

    auto aff = sqlSession->executeUpdate(sql, params);
    return aff > 0;
}

// 按ID查询单个学员（预留实现）
PtrStudentDO StudentDAO::selectById(const string& id)
{
    string sql = "SELECT * FROM student WHERE id=? AND deleted=0 ";
    SqlParams params;
    SQLPARAMS_PUSH(params, "ull", uint64_t, std::stoull(id));
    auto list = sqlSession->executeQuery<PtrStudentDO>(sql, StudentMapper(), params);
    return list.empty() ? nullptr : list.front();
}