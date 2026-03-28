#pragma once

#ifndef _USERINGORMATION_H_
#define _USERINGORMATION_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/SysPermissionDO.h"

class PermissionDAO : public BaseDAO
{
public:
	//获取权限列表，通过用户id查询
	std::list <PtrSysPermissionDO> getPermissionsByUserId(long long  UserId);
};

#endif // !_USERINGORMATION_H_
