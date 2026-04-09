#pragma once

#include "domain/vo/BaseJsonVO.h"
#include "../../domain/dto/StudentRecord/StlistDTO.h"
#include "../../domain/vo/StudentRecord/StlistVO.h"
#include "../../domain/query/StudentRecord/StlistQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG1 ZH_WORDS_GETTER("stlist.controller.tag1")

class StlistController :public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(StlistController);
public:
	//定义查询接口描述
	ENDPOINT_INFO(querystList) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("stlist.controller.title"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(StlistPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG1);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("stlist.controller.name"), "li", false);
		API_DEF_ADD_QUERY_PARAMS(String, "mobile", ZH_WORDS_GETTER("stlist.controller.mobile"), "", false);
	}
	//定义查询接口处理
	ENDPOINT(API_M_GET, "/c7-workbench/Stlist", querystList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, StlistQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQuerySample(userQuery));
	}


private:
	// 3.3 演示分页查询数据
	StlistPageJsonVO::Wrapper execQuerySample(const StlistQuery::Wrapper& query);
};

#undef API_TAG1
#include OATPP_CODEGEN_END(ApiController)