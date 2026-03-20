#include "stdafx.h"
#include "CourseController.h"

// 前面必须加 CourseController::
CourseListJsonVO::Wrapper CourseController::execQueryCourseDetail(const QueryParams& queryParams)
{
    return CourseListJsonVO::createShared();
}

CoursePageJsonVO::Wrapper CourseController::execQueryPage(const CourseQuery::Wrapper& query)
{
    return {};
}

Uint64JsonVO::Wrapper CourseController::execSave(const CourseDTO::Wrapper& dto, const PayloadDTO& payload)
{
    return {};
}