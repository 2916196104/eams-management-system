#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _TESTCONTROLLER_H_
#define _TESTCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class TestController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(TestController);
public: // 定义接口
	ENDPOINT_INFO(queryTest) {
		info->summary = ZH_WORDS_GETTER("test.summary");
		// 支持授权
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		//API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
		// 定义请求参数格式
		API_DEF_ADD_PAGE_PARAMS();
	}
	ENDPOINT(API_M_GET, "/test", queryTest, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数
		API_HANDLER_QUERY_PARAM(query, PageQuery, params);
		// 响应结果
		API_HANDLER_RESP_VO(executeQueryTest(query));
	}
private: // 定义接口执行函数
	StringJsonVO::Wrapper executeQueryTest(const PageQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_TESTCONTROLLER_H_