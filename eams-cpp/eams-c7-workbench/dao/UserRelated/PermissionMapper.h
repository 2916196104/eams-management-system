#pragma once

#ifndef _USERINFORMATIONMAPPER_H_
#define _USERINFORMATIONMAPPER_H_

#include "Mapper.h"
#include "domain/do/UserRelated/SysPermissionDO.h"

class PermissionMapper : public Mapper<PtrSysPermissionDO>
{
public:
	PtrSysPermissionDO mapper(ResultSet* resultSet) const override
	{
		PtrSysPermissionDO permission = std::make_shared<SysPermissionDO>();
		/*permission->setId(resultSet->getInt("id"));
		permission->setName(resultSet->getString("name"));
		permission->setParentId(resultSet->getString("parent_id"));
		permission->setUrl(resultSet->getString("url"));*/
		permission->setCode(resultSet->getString("code"));
		/*permission->setPath(resultSet->getString("path"));
		permission->setEnabled(resultSet->getInt("enabled"));
		permission->setGroupName(resultSet->getString("group_name"));*/
		return permission;
	}
};

#endif // !_USERINFORMATIONMAPPER_H_
