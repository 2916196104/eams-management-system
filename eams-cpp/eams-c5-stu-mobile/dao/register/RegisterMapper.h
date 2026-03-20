#pragma once
#ifndef _REGISTERDAO_H_
#define _REGISTERDAO_H_

#include "Mapper.h"
#include "domain/do/register/RegisterDO.h"

/**
 * 用户表字段匹配映射
 */
class RegisterMapper : public Mapper<RegisterDO>
{
public:
	RegisterDO mapper(ResultSet* res) const override
	{
		RegisterDO bd;
		bd.setId(res->getString("id"));
		bd.setTelephoneNumber(res->getString("mobile"));
		bd.setName(res->getString("name"));
		bd.setPassword(res->getString("password"));
		bd.setStatus(res->getInt("state"));
		bd.setCreateBy(res->getString("creator"));
		bd.setCreateTime(res->getString("add_time"));
		bd.setLatestLoginTime(res->getString("latest_login_time"));
		bd.setLatestLoginIp(res->getString("latest_login_ip"));
		return bd;
	}
};

/**
 * 用户表字段匹配映射-创建智能指针对象
 */
class PtrRegisterMapper : public Mapper<PtrRegisterDO>
{
public:
	PtrRegisterDO mapper(ResultSet* res) const override
	{
		auto bd = std::make_shared<RegisterDO>();
		bd->setId(res->getString("id"));
		bd->setTelephoneNumber(res->getString("mobile"));
		bd->setName(res->getString("name"));
		bd->setPassword(res->getString("password"));
		bd->setStatus(res->getInt("state"));
		bd->setCreateBy(res->getString("creator"));
		bd->setCreateTime(res->getString("add_time"));
		bd->setLatestLoginTime(res->getString("latest_login_time"));
		bd->setLatestLoginIp(res->getString("latest_login_ip"));
		return bd;
	}
};
#endif