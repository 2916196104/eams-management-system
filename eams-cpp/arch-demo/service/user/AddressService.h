#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 16:14:42

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
#ifndef _ADDRESSSERVICE_H_
#define _ADDRESSSERVICE_H_
#include "domain/dto/user/AddressDTO.h"
/**
 * 收货地址业务逻辑处理类
 */
class AddressService
{
public:
	// 保存收货地址
	string saveAddress(const AddressAddDTO::Wrapper& dto);
};

#endif // !_ADDRESSSERVICE_H_