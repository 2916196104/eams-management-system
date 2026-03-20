#pragma once
#ifndef _GETTRIALCARD_CONTROLLER_H_
#define _GETTRIALCARD_CONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/trial/GetTrialcardQuery.h"
#include "domain/dto/home/trial/GetTrialcardDTO.h"
#include "domain/vo/home/trial/GetTrialcardVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.home.trial.tag")
class GetTrialcardController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GetTrialcardController);
public://定义接口
	//接口描述
	ENDPOINT_INFO(GetTrialcard) {
		info->summary = ZH_WORDS_GETTER("c5.home.trial.query-all.summary");
		//支持授权
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON(GetTrialcardJsonVO::Wrapper);
		//定义请求参数格式
		API_DEF_ADD_QUERY_PARAMS(Int32, "course_id", ZH_WORDS_GETTER("c5.home.trial.field.course_id"), 1, true);
	}
	//接口端点,端点名称改为GetTrialcard
	ENDPOINT(API_M_GET, "/c5/home/trial/GetTrialcard", GetTrialcard, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		//查询参数绑定
		API_HANDLER_QUERY_PARAM(query, GetTrialcardQuery, params);
		API_HANDLER_RESP_VO(executeQueryGetTrialcardQuery(query));

	}
private:
	GetTrialcardJsonVO::Wrapper executeQueryGetTrialcardQuery(const GetTrialcardQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#endif