#pragma once
#ifndef _PARENT_ACCOUNT_DO_H_
#define _PARENT_ACCOUNT_DO_H_

#include "domain/do/DoInclude.h"

/**
 * 家长账号数据对象
 */
class ParentAccountDO : public BaseDO
{
public:
	ParentAccountDO() : BaseDO("parent_account")
	{
		MYSQL_ADD_FIELD_PK("user_id", "ull", userId);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		MYSQL_ADD_FIELD("wx_name", "s", wxName);
		MYSQL_ADD_FIELD("login_times", "i", loginTimes);
		MYSQL_ADD_FIELD("latest_login_time", "s", latestLoginTime);
		MYSQL_ADD_FIELD("latest_login_ip", "s", latestLoginIp);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("state", "i", state);
	}

	MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, wxName, WxName);
	MYSQL_SYNTHESIZE(int32_t, loginTimes, LoginTimes);
	MYSQL_SYNTHESIZE(string, latestLoginTime, LatestLoginTime);
	MYSQL_SYNTHESIZE(string, latestLoginIp, LatestLoginIp);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int32_t, state, State);
};

#endif // !_PARENT_ACCOUNT_DO_H_
