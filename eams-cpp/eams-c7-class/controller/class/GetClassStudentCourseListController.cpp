#include "stdafx.h"
#include "GetClassStudentCourseListController.h"

StudentCoursePageJsonVO::Wrapper GetClassStudentCourseListController::executeGetStudentCourseList(
    const StudentCourseListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    // 创建响应VO
    auto vo = StudentCoursePageJsonVO::createShared();

    // TODO: 调用Service查询学员课程列表
    // auto result = StudentService::getStudentCourseList(query, payload);

    // 返回空数据
    auto pageDto = StudentCoursePageDTO::createShared();
    vo->success(pageDto);

    return vo;
}