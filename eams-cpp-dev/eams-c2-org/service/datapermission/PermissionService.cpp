#include "PermissionService.h"
#include "stdafx.h"
#include "domain/do/datapermission/PermissionDO.h"




UInt64 DataPermissionService::savePermission(const PositionDataDTO::Wrapper& dto)
{
	PermissionDO data; int res1, res2 = 0;
	
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		PositionId, position_Id,
		ScopeType, scopeType,
		EntityName, entityName,
		OwnerField, ownerField,
		Info, info,
		OwnerOrgField, ownerOrgField
	);
	
	DataPermissionDAO dao;

	if (!dto->id) //id为空，则根据雪花id生成器生成唯一id	, 执行新增逻辑
	{
		SnowFlake sf(1, 1);
		data.setId(dto->id = sf.nextId());
		(res1 = dao.insert(data)) && (dto->scopeType == 10) && (res2 = savecustompermission(dto, std::move(sf), dao));
		dto->id = nullptr;
	}
	else // 执行修改逻辑
	{
		data.setId(dto->id.getValue({}));
		auto session = dao.getSqlSession();
		res1 = dao.update(data); //data_permission修改成功
		
		session->beginTransaction();

		int cnt = dto->orgIds.get()->size(); // 需要改变的自定义数据权限行数

		dao.deleteBypermissionId(std::to_string(data.getId())); // 先删除原先的自定义数据权限

		((dto->scopeType == 10) && (res2 = savecustompermission(dto, SnowFlake(1, 1), dao))); // 再插入现在的自定义数据权限
		if (dto->scopeType == 10 && res2 != cnt)
			session->rollbackTransaction();
		else
			session->commitTransaction();
		
	}
	if (res1 || (dto->scopeType == 10 && res2 == dto->orgIds.get()->size())) 
		return UInt64(data.getId());
	return UInt64(nullptr);
}

int DataPermissionService::deletePermissions(const List<UInt64>& ids)
{
	// 创建DAO执行该批量删除
	DataPermissionDAO dao;

	std::list<string> idl;
	for (auto& val : *ids.get())
	{
		idl.push_back(std::to_string(val.getValue({})));
		dao.deleteBypermissionId(std::to_string(val)); // 同时删除这些permission_id对应在data_permission_custom中的记录
	}

	

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

int DataPermissionService::savecustompermission(const PositionDataDTO::Wrapper& dto, SnowFlake&& sf, DataPermissionDAO& dao)
{
	list<PermissionCustomDO> dol;
	for (auto& orgid : *dto->orgIds.get())
	{
		auto& data = dol.emplace_back(); //原地默认构造后再拿着引用设置值
		data.setId(sf.nextId());
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, PermissionId, id, PositionId, position_Id);
		data.setOrgId(orgid);
	}
	auto session = dao.getSqlSession();
	
	session->beginTransaction();
	
	int res = dao.insertBatch(dol);
	
	if (res != dto->orgIds.get()->size())
		session->rollbackTransaction();
	else
		session->commitTransaction();

	return res;
}
