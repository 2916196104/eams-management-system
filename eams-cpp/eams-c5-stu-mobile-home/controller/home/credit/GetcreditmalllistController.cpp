#include "stdafx.h"
#include "GetcreditmalllistController.h"
#include "service/home/credit/GetCreditMallListService.h"



CreditMallListPageJsonVO::Wrapper GetCreditMallListController::executeQueryAll(const CreditMallListQuery::Wrapper& creditmallQuery)
{
	CreditMallListService cms;
	auto vo = CreditMallListPageJsonVO::createShared();
	vo->success(cms.listAll(creditmallQuery));
	return vo;
}