
#include"stdafx.h"
#include"GettimeableController.h"
StringJsonVO::Wrapper GettimeableController::executequerytest(const PageQuery::Wrapper & query)
{
	//创建一个响应结果
	auto vo = StringJsonVO::createShared();
	vo->success("success");
	return vo;

}