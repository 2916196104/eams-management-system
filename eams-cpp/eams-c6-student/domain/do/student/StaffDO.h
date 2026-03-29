#pragma once
#include "../DoInclude.h"

class ExcelStaffDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, wxAccessId, WxAccessId);
	MYSQL_SYNTHESIZE(string, email, Email);
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	MYSQL_SYNTHESIZE(int, gender, Gender);
	MYSQL_SYNTHESIZE(string, idCard, IdCard);
	MYSQL_SYNTHESIZE(string, school, School);
	MYSQL_SYNTHESIZE(int, degree, Degree);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(int, state, State);
	MYSQL_SYNTHESIZE(int, isManager, IsManager);
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	MYSQL_SYNTHESIZE(string, hireDate, HireDate);
	MYSQL_SYNTHESIZE(string, fireDate, FireDate);
	MYSQL_SYNTHESIZE(string, intro, Intro);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	MYSQL_SYNTHESIZE(string, creator, Creator);
	MYSQL_SYNTHESIZE(string, editor, Editor);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(string, password, Password);
	MYSQL_SYNTHESIZE(double, classFee, ClassFee);
	MYSQL_SYNTHESIZE(double, assistantFee, AssistantFee);
	MYSQL_SYNTHESIZE(string, orgId, OrgId);
	MYSQL_SYNTHESIZE(int, isInner, IsInner);

public:
	ExcelStaffDO() : BaseDO("staff")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("wx_access_id", "s", wxAccessId);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("id_card", "s", idCard);
		MYSQL_ADD_FIELD("school", "s", school);
		MYSQL_ADD_FIELD("degree", "i", degree);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("is_manager", "i", isManager);
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		MYSQL_ADD_FIELD("hire_date", "s", hireDate);
		MYSQL_ADD_FIELD("fire_date", "s", fireDate);
		MYSQL_ADD_FIELD("intro", "s", intro);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("class_fee", "d", classFee);
		MYSQL_ADD_FIELD("assistant_fee", "d", assistantFee);
		MYSQL_ADD_FIELD("org_id", "s", orgId);
		MYSQL_ADD_FIELD("is_inner", "i", isInner);
	}
};
typedef std::shared_ptr<ExcelStaffDO> PtrExcelStaffDO;