#include "stdafx.h"
#include "MyCustomersService.h"
#include <string>

#define deBug 1

// 1. 我的客户（学员列表）
MyCustomersPageDTO::Wrapper MyCustomersService::listMyCustomers(const MyCustomersQuery::Wrapper& query) {
    // 创建返回分页对象
    auto pages = MyCustomersPageDTO::createShared();

    // 检查query是否为空
    if (!query) {
        pages->pageIndex = 1;
        pages->pageSize = 10;
        return pages;
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    // 查询总条数
    StudentDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) {
        return pages;
    }

    // 分页查询数据
    pages->total = count;
    list<StudentDO> result = dao.selectPage(query);

    // DO → DTO 转换
    for (StudentDO& sub : result) {
        auto dto = MyCustomersDTO::createShared();
        dto->MyCustomersName = sub.getName();       // 姓名
        dto->phoneNumber = sub.getMobile();    // 电话
        pages->addData(dto);
    }
    return pages;
}

// 2. 学员详情
MyCustomerDetailDTO::Wrapper MyCustomersService::getStudentDetail(uint64_t studentId) {
    // 创建返回详情对象
    auto dto = MyCustomerDetailDTO::createShared();

    // 查询DO
    StudentDAO dao;
    PtrStudentDO data = dao.selectById(studentId);
    if (!data) {
        return dto;
    }

    // DO → DTO 转换
    dto->MyCustomersName = data->getName();
    dto->phoneNumber = data->getMobile();
    dto->sex = (data->getGender() == 1) ? ZH_WORDS_GETTER("cus.field.sex.male")
        : ZH_WORDS_GETTER("cus.field.sex.female");  // 假设1为男
    dto->age = data->getAge();
    dto->birth = data->getBirthday();
    dto->type = (data->getStage() == 1 ? ZH_WORDS_GETTER("cus.field.type.formal")
        : ZH_WORDS_GETTER("cus.field.type.trial"));
    dto->notes = data->getRemark();

    return dto;
}

// 3. 学员课程列表
StudentCoursesPageDTO::Wrapper MyCustomersService::listStudentCourses(const StudentCourseQuery::Wrapper& query) {
    auto pages = StudentCoursesPageDTO::createShared();
    if (!query) {
        pages->pageIndex = 1;
        pages->pageSize = 10;
        return pages;
    }
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    StudentCourseDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0) {
        return pages;
    }
    pages->total = count;
    list<StudentCourseDO> result = dao.selectPage(query);

    for (StudentCourseDO& sub : result) {
        auto dto = StudentCourseDTO::createShared();
        dto->courseName = sub.getCourseName();
        dto->totalLessons = sub.getCountLessonTotal();    // 总次数（int）
        dto->finishedLessons = sub.getCountLessonComplete(); // 已学次数（int）
        dto->remainingLessons = sub.getCountLessonTotal() - sub.getCountLessonComplete();
        dto->expireTime = sub.getExpireDate();
        pages->addData(dto);
    }
    return pages;
}