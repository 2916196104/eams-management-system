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
#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"
#include "domain/vo/JsonVO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
// 1. 客户列表 DTO
class MyCustomersDTO : public oatpp::DTO
{
	DTO_INIT(MyCustomersDTO, DTO);

	// 客户姓名
	API_DTO_FIELD_DEFAULT(String, MyCustomersName, ZH_WORDS_GETTER("cus.field.name"));
	// 电话号码
	API_DTO_FIELD_DEFAULT(String, phoneNumber, ZH_WORDS_GETTER("cus.field.phoneNumber"));
};

// 2. 客户详情 DTO
class MyCustomerDetailDTO : public oatpp::DTO
{
	DTO_INIT(MyCustomerDetailDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, MyCustomersName, ZH_WORDS_GETTER("cus.field.name"));
	API_DTO_FIELD_DEFAULT(String, phoneNumber, ZH_WORDS_GETTER("cus.field.phoneNumber"));
	API_DTO_FIELD_DEFAULT(String, sex, ZH_WORDS_GETTER("cus.field.sex"));
	API_DTO_FIELD_DEFAULT(Int64, age, ZH_WORDS_GETTER("cus.field.age"));
	API_DTO_FIELD_DEFAULT(String, birth, ZH_WORDS_GETTER("cus.field.birth"));
	API_DTO_FIELD_DEFAULT(String, type, ZH_WORDS_GETTER("cus.field.type"));
	API_DTO_FIELD_DEFAULT(String, notes, ZH_WORDS_GETTER("cus.field.notes"));
};


// 3. 学员课程 DTO
class StudentCourseDTO : public oatpp::DTO
{
	DTO_INIT(StudentCourseDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("cus.course.field.courseName"));
	API_DTO_FIELD_DEFAULT(Int64, totalLessons, ZH_WORDS_GETTER("cus.course.field.totalLessons"));
	API_DTO_FIELD_DEFAULT(Int64, finishedLessons, ZH_WORDS_GETTER("cus.course.field.finishedLessons"));
	API_DTO_FIELD_DEFAULT(Int64, remainingLessons, ZH_WORDS_GETTER("cus.course.field.remainingLessons"));
	API_DTO_FIELD_DEFAULT(String, progress, ZH_WORDS_GETTER("cus.course.field.progress"));
	API_DTO_FIELD_DEFAULT(String, expireTime, ZH_WORDS_GETTER("cus.course.field.expireTime"));
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