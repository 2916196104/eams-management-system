#pragma once

#include "Mapper.h"
#include "domain/do/StudentRecord/stclassrecord/StclassRecordDO.h"

class StclassRecordViewMapper :public Mapper<StclassRecordViewDO>
{
public:
	StclassRecordViewDO mapper(ResultSet* res) const override
	{
		StclassRecordViewDO data;
		data.setTitle(res->getString("title")); // 课程标题
		data.setStartTime(res->getString("start_time")); // 开始时间
		data.setEndTime(res->getString("end_time")); // 结束时间
		data.setState(res->getInt("state")); // 课次状态
		data.setSignType(res->getInt("sign_type"));
		return data;
	}
};