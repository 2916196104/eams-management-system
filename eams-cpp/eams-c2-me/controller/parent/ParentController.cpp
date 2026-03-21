#include "stdafx.h"
#include "Macros.h"
#include "ParentController.h"
#include "domain/vo/ParentVO.h"
#include "service/UsageGuideService.h"
using namespace std;

UsageGuideJsonVO::Wrapper ParentController:: executeQueryAll(const ListQuery::Wrapper& query)
{
	auto vo = UsageGuideJsonVO::createShared();
	UsageGuideService service;
	auto listData = service.listAll(query);
	vo->success(listData);
	return vo;
}

UsageDetailJsonVO::Wrapper ParentController::executeQueryOne(const String& id)
{
	auto vo = UsageDetailJsonVO::createShared();
	UsageGuideService service;
	auto pageData = service.getById(id);
	vo->success(pageData);
	return vo;
}

