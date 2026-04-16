#pragma once
#ifndef _REGISTER_SERVICE_H_
#define _REGISTER_SERVICE_H_

#include "domain/dto/login/RegisterDTO.h"
#include "domain/query/register/RegisterQuery.h"

class RegisterService
{
private:
	// 加密密码
	std::string encrpyPassword(std::string password);
	// 校验手机号
	bool checkMobile(std::string mobile);
	// 校验密码
	bool checkPassword(std::string password);
	// 校验验证码
	bool checkVertificationCode(std::string vertificationCode);
public:
	std::string insert(const RegisterAddDTO::Wrapper dto);
	// 数据校验,如果有错误，返回错误提示
	std::string validate(const RegisterAddDTO::Wrapper dto);
};

#endif