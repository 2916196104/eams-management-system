#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 20:14:04

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
#ifndef _ADDRESSDO_H_
#define _ADDRESSDO_H_
#include "../DoInclude.h"
/**
 * 测试地址数据模型
 */
class AddressDO : public BaseDO
{
	// 唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 关联用户
	MYSQL_SYNTHESIZE(string, userId, UserId);
	// 联系人
	MYSQL_SYNTHESIZE(string, contact, Contact);
	// 联系电话
	MYSQL_SYNTHESIZE(string, phone, Phone);
	// 省份
	MYSQL_SYNTHESIZE(string, province, Province);
	// 城市
	MYSQL_SYNTHESIZE(string, city, City);
	// 区县
	MYSQL_SYNTHESIZE(string, country, Country);
	// 详细地址
	MYSQL_SYNTHESIZE(string, address, Address);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
public:
	AddressDO() : BaseDO("sample_address")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("user_id", "s", userId, false);
		MYSQL_ADD_FIELD_NULLABLE("contact", "s", contact, false);
		MYSQL_ADD_FIELD_NULLABLE("phone", "s", phone, false);
		MYSQL_ADD_FIELD_NULLABLE("province", "s", province, false);
		MYSQL_ADD_FIELD_NULLABLE("city", "s", city, false);
		MYSQL_ADD_FIELD_NULLABLE("country", "s", country, false);
		MYSQL_ADD_FIELD_NULLABLE("address", "s", address, false);
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<AddressDO> PtrAddressDO;

#endif // !_ADDRESSDO_H_