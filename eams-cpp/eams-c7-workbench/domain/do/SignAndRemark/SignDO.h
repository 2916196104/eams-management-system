#pragma once
#ifndef _SIGNDO_H_
#define _SIGNDO_H_

#include "../DoInclude.h"

class SignDO : public BaseDO
{
	//主键字段
	MYSQL_SYNTHESIZE(int, id, Id);
	//学生id
	MYSQL_SYNTHESIZE(int, stu_id, Stu_id);
	//学生签到情况
	MYSQL_SYNTHESIZE(string, sign, Sign);
	//学生签到事件
	MYSQL_SYNTHESIZE(string, date, Date);
	

public:
	SignDO() :BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("student_id", "i", stu_id);
		MYSQL_ADD_FIELD("sign_state", "s", sign);
		MYSQL_ADD_FIELD("sign_time", "s", date);
	}

};

//定义一个点名记录实体的智能指针
typedef std::shared_ptr<SignDO> PtrSignDO;

/**
 * 点名视图对象，关联一些外表的字段
 */
class SignViewDO :public SignDO
{
	//学生姓名
	MYSQL_SYNTHESIZE(string, stu_name, Stu_name);
};

typedef std::shared_ptr<SignViewDO> PtrSignViewDO;

#endif // !_SIGNDO_H_

