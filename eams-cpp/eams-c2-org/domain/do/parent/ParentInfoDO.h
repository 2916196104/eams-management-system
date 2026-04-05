#pragma once
#ifndef _PARENTINFO_DO_
#define _PARENTINFO_DO_

/*
* @Auther : shuishouy 
* @Date: 2026/3/28 16:29
*/
#include "../../Macros.h"
#include "BaseDO.h"

/*
* @Auther : shuishouy
* @Date: 2026/3/28 16:32
* 家长信息数据
*/
class ParentInfoDO : public BaseDO {
  // 用户主键
  MYSQL_SYNTHESIZE(unsigned long, id, Id);
  // 家长姓名
  MYSQL_SYNTHESIZE(string, name, Name);
  // 微信id
  MYSQL_SYNTHESIZE(int, wx_access_id, Wx_access_id);
  // 手机号账号
  MYSQL_SYNTHESIZE(string, mobile, Mobile);
  // 账号状态
  MYSQL_SYNTHESIZE(bool, state, State);
  // 密码
  MYSQL_SYNTHESIZE(string, password, Password);

  // 关联一个文件实体，存储头像文件信息
  CC_SYNTHESIZE(PtrFileDO, file, File);

public:
  ParentInfoDO() : BaseDO("parent_user") {
	MYSQL_ADD_FIELD_PK("id", "s", id);
	MYSQL_ADD_FIELD("name", "s", name);
	MYSQL_ADD_FIELD("wx_access_id", "i", wx_access_id);
	MYSQL_ADD_FIELD("mobile", "s", mobile);
	MYSQL_ADD_FIELD("state", "b", state);
	MYSQL_ADD_FIELD("password", "s", password);
  }
};

// 定义一个用户实体的智能指针
typedef std::shared_ptr<ParentInfoDO> PtrParentInfoDO;


#endif // !_PARENTINFO_DO_

