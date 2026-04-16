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
#ifndef _REGISTRATIONCONTRULLER_H_
#define _REGISTRATIONCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/registration-records/registrationVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/registration-records/registrationquery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG_REGISTRATION ZH_WORDS_GETTER("registration-records.tag")
//报名记录模块控制器
class RegistrationRecodeController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(RegistrationRecodeController);
public: // 定义接口
	// 定义获取报名记录列表（条件+分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("registration-records.query-records.summary"),
		queryRecords,
		RegistrationRecordQuery,
		RegistrationRecordPageJsonVO::Wrapper,
		API_TAG_REGISTRATION
	);
	// 定义获取报名记录列表（条件+分页）接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"/app/sCenter/shop/courseInfo",
		queryRecords,
		RegistrationRecordQuery,
		execQueryRecords(query)
	);


private: // 定义接口执行函数
	RegistrationRecordPageJsonVO::Wrapper execQueryRecords(const RegistrationRecordQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_REGISTRATIONCONTROLLER_H_