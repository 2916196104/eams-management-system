#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 14:45:11

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
#ifndef _ADDRESSDAO_H_
#define _ADDRESSDAO_H_
#include "BaseDAO.h"
#include "domain/do/user/AddressDO.h"

/**
 * 收货地址操作
 */
class AddressDAO : public BaseDAO
{
public:
	// 获取指定用户的收货地址
	list<PtrAddressDO> selectByUserId(string userId);
};

#endif // !_ADDRESSDAO_H_