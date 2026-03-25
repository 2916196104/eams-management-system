#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

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
#ifndef _MYLISTENINGCARD_MAPPER_
#define _MYLISTENINGCARD_MAPPER_

#include "Mapper.h"
#include "../domain/do/cardDO.h"

/**
 * 示例表字段匹配映射
 */
class MyListeningCardMapper : public Mapper<cardDO>
{
public:
	cardDO mapper(ResultSet* resultSet) const override
	{
		cardDO data;
		data.setCourseId(resultSet->getInt(1));
		data.setTitle(resultSet->getString(2));
		data.setEndDate(resultSet->getString(3));
		data.setLessonCount(resultSet->getInt(4));
		data.setAddTime(resultSet->getString(3));
		return data;
	}
};

/**
 * 示例表字段匹配映射-创建智能指针对象
 */
class PtrMyListeningCardMapper : public Mapper<PtrCardDO>
{
public:
	PtrCardDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<cardDO>();
		data->setCourseId(resultSet->getInt(1));
		data->setTitle(resultSet->getString(2));
		data->setEndDate(resultSet->getString(3));
		data->setLessonCount(resultSet->getInt(4));
		data->setAddTime(resultSet->getString(3));
		return data;
	}
};

#endif // !_MYLISTENINGCARD_MAPPER_