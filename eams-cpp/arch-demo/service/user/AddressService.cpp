/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 16:15:19

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
#include "stdafx.h"
#include "AddressService.h"
#include "id/UuidFacade.h"
#include "dao/user/AddressDAO.h"

string AddressService::saveAddress(const AddressAddDTO::Wrapper& dto)
{
	// 生成唯一ID
	UuidFacade uf;
	std::string id = uf.genUuid();

	// 构建插入数据对象
	AddressDO data;
	data.setId(id);
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		UserId, userId,
		Contact, contact,
		Phone, phone,
		Province, province,
		City, city,
		Country, country,
		Address, address,
		Remark, remark
	);

	// 插入数据
	auto res = AddressDAO().insert(data);
	if (res == 1) return id;
	return  "";
}
