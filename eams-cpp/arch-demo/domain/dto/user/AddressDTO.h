#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 11:00:34

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
#ifndef _ADDRESSDTO_H_
#define _ADDRESSDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 添加收货地址数据模型
 */
class AddressAddDTO : public oatpp::DTO
{
	DTO_INIT(AddressAddDTO, DTO);
	// 用户编号
	API_DTO_FIELD_REQUIRE(String, userId, ZH_WORDS_GETTER("user.field.id"), true);
	// 联系人
	API_DTO_FIELD_REQUIRE(String, contact, ZH_WORDS_GETTER("address.field.contact"), true);
	// 联系电话
	API_DTO_FIELD_REQUIRE(String, phone, ZH_WORDS_GETTER("address.field.phone"), true);
	// 省份
	API_DTO_FIELD_REQUIRE(String, province, ZH_WORDS_GETTER("address.field.province"), true);
	// 城市
	API_DTO_FIELD_REQUIRE(String, city, ZH_WORDS_GETTER("address.field.city"), true);
	// 区县
	API_DTO_FIELD_REQUIRE(String, country, ZH_WORDS_GETTER("address.field.country"), true);
	// 详细地址
	API_DTO_FIELD_REQUIRE(String, address, ZH_WORDS_GETTER("address.field.address"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("address.field.remark"));
};

/**
 * 收货地址数据模型
 */
class AddressDTO : public AddressAddDTO
{
	DTO_INIT(AddressDTO, AddressAddDTO);
	// 编号
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("address.field.id"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_ADDRESSDTO_H_