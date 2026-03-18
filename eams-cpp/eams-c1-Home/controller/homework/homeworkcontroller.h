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
#ifndef _HOMEWORKCONTRULLER_H_
#define _HOMEWORKCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/dto/homework/homeworkDTO.h"
#include "domain/vo/homework/homeworkVO.h"

#define API_TAG ZH_WORDS_GETTER("home.homework.tag")

#include OATPP_CODEGEN_BEGIN(ApiController)
//作业模块控制器
class homeworkController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(homeworkController);

public:
	homeworkController(const std::shared_ptr<ObjectMapper>& objectMapper)
		: oatpp::web::server::api::ApiController(objectMapper)
	{}

public: // 定义接口

	// 1.1 定义提交作业接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.homework.submit"),
		homeworkSubmit,
		HomeworkJsonVO::Wrapper,
		API_TAG
	);

	// 1.2 定义提交作业接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/homework/submit",
		homeworkSubmit,
		BODY_DTO(oatpp::Object<HomeworkSubmitDTO>, request),
		execHomeworkSubmit(request)
	);

	// 2.1 定义删除作业接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.homework.delete"),
		homeworkDelete,
		HomeworkJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt32, "homeworkId", ZH_WORDS_GETTER("home.homework.whichId"), 1, true);
	);

	// 2.2 定义删除作业接口处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_DEL,
		"/homework/delete",
		homeworkDelete,
		QUERY(UInt32, homeworkId),
		execHomeworkDelete(homeworkId)
	);

private: // 定义接口执行函数

	HomeworkJsonVO::Wrapper homeworkController::execHomeworkSubmit(const oatpp::Object<HomeworkSubmitDTO>& request);
	HomeworkJsonVO::Wrapper homeworkController::execHomeworkDelete(const oatpp::Object<HomeworkDeleteDTO>& request);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORKCONTROLLER_H_