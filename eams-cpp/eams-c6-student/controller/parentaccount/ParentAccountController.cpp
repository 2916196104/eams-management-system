#include "stdafx.h"
#include "ParentAccountController.h"

ParentAccountPageJsonVO::Wrapper ParentAccountController::execQueryParentAccount(const ParentAccountQuery::Wrapper& query)
{
	auto data = m_parentAccountService.listParentAccount(query);
	auto jvo = ParentAccountPageJsonVO::createShared();
	jvo->success(data);
	return jvo;
}

ParentAccountChangeJsonVO::Wrapper ParentAccountController::excuteParentAccountChange(const ParentAccountChangeDTO::Wrapper& dto) {
	return {};
}

ParentPasswordChangeJsonVO::Wrapper ParentAccountController::excuteParentPasswordChange(const ParentPasswordChangeDTO::Wrapper& dto)
{
	return {};
}
