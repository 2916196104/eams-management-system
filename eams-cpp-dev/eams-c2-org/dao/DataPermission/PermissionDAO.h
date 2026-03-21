#pragma once

#include "BaseDAO.h"
#include "domain/do/datapermission/PermissionDO.h"
#include "../../service/datapermission/PermissionService.h"


/**
 * 周围数据权限相关操作
 */
class DataPermissionDAO : public BaseDAO
{
public:
	int deleteBypermissionId(const std::string& permissionid)
	{
		// 检测T是否继承自BaseDO
		static_assert(std::is_base_of<BaseDO, PermissionCustomDO>::value, "T must be derived from BaseDO");
		// 构建删除语句与参数
		PermissionCustomDO bd;
		std::ostringstream sql;
		sql << "DELETE FROM " << bd.getTable() << " WHERE " << "permission_id" << " = ?";
		// 执行删除
		return sqlSession->executeUpdate(sql.str(), "%s", permissionid);
	}
};