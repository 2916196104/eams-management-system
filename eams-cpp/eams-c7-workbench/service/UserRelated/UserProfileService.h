#pragma once

#ifndef _USERPROFILESERVICE_H_
#define _USERPROFILESERVICE_H_
#include "domain/dto/UserRelated/UserRelatedDTO.h"

class UserProfileService {
public:
	//获取用户资料，根据用户ID获取
	UserProfileDTO::Wrapper getUserProfile(long long userId);
};


#endif // !_USERPROFILESERVICE_H_
