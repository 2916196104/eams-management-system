#pragma once
#include <oatpp-swagger/Controller.hpp>
#ifndef _H	OMEWORKCONTROLLER_H_
#define _HOMEWORKCONTROLLER_H_

#include "ApiHelper.h"
#include"ServerInfo.h"
#include"Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class HomeworkController : public oatpp::web::server::api::ApiController {
	//定义控制器访问入口
	API_ACCESS_DECLARE(HomeworkController);
public://定义接口
	ENDPOINT_INFO(queryHomework) {
		info->summary = ZH_WORDS_GETTER("homework.summary");
		//支持授权
		API_DEF_ADD_AUTH();
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO); 
		//API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("homework.id"), "0001", true);
		API_DEF_ADD_QUERY_PARAMS(String, "subject", ZH_WORDS_GETTER("homework.subject"), ZH_WORDS_GETTER("homework.example"), true);
	}

	ENDPOINT(API_M_GET, "/homework", queryHomework,QUERIES(QueryParams, params),API_HANDLER_AUTH_PARAME) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		//响应结果
		API_HANDLER_RESP_VO(executeQueryHomework(query));
		return createResponse(Status::CODE_200, "Hello World!");
	}
private://定义接口执行函数
	StringJsonVO::Wrapper executeQueryHomework(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif //!_HOMEWORKCONTROLLER_H_