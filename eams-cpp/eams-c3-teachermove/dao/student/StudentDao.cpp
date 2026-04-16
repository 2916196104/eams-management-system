#include "stdafx.h"
#include "StudentDao.h"
#include "StudentMapper.h"


// ========== 私有方法：查询条件构建器 ==========
std::string StudentDAO::queryConditionBuilder(
    const StudentQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 根据 Query 的字段动态拼接 WHERE 条件
    if (query->name) {
        sqlCondition << " AND s.`name`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
    }

    if (query->stage) {
        sqlCondition << " AND s.`stage`=?";
        SQLPARAMS_PUSH(params, "i", int8_t, query->stage.getValue(0));
    }

    return sqlCondition.str();
}

// ========== 查询方法 ==========

// 统计数据条数
uint64_t StudentDAO::count(const StudentQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM student ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询数据
std::list<StudentDO> StudentDAO::selectWithPage(const StudentQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT s.name, u.mobile, s.gender FROM student s INNER JOIN `user` u ON s.user_id = u.id";

    // 构建查询条件
    sql += queryConditionBuilder(query, params);

    // 构建排序语句
    sql += " ORDER BY s.`id` DESC ";

    // 构建分页条件
    sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize)
        + "," + std::to_string(query->pageSize);

    // 执行查询
    return sqlSession->executeQuery<StudentDO>(sql, StudentMapper(), params);
}

// // 通过姓名模糊查询
// std::list<StudentDO> StudentDAO::selectByName(const string& name)
// {
//     string sql = "SELECT id,name,sex,age FROM student WHERE `name` LIKE CONCAT('%',?,'%')";
//     return sqlSession->executeQuery<StudentDO>(sql, StudentMapper(), "%s", name);
// }

StudentDO StudentDAO::selectById(std::string id)
{
	const std::string sql =
		"SELECT s.name, IFNULL(u.mobile,''), s.gender FROM student s "
		"LEFT JOIN `user` u ON s.user_id = u.id "
		"WHERE s.id = ? AND s.deleted = 0 LIMIT 1";
	return sqlSession->executeQueryOne<StudentDO>(sql, StudentMapper(), "%s", id);
}

// ========== 增删改方法 ==========

// 插入数据
uint64_t StudentDAO::insert(const StudentDO& data)
{
    // 使用 BaseDAO 的通用插入方法
    return BaseDAO::insert(data);
}

// 批量插入数据
uint64_t StudentDAO::insertBatch(const std::list<StudentDO>& datas)
{
    // 使用 BaseDAO 的通用批量插入方法
    return BaseDAO::insertBatch(datas);
}

// 更新数据
uint64_t StudentDAO::update(const StudentDO& data)
{
    // 使用 BaseDAO 的通用更新方法
    return BaseDAO::update(data);
}

// 通过ID删除数据
uint64_t StudentDAO::deleteById(const std::string& id)
{
    string sql = "DELETE FROM sample WHERE `id`=?";
    return sqlSession->executeUpdate(sql, "%s", id);
}