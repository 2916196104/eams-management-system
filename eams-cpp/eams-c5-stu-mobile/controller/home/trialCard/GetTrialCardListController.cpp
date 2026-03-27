#include "stdafx.h"
#include "GetTrialCardListController.h"
#include "service/home/trialCard/GetTrialCardListService.h"

GetTrialCardListPageJsonVO::Wrapper GetTrialCardListController::executeGetCardList(const GetTrialCardListQuery::Wrapper& query)
{
	auto res = GetTrialCardListService().listAll(query);

	auto jvo = GetTrialCardListPageJsonVO::createShared();
	jvo->success(res);
	return jvo;
}