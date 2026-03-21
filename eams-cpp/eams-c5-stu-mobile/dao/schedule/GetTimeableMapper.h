#pragma once
#ifndef _GETTIMEABLE_MAPPER_
#define _GETTIMEABLE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/schedule/GetTimeableDO.h"

/**
 * 示例表字段匹配映射
 */
class GetTimeableMapper : public Mapper<GetTimeableDO>
{
public:
	GetTimeableDO mapper(ResultSet* resultSet) const override
	{
		GetTimeableDO data;
		data.setId(resultSet->getString(1));
		data.setDate(resultSet->getString(1));
		return data;
	}
};

///**
// * 示例表字段匹配映射-创建智能指针对象
// */
class PtrGetTimeableMapper : public Mapper<PtrGetTimeableDO>
{
public:
	PtrGetTimeableDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<GetTimeableDO>();
		data->setId(resultSet->getString(1));
		return data;
	}
};

#endif // !_GETTIMEABLE_MAPPER_