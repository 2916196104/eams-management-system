//#include "stdafx.h"
//#include "MonthlyDataService.h"
//
//MonthlyDataDTO::Wrapper MonthlyDataService::listAll(const MonthlyDataQuery::Wrapper& query)
//{
//}


#include "stdafx.h"
#include "MonthlyDataService.h"

MonthlyDataDTO::Wrapper MonthlyDataService::listAll(const MonthlyDataQuery::Wrapper& query)
{
    // 构建返回对象（不分页）
    auto result = MonthlyDataDTO::createShared();

    // 查询数据（不分页，直接查询）
    MonthlyDataDAO dao;
    std::list<MonthlyDataViewDOPtr> list = dao.selectWithoutPage(query);

    if (!list.empty())
    {
        auto one = list.front();
        ZO_STAR_DOMAIN_DO_TO_DTO_1(result, one,
            rollcall_count, Rollcall_count,
            lesson_count, Lesson_count,
            student_count, Student_count,
            course_count, Course_count
        );
    }

    return result;
}