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
#ifndef _GETCLASSDETAILSCONTROLLER_
#define _GETCLASSDETAILSCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/query/ClassQuery.h"
#include "domain/vo/ClassVO.h"
#include "../lib-oatpp/include/domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("class.tag")

//获取班级的controller
class GetClassController : public oatpp::web::server::api::ApiController
{
	// 添加访问定义
	API_ACCESS_DECLARE(GetClassController);
public:
	// 定义获取班级详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.query-classdetails.summary"), queryClassDetail, ClassListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "classname", ZH_WORDS_GETTER("class.field.classname"), "classname", false);
	);

	//定义获取班级详情接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7/class/byname", queryClassDetail, QUERY(String, classname), execQueryClassList(classname));

	// 定义获取班级列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("class.query-classlist.summary"), QueryPage, ClassQuery, ClassPageJsonVO::Wrapper, API_TAG);
	// 定义获取班级列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7/class", QueryPage, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, ClassQuery, queryParams); API_HANDLER_RESP_VO(execQueryPage(query)););
private:
	//定义获取班级详情接口执行函数
	ClassListJsonVO::Wrapper execQueryClassList(const oatpp::String& classname);
	//定义获取班级列表（条件+分页）接口执行函数
	ClassListJsonVO::Wrapper execQueryPage(const ClassQuery::Wrapper& query);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _GETCLASSDETAILSCONTROLLER_