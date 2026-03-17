#pragma once
#include <oatpp-swagger/model.hpp>
#ifndef COURSERECORDCONTROLLER_H
#define COURSERECORDCONTROLLER_H

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/*
	上课记录控制器
*/
class CourseRecordController : public oatpp::web::server::api::ApiController {
	// 定义控制器访问入口
	API_ACCESS_DECLARE(CourseRecordController);
public:// 定义接口
	ENDPOINT(API_M_GET, "/schedule", queryTest, QUERIES(QueryParams,params) ){
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