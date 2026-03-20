#pragma once
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/SignAndRemark/SignQuery.h"
#include "domain/dto/SignAndRemark/SignDTO.h"
#include "domain/vo/SignAndRemark/SignVO.h"
#include "domain/query/homework/HomeworkQuery.h"
#include "domain/dto/homework/HomeworkDTO.h"
#include "domain/vo/homework/HomeworkVO.h"
#include "domain/query/SignAndRemark/RemarkQuery.h"
#include "domain/dto/SignAndRemark/RemarkDTO.h"
#include "domain/vo/SignAndRemark/RemarkVO.h"



#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG1  ZH_WORDS_GETTER("sign.tags.tag1")
#define API_TAG2  ZH_WORDS_GETTER("sign.tags.tag2")
#define API_TAG3  ZH_WORDS_GETTER("sign.tags.tag3")
/*
* 签到控制器
*/
class Controller:public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Controller);

public:	//定义接口
	
	// 3.1 定义获取点名列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("c7.query-sign-page.summary"), queryPage, SignQuery, SignPageJsonVO::Wrapper, API_TAG1);
	
	// 3.2 定义获取点名列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/sign", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, SignQuery, queryParams); 
	API_HANDLER_RESP_VO(execQuerySignPage(query));
		);
	
	// 3.1 定义获取作业列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("c7.query-homewk-page.summary"), queryhomwkPage, HomeworkQuery, HomeworkPageJsonVO::Wrapper, API_TAG2);

	// 3.2 定义获取作业列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/homework", queryhomwkPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, HomeworkQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryHomeworkPage(query));
		);

	// 3.1 定义获取点评列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("c7.query-remark-page.summary"), queryremarkPage, RemarkQuery, RemarkPageJsonVO::Wrapper, API_TAG3);

	// 3.2 定义获取点评列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/remark", queryremarkPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, RemarkQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryRemarkPage(query));
		);



private: //定义接口执行函数
	
	//3.3 定义获取签到列表接口执行函数
	SignListJsonVO::Wrapper execQuerySignPage(const SignQuery::Wrapper& query);
	
	//3.3 定义获取作业列表接口执行函数
	HomeworkListJsonVO::Wrapper execQueryHomeworkPage(const HomeworkQuery::Wrapper& query);

	//3.3 定义获取点评列表接口执行函数
	RemarkListJsonVO::Wrapper execQueryRemarkPage(const RemarkQuery::Wrapper& query);

};


#undef API_TAG1
#undef API_TAG2
#undef API_TAG3
#include OATPP_CODEGEN_END(ApiController)

#endif // !_CONTROLLER_H_

