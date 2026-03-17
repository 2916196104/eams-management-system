#include"stdafx.h"
#include"GetClassDetailsController.h"
ClassJsonVO::Wrapper GetClassDetailsController::executeGetClassDetails(const String& id)
{
	// 创建响应VO
	auto vo = ClassJsonVO::createShared();
	// 暂返回空数据
	vo->fail({});

	return vo;
}