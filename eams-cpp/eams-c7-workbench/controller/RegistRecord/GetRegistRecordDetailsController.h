#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

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
#ifndef _GETREGISTRECORDDETAILSCONTROLLER_
#define _GETREGISTRECORDDETAILSCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/RegistRecord/RegistRecordQuery.h"
#include "domain/vo/RegistRecord/RegistRecordVO.h"
#include "service/RegistRecord/RegistRecordService.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class GetRegistRecordDetailsController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GetRegistRecordDetailsController);
public://定义接口
	ENDPOINT(API_M_GET, "/c7-workbench/RegistRecordDetails", querydetails, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, RegistRecordQuery, params);
		API_HANDLER_RESP_VO(execQueryById(query->id));
	}

	ENDPOINT_INFO(querydetails) {
		info->summary = ZH_WORDS_GETTER("translation.RegistRecordDetails");
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("translation.id"), "", true);
		
		//支持授权
		API_DEF_ADD_AUTH();
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON(RegistRecordJsonVO::Wrapper);
		//定义请求参数格式
		API_DEF_ADD_PAGE_PARAMS();
	}
private://定义执行函数
	RegistRecordJsonVO::Wrapper execQueryById(const String& id);
};




#include OATPP_CODEGEN_END(ApiController) //<- End Codegen




#endif // _USERCONTROLLER_H_
