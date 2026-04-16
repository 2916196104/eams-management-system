#pragma once

#ifndef _PARENTDO_H_
#define _PARENTDO_H_

#include "BaseDO.h"
#include <memory>

class ParentInfoDO : public BaseDO {
	// id
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// name家长姓名
	MYSQL_SYNTHESIZE(std::string, name, Name);
	// mobile手机号账号
	MYSQL_SYNTHESIZE(std::string, mobile, Mobile);
	// state账号状态
	MYSQL_SYNTHESIZE(int, state, State);
	// password密码
	MYSQL_SYNTHESIZE(std::string, password, Password);
	// add_time加入时间
	MYSQL_SYNTHESIZE(std::string, datetime, Datetime);
	// 用户头像
	//MYSQL_SYNTHESIZE(string, avatar, Avatar);
	// 关联一个文件实体，存储头像文件信息
	//CC_SYNTHESIZE(PtrFileDO, file, File);
public:
	ParentInfoDO() : BaseDO("user") {
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "string", mobile);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("datetime", "s", datetime);
	}
};

// 定义一个家长用户实体的智能指针  -- 用于返回单条
typedef std::shared_ptr<ParentInfoDO> PtrParentInfoDO;

#endif // !_PARENTDO_H_
