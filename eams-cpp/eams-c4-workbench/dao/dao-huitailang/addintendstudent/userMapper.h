#pragma once
#ifndef USERMAPPER_H
#define USERMAPPER_H
#include "domain/do/UserDO.h"
class UserMapper : public Mapper<UserDO>
{
public:
	UserDO mapper(ResultSet* resultSet) const override
	{
		UserDO data;
		data.setId(resultSet->getUInt64(1));
		data.setMobile(resultSet->getString(2));
		return data;
	}
};


class PtrUserMapper : public Mapper<PtrUserDO>
{
public:
	PtrUserDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<UserDO>();
		data->setId(resultSet->getUInt64(1));
		data->setMobile(resultSet->getString(2));
		return data;
	}
};


#endif