#include "stdafx.h"
#include "UserInformationService.h"
#include "dao/UserRelated/UserProfileDAO.h"
#include "dao/UserRelated/RoleDAO.h"
#include "dao/UserRelated/PermissionDAO.h"

UserInformationDTO::Wrapper UserInformationService::getUserInformation(long long userId)
{
	// 创建一个UserInformationDTO对象
	UserInformationDTO::Wrapper userInfoDto = UserInformationDTO::createShared();
	// 获取用户基本信息
	UserRelatedDAO UserInformationDAO;
	auto userProfile = UserInformationDAO.selectById(userId);
	if (userProfile != nullptr) {
		userInfoDto->ID = userProfile->getId();                     
		userInfoDto->name = oatpp::String(userProfile->getName()); 
		userInfoDto->mobile = oatpp::String(userProfile->getMobile());
	}
	// 获取用户角色编码
	RoleDAO RoleDAO;
	auto roles = RoleDAO.getRolesByUserId(userId);
	//创建一个空的角色列表
	userInfoDto->role = oatpp::List<oatpp::String>::createShared();
	for (const auto& role : roles) {
		if (role) { // 确保 role 智能指针有效
			userInfoDto->role->push_back(oatpp::String(role->getCode()));
		}
	}
	// 获取用户权限信息
	PermissionDAO PermissionDAO;
	auto permissions = PermissionDAO.getPermissionsByUserId(userId);
	// 创建一个空的权限列表
	userInfoDto->permissions = oatpp::List<oatpp::String>::createShared();
	for (const auto& permission : permissions) {
		if (permission) { 
			userInfoDto->permissions->push_back(oatpp::String(permission->getCode()));
		}
	}
	return userInfoDto;
}
