#pragma once

#ifndef _PARENTINFO_DAO_
#define _PARENTINFO_DAO_
#include "BaseDAO.h"
#include "domain/do/parent/ParentInfoDO.h"
#include "domain/dto/parent/ParentInfoDTO.h"
#include "domain/query/parent/ParentInfoQuery.h"

/*
* 家长信息操作类
*/
class ParentInfoDAO : public BaseDAO {
public:
	// 获取家长信息
	PtrParentInfoDO selectParentInfoById(const uint64_t& id);
	// 获取家长信息
	//PtrParentInfoDO getParentInfo();
	// 修改家长姓名
	std::string updateParentName(const std::string& newName);
	// 获取用户密码
	std::string getCurPassword();
	// 修改登录密码
	std::string updateLoginPassword(const std::string& password);
};

#endif // !_PARENTINFO_DAO_
