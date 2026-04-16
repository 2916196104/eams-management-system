#pragma once
#ifndef _LOGINDAO_H_
#define _LOGINDAO_H_

#include "BaseDAO.h"
#include "domain/do/login/loginDO.h"

class LoginDAO : public BaseDAO
{
public:
	// 查看是否存在当前用户
	uint64_t count(const std::string& mobile);
	// 保存验证码
	bool saveCode(const std::string& key, const std::string& val, int expireSeconds);
	// 删除验证码
	bool deleteKey(const std::string& key);
	// 获取验证码
	std::string getValue(const std::string& key);
	// 修改密码
	bool updatePassword(const std::string& mobile, const std::string& email, const std::string& newPassword);
};

#endif // !_LOGINDAO_H_
