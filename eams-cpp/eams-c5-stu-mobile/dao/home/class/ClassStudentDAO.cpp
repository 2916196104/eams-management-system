#include "stdafx.h"
#include "ClassStudentDAO.h"       // 替换为ClassStudentDAO头文件
#include "ClassStudentMapper.h"   // 替换为ClassStudentMapper头文件

// 条件构建方法：参数替换为ClassStudentQuery
std::string ClassStudentDAO::queryConditionBuilder(const ClassStudentQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    // 保留class_id查询条件（与class_student表字段匹配）
    if (query->class_id)
    {
        sqlCondition << " AND class_id =?";
        // 类型适配：class_student表的class_id是bigint，改用uint64_t更匹配
        SQLPARAMS_PUSH(params, "i", uint64_t, query->class_id.getValue(0));
    }
    return sqlCondition.str();
}

// 计数方法：表名改为class_student，参数替换为ClassStudentQuery
uint64_t ClassStudentDAO::count(const ClassStudentQuery::Wrapper& query)
{
    SqlParams params;
    // 数据库表名改为class_student（核心：匹配班级学员表）
    string sql = "SELECT COUNT(*) FROM class_student ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 执行查询
    return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询方法：适配ClassStudentDO/ClassStudentMapper，表名改为class_student
std::list<ClassStudentDO> ClassStudentDAO::selectWithPage(const ClassStudentQuery::Wrapper& query)
{
    SqlParams params;
    // 数据库表名改为class_student
    string sql = "SELECT * FROM class_student ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);

    // 修复：移除不存在的edit_time字段，仅用add_time排序（匹配class_student表结构）
    sql += " ORDER BY `add_time` DESC, `id` DESC ";

    // 构建分页条件（PageQuery的pageIndex/pageSize字段不变）
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询：替换为ClassStudentDO和ClassStudentMapper
    return sqlSession->executeQuery<ClassStudentDO>(sql, ClassStudentMapper(), params);
}