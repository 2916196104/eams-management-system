#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:59:38

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
#ifndef _USERRELATEDDTO_H_
#define _USERRELATEDDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 用户信息传输对象
*/
class UserRelatedDTO : public oatpp::DTO
{
	DTO_INIT(UserRelatedDTO, DTO);
	
	// 用户权限（用于按钮控制）
	API_DTO_FIELD_REQUIRE(List<String>, permissions, ZH_WORDS_GETTER("file.field.ft"),true);
	// 角色编码
	API_DTO_FIELD_REQUIRE(List<String>, role, ZH_WORDS_GETTER("file.field.ft"), true);
	//用户ID
	API_DTO_FIELD_REQUIRE(Int64, ID, ZH_WORDS_GETTER("user.field.id"), true);
	//用户姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("user.field.name"), true);
	//用户手机号
	API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("file.field.ft"), true);

public:

};

/*
* 用户资料传输对象
*/
class UserProfileDTO : public oatpp::DTO
{
	DTO_INIT(UserProfileDTO, DTO);
	//用户ID
	API_DTO_FIELD_REQUIRE(Int64, ID, ZH_WORDS_GETTER("user.field.id"), true);
	//用户姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("user.field.name"), true);
	//用户手机号
	API_DTO_FIELD_REQUIRE(String, mobile, ZH_WORDS_GETTER("user.field.mobile"), true);
	// 用户年龄
	API_DTO_FIELD_REQUIRE(Int64, age, ZH_WORDS_GETTER("user.field.age"), true);
	// 用户生日
	API_DTO_FIELD_REQUIRE(String, birthday, ZH_WORDS_GETTER("file.field.birthday"), true);
	// 用户性别
	API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("file.field.gender"), true);
	// 用户身份证
	API_DTO_FIELD_REQUIRE(String, idcard, ZH_WORDS_GETTER("file.field.idcard"), true);
	//毕业学校
	API_DTO_FIELD_REQUIRE(String, school, ZH_WORDS_GETTER("file.field.school"), true);
	//学历
	API_DTO_FIELD_REQUIRE(String, degree, ZH_WORDS_GETTER("file.field.degree"), true);
	//备注
	API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("file.field.remark"), true);
	//在职状态
	API_DTO_FIELD_REQUIRE(String, state, ZH_WORDS_GETTER("file.field.state"), true);
	//头像地址
	API_DTO_FIELD_REQUIRE(String, headimg, ZH_WORDS_GETTER("file.field.heading"), true);
	//入职时间
	API_DTO_FIELD_REQUIRE(String, hireDate, ZH_WORDS_GETTER("file.field.hireDate"), true);
	//离职时间
	API_DTO_FIELD_REQUIRE(String, fireDate, ZH_WORDS_GETTER("file.field.fireDate"), true);
	//是否在职
	API_DTO_FIELD_REQUIRE(Boolean, isInner, ZH_WORDS_GETTER("file.field.isInner"), true);
public:

};

/*
* 修改头像数据传输对象
*/
class ChangePictureDTO : public oatpp::DTO
{
	DTO_INIT(ChangePictureDTO, DTO);
	
	// 用户ID
	API_DTO_FIELD_REQUIRE(Int64, ID, ZH_WORDS_GETTER("user.field.id"), true);
	//用户姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("user.field.name"), true);

	// 头像地址
	API_DTO_FIELD_REQUIRE(String, head_img, ZH_WORDS_GETTER("file.field.ft"), true);

public:

};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_