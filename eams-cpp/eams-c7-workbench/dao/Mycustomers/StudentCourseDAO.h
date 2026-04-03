#pragma once
#ifndef _StudentCourseDAO_
#define _StudentCourseDAO_

#include "BaseDAO.h"
#include "../../domain/do/Mycustomers/StudentCourseDo.h"
#include "../../domain/query/MyCustomers/MyCustomersQuery.h"

class StudentCourseDAO : public BaseDAO
{
private:
    std::string queryConditionBuilder(const StudentCourseQuery::Wrapper& query, SqlParams& params);
public:
    // 统计数量
    uint64_t count(const StudentCourseQuery::Wrapper& query);

    // 分页查询
    std::list<StudentCourseDO> selectPage(const StudentCourseQuery::Wrapper& query);

    // 根据学生ID查询
    std::list<StudentCourseDO> selectByStudentId(uint64_t id);
};

#endif // !_StudentCourseDAO_