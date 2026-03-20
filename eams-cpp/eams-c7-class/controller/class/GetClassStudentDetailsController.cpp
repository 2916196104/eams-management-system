#include "stdafx.h"
#include "GetClassStudentDetailsController.h"

StudentDetailJsonVO::Wrapper GetClassStudentDetailsController::executeGetClassStudentDetails(
    const String& studentId,
    const PayloadDTO& payload)
{
    // 创建响应VO
    auto vo = StudentDetailJsonVO::createShared();

    // TODO: 调用Service查询学员详情
    // auto result = StudentService::getStudentDetail(studentId, payload);

    // 返回空数据
    auto dto = StudentDetailDTO::createShared();
    vo->success(dto);

    return vo;
}