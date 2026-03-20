#pragma once
#pragma once
#ifndef _USETRIALCARD_CONTROLLER_H_
#define _USETRIALCARD_CONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/trial/UseTrialcardQuery.h"
#include "domain/dto/home/trial/UseTrialcardDTO.h"
#include "domain/vo/home/trial/UseTrialcardVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.home.trial.tag")
class UseTrialcardController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(UseTrialcardController);
public://定义接口
	//接口描述
	ENDPOINT_INFO(UseTrialcard) {
		info->summary = ZH_WORDS_GETTER("c5.home.trial.use-trial.summary");
		//支持授权
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON(UseTrialcardJsonVO::Wrapper);
		//定义请求参数格式
		API_DEF_ADD_QUERY_PARAMS(Int32, "course_id", ZH_WORDS_GETTER("c5.home.trial.get-field.course_id"), 1, true);
	}
	//接口端点,端点名称改为GetTrialcard
	ENDPOINT(API_M_GET, "/c5/home/trial/UseTrialcard", UseTrialcard, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		//查询参数绑定
		API_HANDLER_QUERY_PARAM(query, UseTrialcardQuery, params);
		API_HANDLER_RESP_VO(executeQueryUseTrialcardQuery(query));

	}
private:
	UseTrialcardJsonVO::Wrapper executeQueryUseTrialcardQuery(const UseTrialcardQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#endif