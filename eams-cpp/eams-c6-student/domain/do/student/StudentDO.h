#pragma once
#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_
#include "../DoInclude.h"
#include"BaseDO.h"
class UserDO : public BaseDO
{
	MYSQL_SYNTHESIZE(uint64_t, id, Id);//id` bigint unsigned NOT NULL COMMENT '用户主键',
	
	MYSQL_SYNTHESIZE(string, name, Name);//`name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '家长姓名',
	
	MYSQL_SYNTHESIZE(int, wx_access_id, Wx_access_id);//`wx_access_id` int DEFAULT NULL COMMENT '微信id',

	MYSQL_SYNTHESIZE(string, mobile, Mobile);//`mobile` varchar(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '手机号账号',

	MYSQL_SYNTHESIZE(string, email, Email);//`email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT 'email',

	MYSQL_SYNTHESIZE(int, state, State);	//`state` tinyint(1) DEFAULT '1' COMMENT '账号状态'
	
	MYSQL_SYNTHESIZE(string, password, Password);//`password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '密码',

	MYSQL_SYNTHESIZE(int, login_times, Login_times);//`login_times` int DEFAULT '0' COMMENT '登录次数',

	MYSQL_SYNTHESIZE(string, latest_login_time, Latest_login_time);//`latest_login_time` datetime DEFAULT NULL COMMENT '上次登录时间',

	MYSQL_SYNTHESIZE(string, latest_login_ip, Latest_login_ip);//`latest_login_ip` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '上次登录ip',

	MYSQL_SYNTHESIZE(string, add_time, Add_time);//`add_time` datetime DEFAULT NULL COMMENT '加入时间',

	MYSQL_SYNTHESIZE(string, remark, Remark);//`remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '备注',

	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);//`creator` bigint DEFAULT NULL COMMENT '添加者',

	MYSQL_SYNTHESIZE(uint64_t, school_id, School_id);//`school_id` bigint DEFAULT NULL COMMENT '所属学校id',

	MYSQL_SYNTHESIZE(uint64_t, org_id, Org_id);//`org_id` bigint DEFAULT NULL COMMENT '创建者所属组织ID',


public:
	UserDO() : BaseDO("user")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("wx_access_id", "i", wx_access_id);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("login_times", "i", login_times);
		MYSQL_ADD_FIELD("latest_login_time", "s", latest_login_time);
		MYSQL_ADD_FIELD("latest_login_ip", "s", latest_login_ip);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("school_id", "s", school_id);
		MYSQL_ADD_FIELD("org_id", "s", org_id);

	}
};
class ParentAccountQueryDO : public BaseDO
{
public:
	ParentAccountQueryDO() : BaseDO("parent_account")
	{
		MYSQL_ADD_FIELD_PK("user_id", "i", userId);
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
#endif