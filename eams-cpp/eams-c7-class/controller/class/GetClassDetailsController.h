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
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("class.tag")

class GetClassDetailsController : public oatpp::web::server::api::ApiController
{
	// 添加访问定义
	API_ACCESS_DECLARE(GetClassDetailsController);
public:
	// 定义获取班级详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class.get-class-details.summary"),
		getClassDetails,
		ClassJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("class.field.id"), "sample_class_id", true);
	);

	// 定义获取班级详情接口端点
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/class/get-class-details/{id}",
		getClassDetails,
		PATH(String, id),
		executeGetClassDetails(id)
	);

private:
	// 获取班级详情
	ClassJsonVO::Wrapper executeGetClassDetails(const String& id);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _GETCLASSDETAILSCONTROLLER_