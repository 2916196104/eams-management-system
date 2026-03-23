#pragma once
#ifnef STUDENTDO_H
#define STUDENTDO_H 
#include "../DoInclude.h"
class StaffDO : public BaseDO {
public:
	// 职工id
	MYSQL_SYNTHESIZE(int, id, Id);
	// 职工姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 手机号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 微信登录id
	MYSQL_SYNTHESIZE(int, wxAccessId, WxAccessId);
	// email
	MYSQL_SYNTHESIZE(string, email, Email);
	//生日
    MYSQL_SYNTHESIZE(string, birthday, BirthDay);
	//性别
    MYSQL_SYNTHESIZE(int, sex, Sex);
	//身份证
    MYSQL_SYNTHESIZE(string, idCard, IdCard);
	//毕业学校
    MYSQL_SYNTHESIZE(string, school, School);
	//学历
    MYSQL_SYNTHESIZE(int, degree, Degree);
	//备注
    MYSQL_SYNTHESIZE(string, remark, Remark);
	//在职状态
    MYSQL_SYNTHESIZE(int, state, State);
	//是否是管理者
    MYSQL_SYNTHESIZE(int, isManager, IsManager);
	//头像
    MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	//入职日期
    MYSQL_SYNTHESIZE(string, hireDate, HireDate);

};






#endif