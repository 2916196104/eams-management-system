#pragma once

#include "domain/dto/postion/PositionDataDTO.h"
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
};