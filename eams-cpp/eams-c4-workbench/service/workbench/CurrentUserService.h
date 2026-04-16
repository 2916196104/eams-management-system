#pragma once
#ifndef _CURRENT_USER_SERVICE_H_
#define _CURRENT_USER_SERVICE_H_

#include "CustomerAuthorizeHandler.h"
#include "domain/dto/workbench/CurrentUserDTO.h"

class CurrentUserService
{
public:
	CurrentUserInfoDTO::Wrapper getCurrentUserInfo(const std::shared_ptr<CustomerAuthorizeObject>& authObject);
};

#endif
