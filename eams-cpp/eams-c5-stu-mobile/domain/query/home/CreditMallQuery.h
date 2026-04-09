#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/18 22:00:00

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
#ifndef _CREDIT_MALL_QUERY_
#define _CREDIT_MALL_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 积分商城礼品分页查询对象
 * 支持按学校ID、物料ID、分类ID、分类名称、礼品名称等条件分页查询
 */
class CreditMallQuery : public PageQuery
{
	DTO_INIT(CreditMallQuery, PageQuery);

	// 所属学校ID
	DTO_FIELD(UInt64, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.school_id");
	}

	// 物料分类ID
	DTO_FIELD(UInt64, material_id);
	DTO_FIELD_INFO(material_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.material_id");
	}

	// 礼品分类ID
	DTO_FIELD(UInt64, category_id);
	DTO_FIELD_INFO(category_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.category_id");
	}

	// 分类名称（支持模糊查询）
	DTO_FIELD(String, category_name);
	DTO_FIELD_INFO(category_name) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.category_name");
	}

	// 礼品名称（支持模糊查询）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.name");
	}

	// 是否可兑换（1-可兑换，0-不可兑换）
	DTO_FIELD(Boolean, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.state");
	}

	// 删除标记（0-未删除，1-已删除，默认查询未删除）
	DTO_FIELD(Boolean, deleted);
	DTO_FIELD_INFO(deleted) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.deleted");
	}

	// 创建者所属组织ID
	DTO_FIELD(Int64, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("credit_mall.field.org_id");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CREDIT_MALL_QUERY_