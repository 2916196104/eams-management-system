#include "stdafx.h"
#include "GetClassStudentDetailsController.h"
#include "service/ClassStudentService.h"
#include <iostream>  // 添加这行

StudentDetailJsonVO::Wrapper GetClassStudentDetailsController::executeGetClassStudentDetails(
    const String& studentId,
    const PayloadDTO& payload)
{
    auto vo = StudentDetailJsonVO::createShared();

    // 调试输出
    std::cout << "=== GetClassStudentDetails START ===" << std::endl;
    std::cout << "studentId: " << (studentId ? studentId->c_str() : "NULL") << std::endl;

    // 参数校验
    if (!studentId || studentId->empty()) {
        std::cout << "ERROR: studentId is empty" << std::endl;
        auto dto = StudentDetailDTO::createShared();
        vo->fail(dto);
        return vo;
    }

    // 转换 studentId 为 UInt64
    UInt64 studentIdNum;
    try {
        studentIdNum = std::stoull(studentId->c_str());
        std::cout << "studentIdNum: " << studentIdNum << std::endl;
    }
    catch (...) {
        std::cout << "ERROR: Failed to parse studentId" << std::endl;
        auto dto = StudentDetailDTO::createShared();
        vo->fail(dto);
        return vo;
    }

    try {
        std::cout << "Creating service..." << std::endl;
        auto service = std::make_shared<ClassStudentService>();

        std::cout << "Calling getStudentDetail..." << std::endl;
        auto result = service->getStudentDetail(studentIdNum);

        std::cout << "getStudentDetail returned, result is " << (result ? "not null" : "null") << std::endl;

        if (!result || result->id == 0) {
            std::cout << "ERROR: Student not found for id: " << studentIdNum << std::endl;
            auto dto = StudentDetailDTO::createShared();
            vo->fail(dto);
            return vo;
        }

        std::cout << "SUCCESS! name: " << (result->name ? result->name->c_str() : "NULL") << std::endl;
        vo->success(result);
        return vo;
    }
    catch (const std::exception& e) {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
        auto dto = StudentDetailDTO::createShared();
        vo->fail(dto);
        return vo;
    }
}