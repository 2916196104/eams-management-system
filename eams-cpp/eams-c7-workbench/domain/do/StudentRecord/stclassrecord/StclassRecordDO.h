#pragma once

#include "../../DoInclude.h"

class StclassRecordDO :public BaseDO
{
	MYSQL_SYNTHESIZE(unsigned long long, id, Id); // 主键
	MYSQL_SYNTHESIZE(string, title, Title); // 课程标题
	MYSQL_SYNTHESIZE(string, startTime, StartTime); // 开始时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime); // 结束时间
	MYSQL_SYNTHESIZE(int, state, State); // 课次状态
public :
	StclassRecordDO() :BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id); // 主键
		MYSQL_ADD_FIELD("title", "s", title); // 课程标题
		MYSQL_ADD_FIELD("start_time", "dt", startTime); // 开始时间
		MYSQL_ADD_FIELD("end_time", "dt", endTime); // 结束时间
		MYSQL_ADD_FIELD("state", "i", state); // 课次状态
	}
};

//视图DO
class StclassRecordViewDO :public StclassRecordDO
{
	// 是否签到
	MYSQL_SYNTHESIZE(int, signType, SignType);
};

typedef std::shared_ptr<StclassRecordViewDO> PtrStclassRecordViewDO;