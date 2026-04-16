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
#include "domain/dto/homework/homeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG3 ZH_WORDS_GETTER("homework.tag")
//作业模块控制器
class HomeworkController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(HomeworkController);

public:

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("homework.get_homework_page"), queryPage, HomeworkQuery, HomeworkPageJsonVO::Wrapper, API_TAG3);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/app/sCenter/homework/list", queryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, HomeworkQuery, queryParams); API_HANDLER_RESP_VO(execQueryPage(query)););

	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.get_homework_info"), queryDetail, HomeworkDetailJsonVO::Wrapper, API_TAG3,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("homework.field.id"), nullptr, true);
	);

	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/app/sCenter/homework/info", queryDetail, QUERY(UInt64, id), execQueryDetail(id));

	// 1.1 定义提交作业接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.submit"),
		querySubmit,
		HomeworkJsonVO::Wrapper,
		API_TAG3
	);

	// 1.2 定义提交作业接口处理/*"/app/sCenter/homework/saveRecord",
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/app/sCenter/homework/saveRecord",
		querySubmit,
		BODY_DTO(HomeworkSubmitDTO::Wrapper, dto),
		execQuerySubmit(dto)
	);

	// 2.1 定义删除作业接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("homework.delete"),
		queryDelete,
		HomeworkDeleteQuery,
		HomeworkDeleteJsonVO::Wrapper,
		API_TAG3
	);
	// 2.2 定义删除作业接口处理/*"/app/sCenter/homework/deleteRecord/{id}",
	API_HANDLER_ENDPOINT_OPTION_AUTH(
		API_M_DEL,
		"/app/sCenter/homework/deleteRecord/{id}",
		queryDelete,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, HomeworkDeleteQuery, queryParams);
	API_HANDLER_RESP_VO(execQueryDelete(query));
		);
private: // 定义接口执行函数
	HomeworkPageJsonVO::Wrapper execQueryPage(const HomeworkQuery::Wrapper& query);
	HomeworkDetailJsonVO::Wrapper execQueryDetail(const UInt64& id);
	HomeworkSubmitJsonVO::Wrapper execQuerySubmit(const HomeworkSubmitDTO::Wrapper& dto);
	HomeworkDeleteJsonVO::Wrapper execQueryDelete(const HomeworkDeleteQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORKCONTROLLER_H_