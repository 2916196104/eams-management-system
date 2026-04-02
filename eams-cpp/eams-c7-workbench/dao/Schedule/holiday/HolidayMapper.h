#pragma once
#ifndef _HOLIDAY_MAPPER_H_
#define _HOLIDAY_MAPPER_H_
#include "Mapper.h"
#include "domain/do/Schedule/holiday/HolidayDO.h"

class HolidayMapper : public Mapper<HolidayDO>
{
public:
	HolidayDO mapper(ResultSet* resultSet) const override
	{
		HolidayDO data;
		data.setId(resultSet->getInt64(1));
		data.setDate(resultSet->getString(2));
		data.setCreator(resultSet->getInt64(3));
		data.setAddTime(resultSet->getString(4));
		return data;
	}
};

class HolidayDateMapper : public Mapper<std::string>
{
public:
	std::string mapper(ResultSet* resultSet) const override
	{
		return resultSet->getString(1);
	}
};

#endif
