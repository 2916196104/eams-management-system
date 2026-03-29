#pragma once
#include "../DoInclude.h"

class ExcelUserDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(int, wxAccessId, WxAccessId);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, email, Email);
	MYSQL_SYNTHESIZE(int, state, State);
	MYSQL_SYNTHESIZE(string, password, Password);
	MYSQL_SYNTHESIZE(int, loginTimes, LoginTimes);
	MYSQL_SYNTHESIZE(string, latestLoginTime, LatestLoginTime);
	MYSQL_SYNTHESIZE(string, latestLoginIp, LatestLoginIp);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, creator, Creator);
	MYSQL_SYNTHESIZE(string, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(string, orgId, OrgId);

public:
	ExcelUserDO() : BaseDO("user")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("wx_access_id", "i", wxAccessId);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("login_times", "i", loginTimes);
		MYSQL_ADD_FIELD("latest_login_time", "s", latestLoginTime);
		MYSQL_ADD_FIELD("latest_login_ip", "s", latestLoginIp);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("school_id", "s", schoolId);
		MYSQL_ADD_FIELD("org_id", "s", orgId);
	}
};
typedef std::shared_ptr<ExcelUserDO> PtrExcelUserDO;