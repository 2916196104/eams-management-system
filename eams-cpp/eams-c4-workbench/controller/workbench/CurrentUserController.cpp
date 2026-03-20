#include "stdafx.h"
#include "CurrentUserController.h"
#include "service/workbench/CurrentUserService.h"

CurrentUserInfoJsonVO::Wrapper CurrentUserController::execQueryCurrentUserInfo(const std::shared_ptr<CustomerAuthorizeObject>& authObject)
{
	CurrentUserService service;
	auto vo = CurrentUserInfoJsonVO::createShared();
	vo->success(service.getCurrentUserInfo(authObject));
	return vo;
}
