#pragma once

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/Homework/homeworklist/HomeworkListDTO.h"
#include "domain/query/Homework/homeworklist/HomeworkListQuery.h"
#include "domain/vo/Homework/homeworklist/HomeworkListVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG4 ZH_WORDS_GETTER("homeworklist.controller.tag4")
class HomeworkListController :public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(HomeworkListController);
public:
	ENDPOINT_INFO(queryHomeworkList) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("homeworklist.controller.title"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(HomeworkListPageJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG4);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
	}
	// 3.2 定义查询接口处理
	ENDPOINT(API_M_GET, "/c7-workbench/HomeworkList", queryHomeworkList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(userQuery, HomeworkListQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQuerySample(userQuery));
	}
private:
	HomeworkListPageJsonVO::Wrapper execQuerySample(const HomeworkListQuery::Wrapper& query);
};

#undef API_TAG4
#include OATPP_CODEGEN_END(ApiController)