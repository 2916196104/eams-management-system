
#pragma once
#ifndef USERDAO_H
#define USERDAO_H
#include "domain/do/UserDO.h"
#include "BaseDAO.h"
class UserDAO : public BaseDAO
{

public:
	//根据手机号查询用户id
	std::list<UserDO> QueryUid(std::string phone);
	

};

#endif




