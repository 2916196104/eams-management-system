#include "stdafx.h"
#include "Macros.h"
#include "ParentController.h"
#include "domain/vo/ParentVO.h"
#include "service/UsageGuideService.h"
using namespace std;

//执行获取说明列表所有信息的响应
UsageGuideJsonVO::Wrapper ParentController:: executeQueryAll(const ListQuery::Wrapper& query)
{
	auto vo = UsageGuideJsonVO::createShared();// 创建返回对象
	UsageGuideService service;
	auto listData = service.listAll(query);
	vo->success(listData);// 设置数据并标记为成功
	return vo;
}

//执行获取说明列表中，编号为id的数据的详细信息的响应
UsageDetailJsonVO::Wrapper ParentController::executeQueryOne(const String& id)
{
	auto vo = UsageDetailJsonVO::createShared();// 创建返回对象
	UsageGuideService service;
	auto pageData = service.getById(id);
	vo->success(pageData);// 设置数据并标记为成功
	return vo;
}

