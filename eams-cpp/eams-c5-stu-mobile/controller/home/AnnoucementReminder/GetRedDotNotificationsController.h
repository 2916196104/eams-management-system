#pragma once
#ifndef GET_RED_DOT_NOTIFICATIONS_CONTROLLER_H_
#define GET_RED_DOT_NOTIFICATIONS_CONTROLLER_H_


#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include"ApiHelper.h"
#include"ServerInfo.h"
#include "Macros.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("Notifications.tag")

class NotificationsController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(NotificationsController);
public:
	ENDPOINT_INFO(Notifications) {
		info->summary = ZH_WORDS_GETTER("Notifications.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
	}
	ENDPOINT(API_M_GET, "/home/AnnouncementReminder", Notifications, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
			API_HANDLER_QUERY_PARAM(query, PageQuery, params);
			API_HANDLER_RESP_VO(executeGetNotifications(query));
		}
private:
	StringJsonVO::Wrapper executeGetNotifications(const PageQuery::Wrapper& query);
};
#include OATPP_CODEGEN_END(ApiController)


#endif