#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/26 23:47:08

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
#ifndef _USERDTO_H_
#define _USERDTO_H_

#include "../../GlobalInclude.h"
#include "AddressDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个添加用户信息的数据传输模型
 */
class UserAddDTO : public oatpp::DTO
{
	DTO_INIT(UserAddDTO, DTO);
	// 昵称
	API_DTO_FIELD_DEFAULT(String, nickname, ZH_WORDS_GETTER("user.field.nickname"));
	// 年龄
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("user.field.age"));
	// 身份证号
	API_DTO_FIELD_DEFAULT(String, idCard, ZH_WORDS_GETTER("user.field.idCard"));
	// 头像ID
	API_DTO_FIELD_DEFAULT(String, avatar, ZH_WORDS_GETTER("user.field.avatar"));
};

/**
 * 定义一个完整用户信息的数据传输模型
 */
class UserDTO : public UserAddDTO
{
	DTO_INIT(UserDTO, UserAddDTO);
	// 用户ID
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("user.field.id"), true);
	// 头像地址
	API_DTO_FIELD_DEFAULT(String, avatarUrl, ZH_WORDS_GETTER("user.field.avatarUrl"));
};

/**
 * 定义一个用户详细信息数据传输模型
 */
class UserDetailDTO : public UserDTO
{
	DTO_INIT(UserDetailDTO, UserDTO);
	// 收货地址
	API_DTO_FIELD_DEFAULT(List<AddressDTO::Wrapper>, addresses, ZH_WORDS_GETTER("user.field.addresses"));
public:
	UserDetailDTO()
	{
		addresses = {};
	}
};

/**
 * 定义一个用户信息分页传输对象
 */
class UserPageDTO : public PageDTO<UserDTO::Wrapper>
{
	DTO_INIT(UserPageDTO, PageDTO<UserDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _USERDTO_H_