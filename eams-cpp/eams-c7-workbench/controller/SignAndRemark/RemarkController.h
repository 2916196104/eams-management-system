#pragma once
#ifndef _REMARKCONTROLLER_H_
#define _REMARKCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/SignAndRemark/RemarkQuery.h"
#include "domain/dto/SignAndRemark/RemarkDTO.h"
#include "domain/vo/SignAndRemark/RemarkVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG2  ZH_WORDS_GETTER("remark.tag")

/*
* 评语控制器
*/
class RemarkController :public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(RemarkController);

public:	//定义接口
	// 3.1 定义获取点评列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("remark.query-remark-page.summary"), queryremarkPage, RemarkQuery, RemarkPageJsonVO::Wrapper, API_TAG2);

	// 3.2 定义获取点评列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/remark", queryremarkPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, RemarkQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryRemarkPage(query, authObject->getPayload()));
		);

private: //定义接口执行函数


	//3.3 定义获取点评列表接口执行函数
	RemarkPageJsonVO::Wrapper execQueryRemarkPage(const RemarkQuery::Wrapper& query, const PayloadDTO& payload);
};

#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController)

#endif