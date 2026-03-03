#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/31 15:10:35

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
#ifndef _ADDRESSMAPPER_H_
#define _ADDRESSMAPPER_H_
#include "Mapper.h"
#include "domain/do/user/AddressDO.h"

class AddressMapper : public Mapper<PtrAddressDO>
{
public:
	PtrAddressDO mapper(ResultSet* resultSet) const override
	{
		PtrAddressDO addressDO = std::make_shared<AddressDO>();
		addressDO->setId(resultSet->getString("id"));
		addressDO->setUserId(resultSet->getString("user_id"));
		addressDO->setContact(resultSet->getString("contact"));
		addressDO->setPhone(resultSet->getString("phone"));
		addressDO->setProvince(resultSet->getString("province"));
		addressDO->setCity(resultSet->getString("city"));
		addressDO->setCountry(resultSet->getString("country"));
		addressDO->setAddress(resultSet->getString("address"));
		addressDO->setRemark(resultSet->getString("remark"));
		return addressDO;
	}
};

#endif // !_ADDRESSMAPPER_H_