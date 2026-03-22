#include "stdafx.h"
#include "StudentController.h"
#include "service/Student/StudentService.h"

StudentPageJsonVO::Wrapper StudentController::executeQueryAll(const StudentQuery::Wrapper& query)
{
	StudentService us;//实例化服务层
	auto vo = StudentPageJsonVO::createShared();//创建响应VO
	vo->success(us.listAll(query));//调用服务层listAll方法，封装成功响应
	return vo;
}
