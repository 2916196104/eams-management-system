#pragma once

#include "../../domain/do/StudentRecord/stlist/StlistDO.h"
#include "Mapper.h"

class StlistViewMapper :public Mapper<StlistViewDO>
{
public:
	StlistViewDO mapper(ResultSet* res) const override
	{
		StlistViewDO data;
		//data.setId(res->getInt("id"));
		data.setName(res->getString("name")); // 姓名 (varchar(20))
		data.setGender(res->getInt("gender")); // 性别 (tinyint(2))
		data.setMobile(res->getString("mobile"));
		data.setCloseTime(res->getInt("close_time"));
		return data;
	}
};