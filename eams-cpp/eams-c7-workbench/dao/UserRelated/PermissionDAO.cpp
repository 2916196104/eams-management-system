#include "stdafx.h"
#include "PermissionDAO.h"
#include "PermissionMapper.h"

//通过用户id查询权限列表
std::list<PtrSysPermissionDO> PermissionDAO::getPermissionsByUserId(long long  UserId)
{
	//使用join一次性查询用户的权限列表，避免多次查询数据库
	string sql= "SELECT p.code FROM sys_permission p "
		"JOIN sys_role_permission rp ON p.id = rp.permission_id "
		"JOIN sys_user_role ur ON rp.role_id = ur.role_id "
		"WHERE ur.user_id = ?";
	
	//执行查询并映射结果
	auto result = sqlSession->executeQuery<PtrSysPermissionDO>(sql, PermissionMapper(), "%ll", UserId);
	
	return result;
}