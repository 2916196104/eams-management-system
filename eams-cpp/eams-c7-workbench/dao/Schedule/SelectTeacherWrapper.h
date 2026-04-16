#pragma once
#ifndef _SELECTTEACHERMRAPPER_H_
#define _SELECTTEACHERMRAPPER_H_
#include "Mapper.h"
#include "../../domain/do/Schedule/SelectTeacherDO.h"

class SelectTeacherWrapperPtr : public Mapper<SelectTeacherViewDOPtr>
{
public:
	SelectTeacherViewDOPtr mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SelectTeacherViewDO>();
		data->setId(resultSet->getDouble("id"));
		data->setName(resultSet->getString("name"));
		return data;
	}
};

#endif

