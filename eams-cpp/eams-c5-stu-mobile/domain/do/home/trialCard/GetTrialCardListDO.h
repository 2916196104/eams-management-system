#pragma once
#ifndef _GETTRIALCARDLIST_DO_H_
#define _GETTRIALCARDLIST_DO_H_
#include "../../DoInclude.h"

class GetTrialCardListDO : public BaseDO
{
	// 试用卡ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 试用卡名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 课程ID
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	// 试用卡启用状态
	MYSQL_SYNTHESIZE(bool, state, State);
	// 发行数量
	MYSQL_SYNTHESIZE(int, quantity, Quantity);
	// 剩余数量
	MYSQL_SYNTHESIZE(int, remainingQuantity, RemainingQuantity);
	// 课时数量
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 有效天数
	MYSQL_SYNTHESIZE(int, expireDays, ExpireDays);
	// 结束时间
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
public:
	GetTrialCardListDO() : BaseDO("course_trial")
	{
		// 这里的第一个参数必须是数据库真实的列名
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("title", "s", name);               
		MYSQL_ADD_FIELD("course_id", "s", courseName);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("quantity", "i", quantity);
		MYSQL_ADD_FIELD("remaining_quantity", "i", remainingQuantity);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("expire_days", "i", expireDays);
		MYSQL_ADD_FIELD("end_time", "s", endTime);
	}
};

typedef std::shared_ptr<GetTrialCardListDO> PtrGetTrialCardListDO;
#endif // _GETTRIALCARDLISTDO_H_