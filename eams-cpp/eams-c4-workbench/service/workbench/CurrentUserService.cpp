#include "stdafx.h"
#include "CurrentUserService.h"

CurrentUserInfoDTO::Wrapper CurrentUserService::getCurrentUserInfo(const std::shared_ptr<CustomerAuthorizeObject>& authObject)
{
	auto dto = CurrentUserInfoDTO::createShared();
	if (!authObject) {
		return dto;
	}
	const auto& payload = authObject->getPayload();
	dto->id = payload.getId().c_str();
	dto->username = payload.getUsername().c_str();
	for (const auto& one : payload.getAuthorities()) {
		dto->authorities->push_back(one.c_str());
	}
	return dto;
}
