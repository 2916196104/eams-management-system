#pragma once

#ifndef _USERPROFILEMAPPER_H_
#define _USERPROFILEMAPPER_H_

#include "Mapper.h"
#include "domain/do/UserRelated/UserRelatedDO.h"

class UserProfileMapper : public Mapper<PtrUserRelatedDO>
{
public:
	PtrUserRelatedDO mapper(ResultSet* resultSet) const override
	{
		PtrUserRelatedDO userProfile = std::make_shared<UserRelatedDO>(); //创建一个新的UserRelatedDO对象
		userProfile->setId(resultSet->getInt64("id"));
		userProfile->setName(resultSet->getString("name"));
		userProfile->setMobile(resultSet->getString("mobile"));
		userProfile->setGender(resultSet->getInt("gender"));
		userProfile->setBirthday(resultSet->getString("birthday"));
		userProfile->setHeadImg(resultSet->getString("head_img"));
		return userProfile;
	}
};

#endif // !_USERPROFILEMAPPER_H_

