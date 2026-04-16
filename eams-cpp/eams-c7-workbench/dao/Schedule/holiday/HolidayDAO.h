#pragma once
#ifndef _HOLIDAY_DAO_H_
#define _HOLIDAY_DAO_H_
#include "BaseDAO.h"
#include "domain/do/Schedule/holiday/HolidayDO.h"

class HolidayDAO : public BaseDAO
{
public:
	std::list<std::string> selectDatesByRange(const std::string& startDate, const std::string& endDate);
};

#endif
