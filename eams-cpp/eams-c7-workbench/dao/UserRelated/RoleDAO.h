#pragma once

#ifndef _ROLEDAO_H_
#define _ROLEDAO_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/SysRoleDO.h"

class RoleDAO : public BaseDAO
{
public:
	// 根据用户ID获取角色列表
	std::list<PtrSysRoleDO> getRolesByUserId(long long UserId);
};

#endif // !_ROLEDAO_H_
