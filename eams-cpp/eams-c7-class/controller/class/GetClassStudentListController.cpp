#include "stdafx.h"
#include "GetClassStudentListController.h"
#include "service/ClassStudentService.h"

ClassStudentPageJsonVO::Wrapper GetClassStudentListController::executeGetClassStudentList(
    const ClassStudentListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    auto vo = ClassStudentPageJsonVO::createShared();

    // 参数校验
    if (!query || !query->classId || query->classId == 0) {
        auto emptyPageDto = ClassStudentPageDTO::createShared();
        vo->fail(emptyPageDto);
        return vo;
    }

    // 校正分页参数
    if (query->pageIndex < 1) query->pageIndex = 1;
    if (query->pageSize < 1) query->pageSize = 10;
    if (query->pageSize > 100) query->pageSize = 100;

    try {
        auto service = std::make_shared<ClassStudentService>();
        auto result = service->getClassStudentList(query);

        if (!result || result->total == 0) {
            auto emptyPageDto = ClassStudentPageDTO::createShared();
            vo->fail(emptyPageDto);
            return vo;
        }

        vo->success(result);
        return vo;
    }
    catch (const std::exception& e) {
        auto emptyPageDto = ClassStudentPageDTO::createShared();
        vo->fail(emptyPageDto);
        return vo;
    }
}