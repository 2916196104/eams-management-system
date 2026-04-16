#pragma once
#ifndef _LOGIN_DO_
#define _LOGIN_DO_ 

#include "../DoInclude.h"
#include <cstdint>  // 引入标准整数类型uint64_t/int64_t

class LoginDO : public BaseDO
{
	// id
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 微信id
	MYSQL_SYNTHESIZE(int, wxAccessId, WxAccessId);
	// 手机号账号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// email
	MYSQL_SYNTHESIZE(string, email, Email);
	// 账号状态
	MYSQL_SYNTHESIZE(int, state, State);
	// 密码
	MYSQL_SYNTHESIZE(string, password, Password);
	// 登录次数
	MYSQL_SYNTHESIZE(int, loginTimes, LoginTimes);
	// 上次登陆时间
	MYSQL_SYNTHESIZE(string, latestLoginTime, LatestLoginTime);
	// 上次登陆ip
	MYSQL_SYNTHESIZE(string, latestLoginIp, LatestLoginIp);
	// 加入时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 创建人
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 所属学校id
	MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
	// 创建者所属组织
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
	LoginDO() : BaseDO("user")
	{
		// 主键id
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		// 姓名
		MYSQL_ADD_FIELD("name", "s", name);
		// 微信
		MYSQL_ADD_FIELD("wx_access_id", "i", wxAccessId);
		// 手机号
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		// email
		MYSQL_ADD_FIELD("email", "s", email);
		// 账号状态
		MYSQL_ADD_FIELD("state", "i", state);
		// 密码
		MYSQL_ADD_FIELD("password", "s", password);
		// 登录次数
		MYSQL_ADD_FIELD("login_times", "i", loginTimes);
		// 上次登录时间
		MYSQL_ADD_FIELD("latest_login_time", "s", latestLoginTime);
		// 上次登录ip
		MYSQL_ADD_FIELD("latest_login_ip", "s", latestLoginIp);
		// 加入时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 备注
		MYSQL_ADD_FIELD("remark", "s", remark);
		// 创建人
		MYSQL_ADD_FIELD("creator", "ll", creator);
		// 所属学校id
		MYSQL_ADD_FIELD("school_id", "ll", schoolId);
		// 组织id
		MYSQL_ADD_FIELD("org_id", "ll", orgId);

	}
};

// 智能指针
typedef std::shared_ptr<LoginDO> PtrLoginDO;

#endif