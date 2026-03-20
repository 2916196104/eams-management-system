#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:34:14

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
#ifndef _MyCustomers_VO_
#define _MyCustomers_VO_

#include "../eams-c7-workbench/domain/GlobalInclude.h"
#include"../eams-c7-workbench/domain/dto/MyCustomers/MyCustomersDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 客户显示JsonVO，用于响应给客户端的Json对象（单个客户详情）
 */
class MyCustomersJsonVO : public JsonVO<MyCustomerDetailDTO::Wrapper> {
	DTO_INIT(MyCustomersJsonVO, JsonVO<MyCustomerDetailDTO::Wrapper>);
};

/**
 * 我的客户分页显示JsonVO，用于响应给客户端的Json对象（我的客户列表分页）
 */
class MyCustomersPageJsonVO : public JsonVO<MyCustomersPageDTO::Wrapper> {
	DTO_INIT(MyCustomersPageJsonVO, JsonVO<MyCustomersPageDTO::Wrapper>);
};
/**
 * 学生课程列表分页显示JsonVO，用于响应给客户端的Json对象（客户课程列表分页）
 */
class StudentCoursesPageJsonVO : public JsonVO<StudentCoursesPageDTO::Wrapper> {
	DTO_INIT(StudentCoursesPageJsonVO, JsonVO<StudentCoursesPageDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_MyCustomers_VO_