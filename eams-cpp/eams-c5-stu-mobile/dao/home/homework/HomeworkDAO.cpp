#include "stdafx.h"
#include "HomeworkDAO.h"       // 替换为HomeworkDAO头文件
#include "HomeworkMapper.h"   // 替换为HomeworkMapper头文件

// 条件构建方法：参数替换为HomeworkQuery，适配homework表查询字段
std::string HomeworkDAO::queryConditionBuilder(const HomeworkQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 1. 班级ID查询（homework表核心索引字段，NOT NULL）
    if (query->class_id)
    {
        sqlCondition << " AND class_id =?";
        // 类型适配：homework.class_id是bigint → uint64_t
        SQLPARAMS_PUSH(params, "i", uint64_t, query->class_id.getValue(0));
    }

    // 2. 删除标记筛选（homework.deleted是tinyint(1)，默认0）
    if (query->deleted)
    {
        sqlCondition << " AND deleted =?";
        // 类型适配：tinyint(1) → bool（自动转换为0/1）
        SQLPARAMS_PUSH(params, "i", bool, query->deleted.getValue(false));
    }

    // 3. 创建人查询（homework.creator是bigint，可选）
    if (query->creator)
    {
        sqlCondition << " AND creator =?";
        SQLPARAMS_PUSH(params, "i", uint64_t, query->creator.getValue(0));
    }

    // 4. 组织ID查询（homework.org_id是bigint，可选）
    if (query->org_id)
    {
        sqlCondition << " AND org_id =?";
        SQLPARAMS_PUSH(params, "i", uint64_t, query->org_id.getValue(0));
    }

    return sqlCondition.str();
}

// 计数方法：表名改为homework，参数替换为HomeworkQuery
uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;
    // 核心：数据库表名改为homework（匹配作业表）
    string sql = "SELECT COUNT(*) FROM homework ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 执行查询（返回总数）
    return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询方法：适配HomeworkDO/HomeworkMapper，表名改为homework
std::list<HomeworkDO> HomeworkDAO::selectWithPage(const HomeworkQuery::Wrapper& query)
{
    SqlParams params;
    // 数据库表名改为homework
    string sql = "SELECT * FROM homework ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);

    // 排序语句适配homework表字段（优先按添加时间降序，再按主键降序）
    // 匹配homework表的add_time/edit_time/id字段，符合业务查询习惯
    sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";

    // 构建分页条件（复用PageQuery的pageIndex/pageSize，逻辑不变）
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询：替换为HomeworkDO和HomeworkMapper，匹配作业表字段映射
    return sqlSession->executeQuery<HomeworkDO>(sql, HomeworkMapper(), params);
}