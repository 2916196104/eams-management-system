#include "stdafx.h"
#include "GetTrialCardListDAO.h"
#include "GetTrialCardListMapper.h"
#include <sstream>
#include <string>

// 构建查询条件（子查询的WHERE条件）
std::string GetTrialCardListDAO::queryConditionBuilder(const GetTrialCardListQuery::Wrapper& query, SqlParams& params)
{
    std::stringstream sqlCondition;
    // 基础条件：确保trial_id非空，避免NOT IN空值问题
    sqlCondition << " WHERE ctr.trial_id IS NOT NULL ";

    // 如果传入了学生ID，添加学生ID过滤条件
    if (query->id) {
        sqlCondition << " AND ctr.student_id = ? ";
        SQLPARAMS_PUSH(params, "s", std::string, query->id.getValue(""));
    }

    return sqlCondition.str();
}

// 统计未领取试听卡的总数（无需查询courseName，仅需保证关联逻辑不影响计数）
uint64_t GetTrialCardListDAO::count(const GetTrialCardListQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT COUNT(DISTINCT ct.id) FROM course_trial ct \
                       LEFT JOIN course c ON ct.course_id = c.id  \
                       WHERE ct.state = TRUE AND ct.end_date > CURDATE() AND ct.id NOT IN ( \
                           SELECT ctr.trial_id FROM course_trial_record ctr ";

    sql += queryConditionBuilder(query, params);
    sql += " ) ";

    return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询学生未领取的试听卡列表（核心修改处）
std::list<GetTrialCardListDO> GetTrialCardListDAO::selectWithPage(const GetTrialCardListQuery::Wrapper& query)
{
    SqlParams params;

    // 严格按照DO字段定义查询，使用别名匹配
    // 改动1：添加 LEFT JOIN course c ON ct.courseId = c.id 关联课程表
    // 改动2：SELECT 中增加 c.courseName AS courseName（字段名根据实际course表调整）
    std::string sql = "SELECT ct.title AS title,          \
                              ct.lesson_count AS lessonCount,  \
                              ct.remaining_quantity AS remainingQuantity, \
                              ct.`end_date` AS endDate,        \
                              c.name AS courseName       \
        FROM course_trial ct \
        LEFT JOIN course c ON ct.course_id = c.id  \
        WHERE ct.state = TRUE AND ct.end_date > CURDATE() AND ct.id NOT IN(\
            SELECT ctr.trial_id FROM course_trial_record ctr" ;

    sql += queryConditionBuilder(query, params);
    sql += " ) ";

    // 分页逻辑
    if (query->pageIndex > 0 && query->pageSize > 0) {
        uint64_t offset = (query->pageIndex - 1) * query->pageSize;
        sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);
    }

    return sqlSession->executeQuery<GetTrialCardListDO>(sql, GetTrialCardListMapper(), params);
}