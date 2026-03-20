#include "stdafx.h"
#include "controller/parentaccount/ParentAccountController.h"
#include "service/parentaccount/ParentAccountService.h"

ParentAccountPageJsonVO::Wrapper ParentAccountController::execQueryParentAccount(const ParentAccountQuery::Wrapper& query)
{
	auto data = m_parentAccountService.listParentAccount(query);
	auto jvo = ParentAccountPageJsonVO::createShared();
	jvo->success(data);
	return jvo;
	//return {};
}
