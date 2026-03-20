#pragma once
#ifndef _REGISTER_SERVICE_H_
#define _REGISTER_SERVICE_H_

#include "domain/vo/register/RegisterVO.h"
#include "domain/dto/login/RegisterDTO.h"
#include "domain/query/register/RegisterQuery.h"

class RegisterService
{
public:
	// 通过id查找数据
	RegisterDTO::Wrapper getById(std::string id);
};

#endif