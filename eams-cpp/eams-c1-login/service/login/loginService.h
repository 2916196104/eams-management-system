
#pragma once
#ifndef _LOGINSERVICE_H_
#define _LOGINSERVICE_H_

#include "domain/dto/login/AuthDTO.h"


class loginService
{
public:
	// 构建redis key
	std::string buildRedisKey(const std::string& mobile, const std::string& email);
	// 生成验证码
	std::string generateVerifyCode(int len);
	// 构建重置邮件内容
	std::string buildMailBody1(const std::string& code);
	// 构建注册邮件内容
	std::string buildMailBody2(const std::string& code);
	// 校验手机号和邮箱格式是否正确
	bool isValidMobileAndEmail(const std::string& mobile, const std::string& email);
	// 发送验证码
	SendResetCodeRespDTO::Wrapper sendResetCode(const SendResetCodeDTO::Wrapper& dto);
	// 修改密码
	UpdatePasswordRespDTO::Wrapper updatePassword(const UpdatePasswordDTO::Wrapper& dto);

	// 发送注册短信验证
	SendRegisterCodeRespDTO::Wrapper sendRegisterCode(const SendRegisterCodeDTO::Wrapper& dto);

    // 注册账号
	RegisterRespDTO::Wrapper saveAccount(const RegisterDTO::Wrapper& dto);

};




#endif // _LOGINSERVICE_H_
