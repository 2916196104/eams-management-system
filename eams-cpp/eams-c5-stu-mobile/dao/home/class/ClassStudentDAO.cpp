#include "stdafx.h"
#include "ClassStudentDAO.h"       // 替换为ClassStudentDAO头文件
#include "ClassStudentMapper.h"   // 替换为ClassStudentMapper头文件

// 条件构建方法：参数替换为ClassStudentQuery
std::string ClassStudentDAO::queryConditionBuilder(const ClassStudentQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    // 保留student_id查询条件（与class_student表字段匹配）
    if (query->student_id)
    {
        sqlCondition << " AND student_id =?";
        // 类型适配：class_student表的student_id是bigint，对应uint64_t（若项目中用int则保留）
        // 若student_id是uint64_t，需改为：SQLPARAMS_PUSH(params, "i", uint64_t, query->student_id.getValue(0));
        SQLPARAMS_PUSH(params, "i", int, query->student_id.getValue(0));
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

    // 排序语句适配class_student表字段（确认表中有edit_time/add_time/id字段，若无则调整）
    // 若class_student表无edit_time/add_time，可改为：ORDER BY `add_time` DESC, `id` DESC
    sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";

    // 构建分页条件（PageQuery的pageIndex/pageSize字段不变）
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询：替换为ClassStudentDO和ClassStudentMapper
    return sqlSession->executeQuery<ClassStudentDO>(sql, ClassStudentMapper(), params);
}