#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 11:01:02

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
#ifndef _MyCustomersQuery_H_
#define _MyCustomersQuery_H_

#include "../eams-c7-workbench/domain/GlobalInclude.h"
#include "domain/query/MyCustomers/MyCustomersQuery.h"
#include "../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 客户查询对象
 */
class MyCustomersQuery : public PageQuery {
	DTO_INIT(MyCustomersQuery, PageQuery);

	// 客户姓名
	API_DTO_FIELD_DEFAULT(String, MyCustomersName, u8"客户姓名");

	// 电话号码
	API_DTO_FIELD_DEFAULT(String, phoneNumber, u8"电话号码");

};

#include OATPP_CODEGEN_END(DTO)
#endif // !_MyCustomersQuery_H_