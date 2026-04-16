#pragma once

#ifndef _ROLEMAPPER_H_
#define _ROLEMAPPER_H_

#include "Mapper.h"
#include "domain/do/UserRelated/SysRoleDO.h"

class RoleMapper : public Mapper<PtrSysRoleDO>
{
public:
	PtrSysRoleDO mapper(ResultSet* resultSet) const override {
		PtrSysRoleDO role = std::make_shared<SysRoleDO>();
		//role->setId(resultSet->getInt("id"));
		//role->setName(resultSet->getString("name"));
		role->setCode(resultSet->getString("code"));
		return role;
	}
	
};

#endif // !_ROLEMAPPER_H_
