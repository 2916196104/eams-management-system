#pragma once
#ifndef STUDENTDO_H
#define STUDENTDO_H 
#include "../DoInclude.h"
class StaffDO : public BaseDO {
public:
	// 职工id
	MYSQL_SYNTHESIZE(long long, id, Id);
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
	//离职日期
	MYSQL_SYNTHESIZE(string, fireData, FireDate);
	//介绍
    MYSQL_SYNTHESIZE(string, introduction, Introduction);
	//创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	//编辑时间
    MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//创建人
    MYSQL_SYNTHESIZE(string, creator, Creator);
	//编辑人
    MYSQL_SYNTHESIZE(string, editor, Editor);
	//是否删除
    MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//密码
	MYSQL_SYNTHESIZE(string, password, Password);
	//课时费
    MYSQL_SYNTHESIZE(int, classFee, ClassFee);
	//助教费
    MYSQL_SYNTHESIZE(int, assistantFee, AssistantFee);
	//staff所属组织id
    MYSQL_SYNTHESIZE(long long, orgId, OrgId);
	//是否内部人员
    MYSQL_SYNTHESIZE(int, isInner, IsInner);
public:
	StaffDO() : BaseDO("staff")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "i", mobile);
		MYSQL_ADD_FIELD("wxAccessId", "i", wxAccessId);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("sex", "i", sex);
		MYSQL_ADD_FIELD("idCard", "s", idCard);
		MYSQL_ADD_FIELD("school", "s", school);
		MYSQL_ADD_FIELD("degree", "i", degree);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("isManager", "i", isManager);
		MYSQL_ADD_FIELD("headImg", "s", headImg);
		MYSQL_ADD_FIELD("hireData", "s", hireData);
        MYSQL_ADD_FIELD("fireData", "s", fireData);
        MYSQL_ADD_FIELD("introduction", "s", introduction);
        MYSQL_ADD_FIELD("addTime", "s", addTime);
        MYSQL_ADD_FIELD("editTime", "s", editTime);
        MYSQL_ADD_FIELD("creator", "s", creator);
        MYSQL_ADD_FIELD("editor", "s", editor);
        MYSQL_ADD_FIELD("deleted", "i", deleted);
        MYSQL_ADD_FIELD("password", "s", password);
        MYSQL_ADD_FIELD("classFee", "i", classFee);
        MYSQL_ADD_FIELD("assistantFee", "i", assistantFee);
        MYSQL_ADD_FIELD("orgId", "i", orgId);
        MYSQL_ADD_FIELD("isInner", "i", isInner);
	}
};
typedef std::shared_ptr<StaffDO> PtrStaffDO;

#endif