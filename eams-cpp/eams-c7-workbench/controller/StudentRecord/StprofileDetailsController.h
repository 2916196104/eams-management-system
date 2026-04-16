#pragma once

#include "../../domain/query/StudentRecord/StlistQuery.h"
#include "../../domain/dto/StudentRecord/StprofileDetailsDTO.h"
#include "../../domain/vo/StudentRecord/StprofileDetailsVO.h"
#include "../../domain/query/StudentRecord/StprofileDetailsQuery.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG3 ZH_WORDS_GETTER("stprofiledetails.controller.tag3")
class StprofileDetailsController :public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(StprofileDetailsController);
public:
	ENDPOINT_INFO(queryStprofileDetails) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("stprofiledetails.controller.title"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(StprofileDetailsPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG3);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c7-workbench/StprofileDetails", queryStprofileDetails, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, StlistQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQuerySample(userQuery));
	}
private:
	StprofileDetailsPageJsonVO::Wrapper execQuerySample(const StlistQuery::Wrapper& query);
};

#undef API_TAG3
#include OATPP_CODEGEN_END(ApiController)