#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/18 22:10:00

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
#ifndef _CREDIT_MALL_CONTROLLER_
#define _CREDIT_MALL_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/home/CreditMallQuery.h"
#include "domain/dto/home/credit_mallDTO.h"
#include "domain/vo/home/credit_mallVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("credit_mall.tags.t1")
#define API_TAG2 ZH_WORDS_GETTER("credit_mall.tags.t2")

/**
 * 积分商城礼品控制器
 * 提供积分商城礼品的增删改查、导入导出等接口
 * 区分：批量分页查询（school/material/category）、单ID精准查询
 */
class CreditMallController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(CreditMallController);
	// 3 定义接口
public:
	

	// ====================== 单ID精准查询（返回单条数据，无分页） ======================
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("credit_mall.query-by-id.summary"), queryCreditMallById, credit_mallVO::Wrapper, ZH_WORDS_GETTER("credit_mall.tags.t3"), // 单条VO（无分页）
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("credit_mall.field.id"), "", true); // id必传，唯一标识
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c5/home/credit-mall", queryCreditMallById, QUERY(String, id), execQueryCreditMallById(id));

	
private:
	// ====================== 单ID查询执行函数（返回单条数据） ======================
	credit_mallVO::Wrapper execQueryCreditMallById(const String& id); // 单条数据，无分页

};

#undef API_TAG
#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController)
#endif // _CREDIT_MALL_CONTROLLER_