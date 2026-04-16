#include"stdafx.h"
#include"UserProfileController.h"
#include "service/UserRelated/UserProfileService.h"
#include "domain/vo/UserRelated/UserProfileVO.h"

UserProfileVO::Wrapper GetUserProfileController::execQuaryUserProfile(const PayloadDTO& payload)
{
	// 获取pyload中的用户唯一id
	auto userID = payload.getId();
	// 根据用户id调用service层获取用户资料
	UserProfileService userProfileService;
	auto dto = userProfileService.getUserProfile(std::stoll(userID)); // 返回一个UserProfileDTO对象
	// 将service层返回的UserInformationDTO对象转换成UserRelatedVO对象
	auto userProfileVO = UserProfileVO::createShared();
	// 将UserInformationDTO对象设置到UserRelatedVO的data字段中，并设置状态为成功
	userProfileVO->success(dto);
	return userProfileVO;
}