#include "stdafx.h"
#include "ClassStudentController.h"       // 替换为ClassStudentController头文件
#include "../../../service/home/class/ClassStudentService.h"  // 替换为ClassStudentService头文件

// 方法适配：返回值/参数/服务调用全替换为ClassStudent相关
ClassStudentJsonVO::Wrapper ClassStudentController::executeQueryClassStudent(const ClassStudentQuery::Wrapper& query)
{
    auto result = ClassStudentService().listAll(query);
    auto jvo = ClassStudentJsonVO::createShared();
    jvo->success(result);
    return jvo;
}