#include "PermissionService.h"
#include "stdafx.h"
#include "id/SnowFlake.h"
#include "dao/DataPermission/PermissionDAO.h"
#include "domain/do/datapermission/PermissionDO.h"


UInt64 DataPermissionService::savePermission(const PositionDataDTO::Wrapper& dto)
{
	PermissionDO data; int res;

	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		PositionId, position_Id,
		ScopeType, scopeType,
		EntityName, entityName,
		OwnerField, ownerField,
		Info, info,
		OwnerOrgField, ownerOrgField
	);
	
	if (!dto->id) //id为空，则根据雪花id生成器生成唯一id	, 执行新增逻辑
	{
		data.setId(SnowFlake(2, 2).nextId());
		res = DataPermissionDAO().insert(data);
	}
	else // 执行修改逻辑
	{
		data.setId(dto->id.getValue({}));
		res = DataPermissionDAO().update(data);
	}
	if (res == 1)
		return UInt64(data.getId());
	return UInt64(nullptr);
}

int DataPermissionService::deletePermissions(const List<UInt64>& ids)
{
	std::list<string> idl;
	for (auto& val : *ids.get())
		idl.push_back(std::to_string(val.getValue({})));

	// 创建DAO执行该批量删除
	DataPermissionDAO dao;

	// 批量删除前开启事务，只要有一条没删除成功就回滚
	auto session = dao.getSqlSession();
	session->beginTransaction();

	// 执行批量删除
	int res = dao.deleteByIds<PermissionDO>(idl);
	
	if (res != ids->size()) //未全部成功删除，回滚
		session->rollbackTransaction();
	else // 全部成功删除，提交
		session->commitTransaction();

	return res; //返回事务中影响的行数
}
