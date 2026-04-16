#include"stdafx.h"
#include"UserInformationController.h"
#include "domain/vo/UserRelated/UserRelatedVO.h"
#include "service/UserRelated/UserInformationService.h"

UserRelatedVO::Wrapper GetUserInformationController::execQuaryUserInformation(const PayloadDTO& payload)
{
	//获取pyload中的用户唯一id
	auto userID = payload.getId();

	//根据用户id调用service层获取用户信息
	UserInformationService userInformationService;
	auto dto = userInformationService.getUserInformation(std::stoll(userID)); //返回一个UserInformationDTO对象


	//将service层返回的UserInformationDTO对象转换成UserRelatedVO对象
	auto userRelatedVO = UserRelatedVO::createShared();
	//将UserInformationDTO对象设置到UserRelatedVO的data字段中，并设置状态为成功
	userRelatedVO->success(dto);
	return userRelatedVO;
}