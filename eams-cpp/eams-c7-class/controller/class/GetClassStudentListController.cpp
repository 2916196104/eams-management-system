#include "stdafx.h"
#include "GetClassStudentListController.h"

ClassStudentPageJsonVO::Wrapper GetClassStudentListController::executeGetClassStudentList(
    const ClassStudentListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    // 创建响应VO
    auto vo = ClassStudentPageJsonVO::createShared();

    // TODO: 调用Service查询班级学员列表
    // auto result = ClassStudentService::getClassStudentList(query, payload);

    // 返回空数据
    auto pageDto = ClassStudentPageDTO::createShared();
    vo->success(pageDto);

    return vo;
}