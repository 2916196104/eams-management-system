#pragma once

#include "domain/dto/position/PositionDataDTO.h"
#include "id/SnowFlake.h"
#include "dao/DataPermission/PermissionDAO.h"
using namespace oatpp;

/**
 * 职位数据权限业务逻辑处理类
 */
class DataPermissionService
{
public:
	// 新增或者修改职位数据权限(只能单条)
	UInt64 savePermission(const PositionDataDTO::Wrapper& dto);
	// 删除职位数据权限(支持批量)
	int deletePermissions(const List<UInt64>& dto);
	// 批量新增/修改自定义数据权限
	int savecustompermission(const PositionDataDTO::Wrapper& dto, SnowFlake&& sf, DataPermissionDAO& dao);
};