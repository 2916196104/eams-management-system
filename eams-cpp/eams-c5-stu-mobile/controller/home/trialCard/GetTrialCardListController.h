#pragma once
#ifndef _GETTRIALCARDCONTROLLER_
#define _GETTRIALCARDCONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/home/trialCard/GetTrialCardListVO.h"
#include "domain/query/home/trialCard/GetTrialCardListQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class GetTrialCardListController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetTrialCardListController);
public:
	ENDPOINT_INFO(getTrialCardList) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("home.trialCard.getTrialCardList.info"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(GetTrialCardListPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(ZH_WORDS_GETTER("home.trialCard.summary"));
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("student.id"), "", true);
	}
	ENDPOINT("GET", "/c5/home/trialCard/GetTrialCardList", getTrialCardList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, GetTrialCardListQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeGetCardList(userQuery));
	}
private:
	GetTrialCardListPageJsonVO::Wrapper executeGetCardList(const GetTrialCardListQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETTRIALCARDCONTROLLER_
