#pragma once
#ifndef _SELECTCLASSMRAPPER_H_
#define _SELECTCLASSMRAPPER_H_
#include "Mapper.h"
#include "../../domain/do/Schedule/SelectClassDO.h"

class SelectClassWrapperPtr : public Mapper<SelectClassViewDOPtr>
{
public:
	SelectClassViewDOPtr mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SelectClassViewDO>();
		data->setId(resultSet->getDouble("id"));
		data->setName(resultSet->getString("name"));
		return data;
	}
};

#endif

