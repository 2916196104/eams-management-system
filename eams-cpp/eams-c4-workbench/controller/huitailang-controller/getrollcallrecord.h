#pragma once
#ifndef GETROLLCALLRECORD_H

#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include "../../domain/vo/huitailang-vo/rollcallvo.h"
#include "../../domain/query/huitailang-query/rollcallquery.h"
#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"

#define API_TAG ZH_WORDS_GETTER("rollcall.getrollrecord")
#include OATPP_CODEGEN_BEGIN(ApiController)

class getrollrecllrecord : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(getrollrecllrecord);
public: // 定义接口
	// 3.1 定义导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("rollcall.getrollrecord"), queryPage, RollcallQuery, RollCallJsonVO::Wrapper, API_TAG);
	
	// 3.2 定义导出接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "c4-workbench/getrollcallrecord", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, RollcallQuery, queryParams); API_HANDLER_RESP_VO(executeQueryRollCall(query)););
private: // 定义接口执行函数 执行函数的返回值是响应给前端的json函数
	//这里返回值stringJsonVo 也是在vo中定义了相应的头文件
	RollCallJsonVO::Wrapper executeQueryRollCall( const RollcallQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG
#endif // !GETROLLCALLRECORD_H