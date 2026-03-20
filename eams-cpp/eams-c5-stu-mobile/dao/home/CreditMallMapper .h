#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 10:30:00

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
#ifndef _CREDIT_MALL_MAPPER_
#define _CREDIT_MALL_MAPPER_

// 引入基础依赖
#include "Mapper.h"
#include "../../domain/do/home/CreditMallDO.h"

/**
 * 积分商城礼品表字段匹配映射器
 * 负责将数据库ResultSet结果集转换为CreditMallDO对象（值对象）
 */
class CreditMallMapper : public Mapper<CreditMallDO>
{
public:
	CreditMallDO mapper(ResultSet* resultSet) const override
	{
		CreditMallDO data;
		// 严格对应credit_mall表的字段顺序（需与SQL查询字段顺序一致）
		data.setId(resultSet->getString(1));          // 1: id（主键）
		data.setSchoolId(resultSet->getUInt64(2));    // 2: school_id
		data.setMaterialId(resultSet->getUInt64(3));  // 3: material_id
		data.setCategoryId(resultSet->getUInt64(4));  // 4: category_id
		data.setCategoryName(resultSet->getString(5));// 5: category_name
		data.setName(resultSet->getString(6));        // 6: name
		data.setCredit(resultSet->getInt(7));         // 7: credit（兑换积分）
		data.setState(resultSet->getInt(8));          // 8: state（状态）
		data.setSaleNum(resultSet->getInt(9));        // 9: sale_num（兑换数）
		data.setViewNum(resultSet->getInt(10));       // 10: view_num（预览数）
		data.setCover(resultSet->getString(11));      // 11: cover（封面）
		data.setContent(resultSet->getString(12));    // 12: content（详情）
		data.setCreator(resultSet->getString(13));    // 13: creator（创建人）
		data.setEditor(resultSet->getString(14));     // 14: editor（修改人）
		data.setAddTime(resultSet->getString(15));    // 15: add_time（创建时间）
		data.setEditTime(resultSet->getString(16));   // 16: edit_time（修改时间）
		data.setDeleted(resultSet->getInt(17));       // 17: deleted（删除标记）
		data.setOrgId(resultSet->getUInt64(18));      // 18: org_id（机构ID）
		return data;
	}
};

/**
 * 积分商城礼品表字段匹配映射器-智能指针版本
 * 负责将数据库ResultSet结果集转换为PtrCreditMallDO（智能指针对象）
 */
class PtrCreditMallMapper : public Mapper<PtrCreditMallDO>
{
public:
	PtrCreditMallDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<CreditMallDO>();
		// 字段顺序与CreditMallMapper完全一致
		data->setId(resultSet->getString(1));
		data->setSchoolId(resultSet->getUInt64(2));
		data->setMaterialId(resultSet->getUInt64(3));
		data->setCategoryId(resultSet->getUInt64(4));
		data->setCategoryName(resultSet->getString(5));
		data->setName(resultSet->getString(6));
		data->setCredit(resultSet->getInt(7));
		data->setState(resultSet->getInt(8));
		data->setSaleNum(resultSet->getInt(9));
		data->setViewNum(resultSet->getInt(10));
		data->setCover(resultSet->getString(11));
		data->setContent(resultSet->getString(12));
		data->setCreator(resultSet->getString(13));
		data->setEditor(resultSet->getString(14));
		data->setAddTime(resultSet->getString(15));
		data->setEditTime(resultSet->getString(16));
		data->setDeleted(resultSet->getInt(17));
		data->setOrgId(resultSet->getUInt64(18));
		return data;
	}
};

#endif // !_CREDIT_MALL_MAPPER_