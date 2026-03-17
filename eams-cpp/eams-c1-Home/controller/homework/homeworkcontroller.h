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
#ifndef _HOMEWORKCONTROLLER_H_
#define _HOMEWORKCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/homework/homeworkVO.h"
#include "domain/query/homework/homeworkquery.h"


#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("homework.tag")
//作业模块控制器
class HomeworkController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(HomeworkController);
public: // 定义接口

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("homework.tag"), queryPage, HomeworkQuery, HomeworkPageJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c1/homework", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, HomeworkQuery, queryParams); API_HANDLER_RESP_VO(execQueryPage(query)););

	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.field.title"), queryDetail, HomeworkDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("homework.field.id"), nullptr, true);
	);

	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c1/homework/detail", queryDetail, QUERY(UInt64, id), execQueryDetail(id));
private: // 定义接口执行函数
	HomeworkPageJsonVO::Wrapper execQueryPage(const HomeworkQuery::Wrapper& query);
	HomeworkDetailJsonVO::Wrapper execQueryDetail(const UInt64& id);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORKCONTROLLER_H_