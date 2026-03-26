#pragma once
#ifndef _EXCHANGEDO_H_
#define _EXCHANGEDO_H_

#include "../DoInclude.h"

// 可兑换礼品
class GoodsDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(int, id, Id);
	MYSQL_SYNTHESIZE(int, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(int, materialId, MaterialId);
	MYSQL_SYNTHESIZE(int, categoryId, CategoryId);
	MYSQL_SYNTHESIZE(string, categoryName, CategoryName);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(int, credit, Credit);
	MYSQL_SYNTHESIZE(int, state, State);
	MYSQL_SYNTHESIZE(int, saleNum, SaleNum);
	MYSQL_SYNTHESIZE(int, viewNum, ViewNum);
	MYSQL_SYNTHESIZE(string, cover, Cover);
	MYSQL_SYNTHESIZE(string, content, Content);
	MYSQL_SYNTHESIZE(int, creator, Creator);
	MYSQL_SYNTHESIZE(int, editor, Editor);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(int, orgId, OrgId);
	// 多表查询中添加的其他表中的字段，不要在 构造函数中添加
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName); // 表 org中的字段
	MYSQL_SYNTHESIZE(int, storage, Storage); // 表 material中的字段

	GoodsDO() : BaseDO("credit_mall")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("school_id", "i", schoolId);
		MYSQL_ADD_FIELD("material_id", "i", materialId);
		MYSQL_ADD_FIELD("category_id", "i", categoryId);
		MYSQL_ADD_FIELD("category_name", "s", categoryName);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("credit", "i", credit);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("sale_num", "i", saleNum);
		MYSQL_ADD_FIELD("view_num", "i", viewNum);
		MYSQL_ADD_FIELD("cover", "s", cover);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};

// 兑换记录
class AcceptGoodsDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int, id, Id);
	MYSQL_SYNTHESIZE(int, creditMallId, CreditMallId);
	MYSQL_SYNTHESIZE(int, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(int, creator, Creator);
	MYSQL_SYNTHESIZE(int, editor, Editor);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(int, studentId, StudentId);
	MYSQL_SYNTHESIZE(int, userId, UserId);
	MYSQL_SYNTHESIZE(int, num, Num);
	MYSQL_SYNTHESIZE(string, credit, Credit);
	MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
	MYSQL_SYNTHESIZE(int, verifyStaff, VerifyStaff);
	MYSQL_SYNTHESIZE(string, verifyTime, VerifyTime);
	MYSQL_SYNTHESIZE(string, verifyRemark, VerifyRemark);
	MYSQL_SYNTHESIZE(string, creditMallName, CreditMallName);// credit_mall 数据库中的name
	MYSQL_SYNTHESIZE(string, cover, Cover);// credit_mall中
	MYSQL_SYNTHESIZE(string, studentName, StudentName);// student表
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName);// org表
	MYSQL_SYNTHESIZE(string, mobile, Mobile);// user表
	MYSQL_SYNTHESIZE(string, verifyStaffName, VerifyStaffName);// staff表

	AcceptGoodsDO() : BaseDO("credit_exchange")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("credit_mall_id", "i", creditMallId);
		MYSQL_ADD_FIELD("school_id", "i", schoolId);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		MYSQL_ADD_FIELD("user_id", "i", userId);
		MYSQL_ADD_FIELD("num", "i", num);
		MYSQL_ADD_FIELD("credit", "s", credit);
		MYSQL_ADD_FIELD("verify_state", "i", verifyState);
		MYSQL_ADD_FIELD("verify_staff", "i", verifyStaff);
		MYSQL_ADD_FIELD("verify_time", "s", verifyTime);
		MYSQL_ADD_FIELD("verify_remark", "s", verifyRemark);
	}
};

// 积分兑换规则
class SettingDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int, id, Id);
	MYSQL_SYNTHESIZE(int, settingId, SettingId);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, code, Code);
	MYSQL_SYNTHESIZE(string, value, Value);
	MYSQL_SYNTHESIZE(string, valueType, ValueType);
	MYSQL_SYNTHESIZE(string, info, Info);
	MYSQL_SYNTHESIZE(int, sortNum, SortNum);

	SettingDO() : BaseDO("setting_option")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("setting_id", "i", settingId);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("code", "s", code);
		MYSQL_ADD_FIELD("value", "s", value);
		MYSQL_ADD_FIELD("value_type", "s", valueType);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("sort_num", "i", sortNum);
	}
};

typedef std::shared_ptr<SettingDO> PtrSettingDO;
typedef std::shared_ptr<AcceptGoodsDO> PtrAcceptGoodsDO;
typedef std::shared_ptr<GoodsDO> PtrGoodsDO;



#endif