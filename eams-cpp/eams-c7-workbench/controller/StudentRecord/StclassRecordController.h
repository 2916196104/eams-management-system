#pragma once

#include "domain/vo/BaseJsonVO.h"
#include "../../domain/query/StudentRecord/StlistQuery.h"
#include "../../domain/dto/StudentRecord/StclassRecordDTO.h"
#include "../../domain/query/StudentRecord/StclassRecordQuery.h"
#include "../../domain/vo/StudentRecord/StclassRecordVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG2 ZH_WORDS_GETTER("stclassrecord.controller.tag2")
class StclassRecordController :public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(StclassRecordController);
public:
	ENDPOINT_INFO(queryStclassRecord) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("stclassrecord.controller.title"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(StclassRecordPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG2);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c7-workbanch/StclassRecord", queryStclassRecord, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, StlistQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQuerySample(userQuery));
	}
private:
	StclassRecordPageJsonVO::Wrapper execQuerySample(const StlistQuery::Wrapper& query);
};

#undef API_TAG2
#include OATPP_CODEGEN_END(ApiController)