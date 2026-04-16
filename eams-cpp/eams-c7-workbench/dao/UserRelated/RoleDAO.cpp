#include "stdafx.h"
#include "RoleDAO.h"
#include "RoleMapper.h"

std::list<PtrSysRoleDO> RoleDAO::getRolesByUserId(long long UserId) {
	string sql = "SELECT r.code FROM sys_role r "
		"JOIN sys_user_role ur ON r.id = ur.role_id "
		"WHERE ur.user_id = ?";
	//执行查询并映射结果
	auto result = sqlSession->executeQuery<PtrSysRoleDO>(sql, RoleMapper(), "%ll", UserId);
	return result;
}