#pragma once
#ifndef LISTEN_CARD_RULERS_CONTROLLER_H
#define  LISTEN_CARD_RULERS_CONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include"ApiHelper.h"
#include"ServerInfo.h"
#include "Macros.h"
#include"../../../domain/vo/home/ListenCard/ListenCardRulesVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("ListenCardRules.tag")
class ListenCardRulesController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(ListenCardRulesController);
public:
	ENDPOINT_INFO(Rules) {
		info->summary = ZH_WORDS_GETTER("ListenCardRules.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(ListenCardRulesJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(Int64, "CourseId", ZH_WORDS_GETTER("ListenCardRules.field.course_id"), 1, true);
		API_DEF_ADD_QUERY_PARAMS(String, "CourseTitle", ZH_WORDS_GETTER("ListenCardRules.field.title"), "English", true);
	}
	ENDPOINT(API_M_GET, "/c5/home/trialCard/rule", Rules, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		API_HANDLER_RESP_VO(executeGetRules(query));
	}
private:
	StringJsonVO::Wrapper executeGetRules(const PageQuery::Wrapper& query);
};
#include OATPP_CODEGEN_END(ApiController)


#endif 
