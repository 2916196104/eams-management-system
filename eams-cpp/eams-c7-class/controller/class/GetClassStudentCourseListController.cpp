#include "stdafx.h"
#include "GetClassStudentCourseListController.h"
#include "service/ClassStudentService.h"

StudentCoursePageJsonVO::Wrapper GetClassStudentCourseListController::executeGetStudentCourseList(
    const StudentCourseListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    auto jvo = StudentCoursePageJsonVO::createShared();
    auto emptyPageDto = StudentCoursePageDTO::createShared();

    // 参数校验
    if (!query || !query->studentId || query->studentId == 0) {
        jvo->fail(emptyPageDto);
        return jvo;
    }

    // 创建查询对象的副本
    auto queryCopy = StudentCourseListQuery::createShared();

    // 复制查询条件字段
    queryCopy->studentId = query->studentId;
    if (query->courseName) {
        queryCopy->courseName = query->courseName;
    }

    // 复制分页字段并校正
    queryCopy->pageIndex = query->pageIndex;
    queryCopy->pageSize = query->pageSize;

    // 校正分页参数
    if (queryCopy->pageIndex < 1) {
        queryCopy->pageIndex = 1;
    }
    if (queryCopy->pageSize < 1) {
        queryCopy->pageSize = 10;
    }
    if (queryCopy->pageSize > 100) {
        queryCopy->pageSize = 100;
    }

    try {
        auto service = std::make_shared<ClassStudentService>();
        auto result = service->getStudentCourseList(queryCopy);

        // PageDTO 使用 rows 成员
        if (!result || !result->rows || result->rows->size() == 0) {
            jvo->fail(emptyPageDto);
            return jvo;
        }

        jvo->success(result);
        return jvo;
    }
    catch (const std::exception& e) {
        jvo->fail(emptyPageDto);
        return jvo;
    }
}