#include "stdafx.h"
#include "UserProfileService.h"
#include "dao/UserRelated/UserProfileDAO.h"

// 辅助函数：将性别 int 转换为字符串
static oatpp::String genderToString(int gender) {
	switch (gender) {
	case 0: return "未知";
	case 1: return "男";
	case 2: return "女";
	default: return "";
	}
}
 
UserProfileDTO::Wrapper UserProfileService::getUserProfile(long long userId) {

	//创建一个UserProfileDTO对象
	UserProfileDTO::Wrapper userprofiledto = UserProfileDTO::createShared();
	//获取用户基本信息
	UserRelatedDAO UserProfileDAO;
	auto userProfile = UserProfileDAO.selectById(userId);

	if (userProfile) {
		//userprofiledto->ID = userProfile->getId();
		userprofiledto->name = oatpp::String(userProfile->getName());
		userprofiledto->mobile = oatpp::String(userProfile->getMobile());
		userprofiledto->birthday = oatpp::String(userProfile->getBirthday());
		userprofiledto->gender = genderToString(userProfile->getGender());
		userprofiledto->headimg = oatpp::String(userProfile->getHeadImg());
	}
	return userprofiledto;
}