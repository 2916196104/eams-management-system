#include "stdafx.h"
#include "RegistrationDAO.h"
#include "RegistrationMapper.h"

uint64_t RegistrationDAO::count(const RegistrationRecordQuery::Wrapper& query) 
{
    SqlSession* session = getSqlSession();
    if (!session) {
        return 0;
    }
    std::string sql = "SELECT COUNT(1) AS total FROM `student_course` sc WHERE sc.deleted = 0 AND 1=1";
    SqlParams params;
    if (query->student_id) {
        sql += " AND student_id = ?";
        SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
    }
    try {
        // 执行查询
        uint64_t total = session->executeQueryNumerical(sql, params);
        return total;
    } catch (const std::exception& e) {
        std::cerr << "[RegistrationDAO::count] 异常：" << e.what() << std::endl;
        return 0; // 异常返回0
    }

}

std::list<PtrRegistrationViewDO> RegistrationDAO::selectByQuery(const RegistrationRecordQuery::Wrapper& query) 
{
    std::string sql = R"(SELECT 
        sc.id, 
        sc.student_id, 
        stu.name AS student_name, 
        sc.course_id, 
        c.name AS course_name, 
        c.subject_id,
        sub.name AS subject_name,
        sc.add_time, 
        sc.expire_date, 
        sc.amount, 
        sc.paid_amount, 
        sc.count_lesson_total, 
        sc.count_lesson_complete,
        c.lesson_type,
        sc.verify_state
        FROM 
        `student_course` sc 
        LEFT JOIN `student` stu ON sc.student_id = stu.id
        LEFT JOIN `course` c ON sc.course_id = c.id
        LEFT JOIN `subject` sub ON sc.subject_id = sub.id
        WHERE 
        sc.deleted = 0
        AND 1=1
     )";
    try {
        // 获取数据库会话
        SqlSession* session = getSqlSession();
        if (!session) {
            std::cerr << "[RegistrationDAO::selectByQuery] : 获取数据库会话失败" << std::endl;
            return std::list<PtrRegistrationViewDO>(); // 获取数据库会话失败时，返回空列表
        }
        // 构造参数列表：条件、分页参数
        // 构造查询参数
        SqlParams params;
        if (query->student_id) {
            sql += " AND sc.student_id = ?";
            SQLPARAMS_PUSH(params, "ll", uint64_t, query->student_id.getValue(1));
        } else {
            std::cerr << "[RegistrationDAO::selectByQuery] : 缺少查询参数" << std::endl;
            return std::list<PtrRegistrationViewDO>(); // 缺少查询参数时，返回空列表
        }
        // 加上排序保证每次查询结果顺序一致
        sql += " ORDER BY sc.add_time DESC";
        if (query->pageIndex || query->pageSize) {
            uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
            sql += " LIMIT ? OFFSET ?";
            SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
            SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
        } else {
            std::cerr << "[RegistrationDAO::selectByQuery] : 缺少分页参数" << std::endl;
            return std::list<PtrRegistrationViewDO>(); // 缺少分页参数，返回空列表
        }
        auto result = session->executeQuery<PtrRegistrationViewDO>(sql, RegistrationMapper(), params);
        if (result.empty()) {                    // 查询结果为空
            return std::list<PtrRegistrationViewDO>(); // 返回空列表
        }
        return result;
    } catch (const std::exception& e) {
        std::cerr << "[RegistrationDAO::selectByQuery] : 异常" << e.what() << std::endl;
        return std::list<PtrRegistrationViewDO>(); // 返回空列表
    }


}
