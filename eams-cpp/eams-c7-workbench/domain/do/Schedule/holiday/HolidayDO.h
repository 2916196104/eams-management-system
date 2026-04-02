#pragma once
#ifndef _HOLIDAY_DO_H_
#define _HOLIDAY_DO_H_
#include "../../DoInclude.h"

class HolidayDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	MYSQL_SYNTHESIZE(string, date, Date);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);

public:
	HolidayDO() : BaseDO("holiday")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("date", "s", date, false);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
	}
};

typedef std::shared_ptr<HolidayDO> PtrHolidayDO;
#endif
