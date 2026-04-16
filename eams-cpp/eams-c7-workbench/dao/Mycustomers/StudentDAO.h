#pragma once
#ifndef _StudentDAO_
#define _StudentDAO_

#include "BaseDAO.h"
#include "domain/do/Mycustomers/StudentDo.h"
#include "domain/query/MyCustomers/MyCustomersQuery.h"

class StudentDAO : public BaseDAO
{
private:
    std::string queryConditionBuilder(const MyCustomersQuery::Wrapper& query, SqlParams& params);
public:
    // 统计学员数量
    uint64_t count(const MyCustomersQuery::Wrapper& query);

    // 分页查询学员
    std::list<StudentDO> selectPage(const MyCustomersQuery::Wrapper& query);

    // 根据ID查询学员
    PtrStudentDO selectById(uint64_t id);
};

#endif // !_StudentDAO_