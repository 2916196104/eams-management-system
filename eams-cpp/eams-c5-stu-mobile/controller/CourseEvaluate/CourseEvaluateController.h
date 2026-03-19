#pragma once
#include <oatpp-swagger/model.hpp>
#ifndef COURSEEVALUATECONTROLLER_H
#define COURSEEVALUATECONTROLLER_H

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/*
	上课记录控制器
*/
class CourseEvaluateController : public oatpp::web::server::api::ApiController {
	// 定义控制器访问入口
	API_ACCESS_DECLARE(CourseEvaluateController);
public:// 定义接口
	ENDPOINT_INFO(CourseRecord) {
		info->summary = ZH_WORDS_GETTER("CourseEvaluate.summary");
		//支持授权
		API_DEF_ADD_AUTH();

		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
	}

	ENDPOINT(API_M_GET, "/CourseEvaluate", CourseRecord, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		// 响应结果
		API_HANDLER_RESP_VO(ExecuteCourseTest(query));
		return createResponse(Status::CODE_200, "Hello World!");
	}
private:// 定义接口执行函数
	StringJsonVO::Wrapper ExecuteCourseTest(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif