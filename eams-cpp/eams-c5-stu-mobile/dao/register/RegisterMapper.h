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
		bd.setMobile(res->getString("mobile"));
		bd.setName(res->getString("name"));
		bd.setPassword(res->getString("password"));
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
		bd->setMobile(res->getString("mobile"));
		bd->setName(res->getString("name"));
		bd->setPassword(res->getString("password"));
		return bd;
	}
};
#endif