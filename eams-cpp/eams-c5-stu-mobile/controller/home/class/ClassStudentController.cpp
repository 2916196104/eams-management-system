#include "stdafx.h"
#include "ClassStudentController.h"       // 替换为ClassStudentController头文件
#include "../../../service/home/class/ClassStudentService.h"  // 替换为ClassStudentService头文件

// 方法适配：返回值/参数/服务调用全替换为ClassStudent相关
ClassStudentPageJsonVO::Wrapper ClassStudentController::executeQueryClassStudent(const ClassStudentQuery::Wrapper& query)
{
	// 调用ClassStudentService的listAll方法（适配class_student表查询）
	auto result = ClassStudentService().listAll(query);
	// 实例化ClassStudent分页VO（适配class_student表分页结果）
	auto jvo = ClassStudentPageJsonVO::createShared();

	// 封装成功响应（数据为class_student表的分页结果）
	jvo->success(result);
	return jvo;
}