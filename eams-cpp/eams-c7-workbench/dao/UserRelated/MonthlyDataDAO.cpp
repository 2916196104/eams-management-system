//#include "stdafx.h"
//#include "MonthlyDataDAO.h"
//#include "MonthlyDataWrapper.h"
//
//std::list<MonthlyDataViewDOPtr> MonthlyDataDAO::selectWithoutPage(const MonthlyDataQuery::Wrapper& query)
//{
//}
//
//uint64_t MonthlyDataDAO::count(const MonthlyDataQuery::Wrapper& query)
//{
//}

#include "stdafx.h"
#include "MonthlyDataDAO.h"
#include "MonthlyDataWrapper.h"

std::list<MonthlyDataViewDOPtr> MonthlyDataDAO::selectWithoutPage(const MonthlyDataQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = R"(
    SELECT
        COALESCE((SELECT COUNT(lesson_student.id) 
            FROM lesson_student 
            WHERE lesson_student.sign_time >= DATE_FORMAT(CURDATE(), '%Y-%m-01')), 0) AS rollcall_count,
        COALESCE((SELECT COUNT(lesson.id) 
            FROM lesson 
            WHERE lesson.date >= DATE_FORMAT(CURDATE(), '%Y-%m-01')), 0) AS lesson_count,
        COALESCE((SELECT COUNT(student.id) 
            FROM student 
            WHERE student.add_time >= DATE_FORMAT(CURDATE(), '%Y-%m-01')), 0) AS student_count,
        COALESCE((SELECT SUM(student_course.paid_amount) 
            FROM student_course 
            WHERE student_course.add_time >= DATE_FORMAT(CURDATE(), '%Y-%m-01')), 0)
            -
        COALESCE((SELECT SUM(refund.refund_amount) 
            FROM refund 
            WHERE refund.done_time >= DATE_FORMAT(CURDATE(), '%Y-%m-01')), 0) AS course_count
    )";

    return sqlSession->executeQuery<MonthlyDataViewDOPtr>(sql, MonthlyDataWrapperPtr(), params);
}

uint64_t MonthlyDataDAO::count(const MonthlyDataQuery::Wrapper& query)
{
    return 1;
}