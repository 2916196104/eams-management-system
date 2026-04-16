#pragma once
#pragma once
#ifndef _MY_CUSTOMERS_SERVICE_
#define _MY_CUSTOMERS_SERVICE_

#include "domain/query/MyCustomers/MyCustomersQuery.h"
#include "domain/dto/MyCustomers/MyCustomersDTO.h"
#include "dao/Mycustomers/StudentDAO.h"
#include "dao/Mycustomers/StudentCourseDAO.h"

/**
 * 我的客户服务实现
 * 对应：学员列表、学员详情、学员课程
 */
class MyCustomersService
{
public:
    // 1. 我的客户（学员列表）- 分页查询
    MyCustomersPageDTO::Wrapper listMyCustomers(const MyCustomersQuery::Wrapper& query);

    // 2. 学员详情 - 根据ID查询
    MyCustomerDetailDTO::Wrapper getStudentDetail(uint64_t studentId);

    // 3. 学员课程列表 - 分页查询
    StudentCoursesPageDTO::Wrapper listStudentCourses(const StudentCourseQuery::Wrapper& query);
};

#endif // !_MY_CUSTOMERS_SERVICE_