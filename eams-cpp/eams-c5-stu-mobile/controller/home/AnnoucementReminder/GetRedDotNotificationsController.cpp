#include"stdafx.h"
#include"GetRedDotNotificationsController.h"
StringJsonVO::Wrapper NotificationsController::executeGetNotifications(const PageQuery::Wrapper& query){
	//创建一个响应结果
	auto vo{ StringJsonVO::createShared() };
	vo->success(ZH_WORDS_GETTER("Notifications.resp"));
	return vo;
}

