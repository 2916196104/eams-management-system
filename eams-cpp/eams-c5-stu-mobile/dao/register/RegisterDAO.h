#pragma once
#ifndef _REGISTER_DAO_H_
#define _REGISTER_DAO_H_
#include "BaseDAO.h"
#include "domain/do/register/RegisterDO.h"
#include "domain/query/register/RegisterQuery.h"

class RegisterDAO : public BaseDAO
{
public:
	// 插入数据,主键为自增
	//uint64_t insertAutoPk(const RegisterDO& bd);
	// 查询数据，根据主键查询
	PtrRegisterDO selectById(const std::string& id);
};

#endif