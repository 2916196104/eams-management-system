#pragma once

#ifndef _USERPROFILEDAO_H_
#define _USERPROFILEDAO_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/UserRelatedDO.h"
#include "domain/dto/UserRelated/UserRelatedDTO.h"


class UserRelatedDAO : public BaseDAO
{
public:
	// 获取用户资料，根据用户ID获取
	PtrUserRelatedDO selectById(long long id);
	
	//更新用户头像
	bool updateHeadImg(long long userId, const std::string& headImgUrl);
};



#endif // !_USERPROFILEDAO_H_