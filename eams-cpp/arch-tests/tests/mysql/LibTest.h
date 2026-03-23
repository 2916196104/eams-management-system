#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2024/04/08 11:30:59

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
#ifndef _LIB_TEST_
#define _LIB_TEST_
#include <string>
#include "Mapper.h"
#include "BaseDAO.h"

/**
 * 测试数据库查询的实体类
 */
class LibTest : public BaseDO
{
	MYSQL_SYNTHESIZE(int, id, Id);
	MYSQL_SYNTHESIZE(std::string, first, First);
	MYSQL_SYNTHESIZE(std::string, last, Last);
	MYSQL_SYNTHESIZE(int, age, Age);
public:
	LibTest() : BaseDO("lib_test")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD_NULLABLE("first", "s", first, false);
		MYSQL_ADD_FIELD("last", "s", last);
		MYSQL_ADD_FIELD("age", "i", age);
	}
};
using LibTestPtr = std::shared_ptr<LibTest>;

/**
 * 测试结果集匹配Mapper实现
 */
class LibTestMapper : public Mapper<LibTest>
{
public:
	LibTest mapper(ResultSet* resultSet) const override
	{
		LibTest p;
		p.setId(resultSet->getInt(1));
		p.setFirst(resultSet->getString(2));
		p.setLast(resultSet->getString(3));
		p.setAge(resultSet->getInt(4));
		return p;
	}
};

/**
 * 测试DAO1
 */
class LibTestDAO1 :public BaseDAO {};

/**
 * 测试DAO2
 */
class LibTestDAO2 :public BaseDAO {};

#endif // _LIB_TEST_
