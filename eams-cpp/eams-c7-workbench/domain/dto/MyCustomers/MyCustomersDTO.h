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
#ifndef _MyCustomers_DTO_
#define _MyCustomers_DTO_
#include "../eams-c7-workbench/domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"
#include "domain/vo/JsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
// 1. 客户列表 DTO
class MyCustomersDTO : public oatpp::DTO
{
	DTO_INIT(MyCustomersDTO, DTO);

	// 客户姓名
	API_DTO_FIELD_DEFAULT(String, MyCustomersName, u8"姓名");
	// 电话号码
	API_DTO_FIELD_DEFAULT(String, phoneNumber, u8"电话号码");
};

// 2. 客户详情 DTO
class MyCustomerDetailDTO : public oatpp::DTO
{
	DTO_INIT(MyCustomerDetailDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, MyCustomersName, u8"姓名");
	API_DTO_FIELD_DEFAULT(String, phoneNumber, u8"电话号码");
	API_DTO_FIELD_DEFAULT(Boolean, sex, u8"性别");
	API_DTO_FIELD_DEFAULT(Int64, age, u8"年龄");
	API_DTO_FIELD_DEFAULT(String, birth, u8"生日");
	API_DTO_FIELD_DEFAULT(String, type, u8"类型");
	API_DTO_FIELD_DEFAULT(String, notes, u8"备注");
};


// 3. 学员课程 DTO
class StudentCourseDTO : public oatpp::DTO
{
	DTO_INIT(StudentCourseDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, courseName, u8"课程名称");
	API_DTO_FIELD_DEFAULT(String, totalHours, u8"总时长");
	API_DTO_FIELD_DEFAULT(String, usedHours, u8"已用时长");
	API_DTO_FIELD_DEFAULT(String, remainingHours, u8"剩余时长");
	API_DTO_FIELD_DEFAULT(String, expireTime, u8"到期时间");
};

// 分页 DTO（自动适配列表）
// 客户列表分页
class MyCustomersPageDTO : public PageDTO<MyCustomersDTO::Wrapper>
{
	DTO_INIT(MyCustomersPageDTO, PageDTO<MyCustomersDTO::Wrapper>);
};

// 学员课程列表分页
class StudentCoursesPageDTO : public PageDTO<StudentCourseDTO::Wrapper>
{
	DTO_INIT(StudentCoursesPageDTO, PageDTO<StudentCourseDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_MyCustomers_DTO_