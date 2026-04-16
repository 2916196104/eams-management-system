#pragma once
#ifndef _SIGNCONTROLLER_H_
#define _SIGNCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/SignAndRemark/SignQuery.h"
#include "domain/dto/SignAndRemark/SignDTO.h"
#include "domain/vo/SignAndRemark/SignVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG1  ZH_WORDS_GETTER("sign.tag")

/*
* 签到控制器
*/
class SignController :public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SignController);

public:	//定义接口

	// 3.1 定义获取点名列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("sign.query-sign-page.summary"), queryPage, SignQuery, SignPageJsonVO::Wrapper, API_TAG1);

	// 3.2 定义获取点名列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/sign", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, SignQuery, queryParams)
		API_HANDLER_RESP_VO(execQuerySignPage(query, authObject->getPayload()));
	);

private: //定义接口执行函数

	//3.3 定义获取签到列表接口执行函数
	SignPageJsonVO::Wrapper execQuerySignPage(const SignQuery::Wrapper& query, const PayloadDTO& payload);

};

#undef API_TAG1

#include OATPP_CODEGEN_END(ApiController)

#endif