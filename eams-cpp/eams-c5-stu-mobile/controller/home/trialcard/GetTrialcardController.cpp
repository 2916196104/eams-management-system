#include "stdafx.h"
#include "GetTrialcardController.h"
GetTrialcardJsonVO::Wrapper GetTrialcardController::executeQueryGetTrialcardQuery(const GetTrialcardQuery::Wrapper& query) {
	auto jvo = GetTrialcardJsonVO::createShared();
	return jvo;
}