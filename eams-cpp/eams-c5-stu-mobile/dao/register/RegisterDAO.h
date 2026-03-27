#pragma once
#ifndef _REGISTER_DAO_H_
#define _REGISTER_DAO_H_
#include "BaseDAO.h"
#include "domain/do/register/RegisterDO.h"
#include "domain/query/register/RegisterQuery.h"

class RegisterDAO : public BaseDAO
{
private:
	// 利用雪花算法生成唯一ID
	std::string generateSnowFlakeId();
	// 获取当前时间
	std::string getCurrentDateTime();
public:
	// 判断当前数据库中是否存在相同手机号的用户
	bool isMobileExist(const std::string& mobile);
	std::string insertUser(const PtrRegisterDO query);
};

#endif