/*
 @Author: abinng
 @Date: 2026/03/22 15:04:40
 @File: ScoreDAO.cpp
*/

#include "stdafx.h"
#include "ScoreDAO.h"
#include "ScoreMapper.h"

uint64_t ScoreDAO::count(const ScoreQuery::Wrapper &query)
{
    SqlSession *session = getSqlSession();
    if (!session)
        return 0;

    std::string sql = "SELECT COUNT(1) AS total FROM `grade_record` WHERE 1=1";
    SqlParams params;

    if (query->student_id) {
        sql += " AND student_id = ?";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
    }

    try {
        uint64_t total = session->executeQueryNumerical(sql, params);
        return total;
    } catch (const std::exception &e) {
        std::cerr << "[ScoreDAO::count] 异常：" << e.what() << std::endl;
        return 0;
    }
}
std::list<PtrScoreViewDO> ScoreDAO::selectByQuery(const ScoreQuery::Wrapper &query)
{
    // 定义连表查询 SQL ，未包含 WHERE 条件
    std::string sql = R"(SELECT
        gr.id,
        gr.grade_id,
        g.title AS grade_title,
        gr.student_id,
        s.name AS student_name,
        gr.score,
        gr.add_time
        FROM
        `grade_record` gr
        LEFT JOIN `grade` g ON gr.grade_id = g.id AND g.deleted = 0
        LEFT JOIN `student` s ON gr.student_id = s.id AND s.deleted = 0
        WHERE
        1=1
        )";
    try {
        // 获取数据库会话
        SqlSession *session = getSqlSession();
        if (!session) {
            std::cerr << "[ScoreDAO::selectByQuery] : 获取数据库会话失败" << std::endl;
            return std::list<PtrScoreViewDO>(); // 获取数据库会话失败时，返回nullptr
        }

        // 构造参数列表：条件、分页参数
        // 构造查询参数
        SqlParams params;
        if (query->student_id) {
            sql += " AND gr.student_id = ?";
            SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
        } else {
            std::cerr << "[ScoreDAO::selectByQuery] : 缺少查询参数" << std::endl;
            return std::list<PtrScoreViewDO>(); // 缺少查询参数时，返回空列表
        }
        // 加上排序
        sql += " ORDER BY gr.add_time DESC";
        // 构造分页参数
        if (query->pageIndex && query->pageSize) {
            uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
            sql += " LIMIT ? OFFSET ?";
            SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
            SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
        } else {
            std::cerr << "[ScoreDAO::selectByQuery] : 缺少分页参数" << std::endl;
        }

        // 执行查询
        auto result = session->executeQuery<PtrScoreViewDO>(sql, ScoreViewMapper(), params);
        if (result.empty()) {
            std::cerr << "[ScoreDAO::selectByQuery] : 查询结果为空或查询异常" << std::endl;
            return std::list<PtrScoreViewDO>(); // 查询结果为空或查询异常时，返回空列表
        }
        return result;
    } catch (const std::exception &e) {
        std::cerr << "[ScoreDAO::selectByQuery] : 异常" << e.what() << std::endl;
        return std::list<PtrScoreViewDO>(); // 异常时，返回空列表
    }
}
