/*
 @Author: abinng
 @Date: 2026/03/23 17:37:41
 @File: ReviewDAO.cpp
*/
#include "stdafx.h"
#include "ReviewDAO.h"
#include "ReviewMapper.h"

uint64_t ReviewDAO::count(const ReviewRecordQuery::Wrapper& query) 
{
    SqlSession* session = getSqlSession();
    if (!session) {
        return 0;
    }

    std::string sql = "SELECT COUNT(1) AS total FROM `lesson_student` WHERE 1=1";
    SqlParams params;

    if (query->student_id) {
        sql += " AND student_id = ?";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
    }

    try {
        // 执行查询
        uint64_t total = session->executeQueryNumerical(sql, params);
        return total;
    } catch(const std::exception &e) {
        std::cerr << "[ReviewDAO::count] 异常：" << e.what() << std::endl;
        return 0;   // 异常返回0
    }
}

std::list<PtrReviewViewDO> ReviewDAO::selectByQuery(const ReviewRecordQuery::Wrapper& query) 
{
    std::string sql = R"(SELECT 
        ls.id, 
        ls.lesson_id, 
        l.title AS lesson_title, 
        ls.evaluate_teacher, 
        ls.evaluation, 
        ls.score, 
        ls.evaluate_time 
        FROM 
        `lesson_student` ls 
        LEFT JOIN `lesson` l ON ls.lesson_id = l.id
        WHERE 
        1=1
     )";

    try {
        // 获取数据库会话
        SqlSession* session = getSqlSession();
        if (!session) {
            std::cerr << "[ReviewDAO::selectByQuery] : 获取数据库会话失败" << std::endl;
            return std::list<PtrReviewViewDO>(); // 获取数据库会话失败时，返回空列表
        }

        // 构造参数列表：条件、分页参数
        // 构造查询参数
        SqlParams params;
        if (query->student_id) {
            sql += " AND ls.student_id = ?";
            SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
        } else {
            std::cerr << "[ReviewDAO::selectByQuery] : 缺少查询参数" << std::endl;
            return std::list<PtrReviewViewDO>(); // 缺少查询参数时，返回空列表
        }

        // 加上排序保证每次查询结果顺序一致
        sql += " ORDER BY ls.evaluate_time DESC";
        if (query->pageIndex || query->pageSize) {
            uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
            sql += " LIMIT ? OFFSET ?";
            SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
            SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
        } else {
            std::cerr << "[ReviewDAO::selectByQuery] : 缺少分页参数" << std::endl;
            return std::list<PtrReviewViewDO>(); // 缺少分页参数，返回空列表
        }

        auto result = session->executeQuery<PtrReviewViewDO>(sql, ReviewMapper(), params);
        if (result.empty()) {   // 查询结果为空
            return std::list<PtrReviewViewDO>();    // 返回空列表
        }
        return result;
    } catch (const std::exception& e) {
        std::cerr << "[ReviewDAO::selectByQuery] : 异常" << e.what() << std::endl;
        return std::list<PtrReviewViewDO>(); // 返回空列表
    }
}
