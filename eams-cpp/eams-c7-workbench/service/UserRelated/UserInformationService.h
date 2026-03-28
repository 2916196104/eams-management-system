#pragma once

#ifndef _USERINFORMATIONSERVICE_H_
#define _USERINFORMATIONSERVICE_H_
#include "domain/dto/UserRelated/UserRelatedDTO.h"


/*
* 用于获取用户的信息，主要是登录用户的基本信息和权限信息，供前端页面展示和按钮权限控制使用
*/
class UserInformationService
{
public:
	// 获取用户信息
	UserInformationDTO::Wrapper getUserInformation(long long userId);

};

#endif // !_USERINFORMATIONSERVICE_H_
