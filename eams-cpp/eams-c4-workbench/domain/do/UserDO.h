#pragma once

#ifndef _USERDO_H_
#define _USERDO_H_

#include"DoInclude.h"

/*
	家长用户数据实体
*/
class UserDO :public BaseDO {
	//用户id主键
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	//家长姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	//微信id
	MYSQL_SYNTHESIZE(int, wx_access_id, Wx_access_id);
	//手机号账号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	//email
	MYSQL_SYNTHESIZE(string, email, Email);
	//账号状态
	MYSQL_SYNTHESIZE(int, state, State);
	//密码
	MYSQL_SYNTHESIZE(string, password, Password);
	//登陆次数
	MYSQL_SYNTHESIZE(int, login_times, Login_times);
	//上次登陆时间
	MYSQL_SYNTHESIZE(string, latest_login_time, Latest_login_time);
	//上次登陆ip
	MYSQL_SYNTHESIZE(string, latest_login_ip, Latest_login_ip);
	//加入时间
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	//备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//添加者
	MYSQL_SYNTHESIZE(string, creator, Creator);
	//所属学校id
	MYSQL_SYNTHESIZE(string, school_id, School_id);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(string, org_id, Org_id);

public:
	UserDO() : BaseDO("user") {
		//添加主键域
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("wx_access_id", "i", wx_access_id);
		MYSQL_ADD_FIELD_NULLABLE("mobile", "s", mobile,false);
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

//定义一个家长用户体的智能指针
typedef std::shared_ptr<UserDO> PtrUserDO;

#endif //!_USERDO_H_