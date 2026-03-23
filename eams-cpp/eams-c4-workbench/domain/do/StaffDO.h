#pragma once
#ifndef STAFFDO_H
#define STAFFDO_H

#include "../do/DoInclude.h"

/**
 * staff表数据库实体类
 */
class StaffDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 手机号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 微信登录ID
	MYSQL_SYNTHESIZE(long long, wxAccessId, WxAccessId);
	// 邮箱
	MYSQL_SYNTHESIZE(string, email, Email);
	// 生日
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	// 性别
	MYSQL_SYNTHESIZE(int, gender, Gender);
	// 身份证
	MYSQL_SYNTHESIZE(string, idCard, IdCard);
	// 毕业学校
	MYSQL_SYNTHESIZE(string, school, School);
	// 学历
	MYSQL_SYNTHESIZE(int, degree, Degree);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 在职状态
	MYSQL_SYNTHESIZE(int, state, State);
	// 是否是管理者
	MYSQL_SYNTHESIZE(int, isManager, IsManager);
	// 头像
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	// 入职日期
	MYSQL_SYNTHESIZE(string, hireDate, HireDate);
	// 离职日期
	MYSQL_SYNTHESIZE(string, fireDate, FireDate);
	// 介绍
	MYSQL_SYNTHESIZE(string, intro, Intro);
	// 创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(long long, editor, Editor);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 密码
	MYSQL_SYNTHESIZE(string, password, Password);
	// 课时费
	MYSQL_SYNTHESIZE(double, classFee, ClassFee);
	// 助教费
	MYSQL_SYNTHESIZE(double, assistantFee, AssistantFee);
	// 所属组织ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);
	// 是否内部人员
	MYSQL_SYNTHESIZE(int, isInner, IsInner);

public:
	StaffDO() : BaseDO("staff")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 姓名
		MYSQL_ADD_FIELD("name", "s", name);
		// 手机号
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		// 微信登录ID
		MYSQL_ADD_FIELD("wx_access_id", "i", wxAccessId);
		// 邮箱
		MYSQL_ADD_FIELD("email", "s", email);
		// 生日
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		// 性别
		MYSQL_ADD_FIELD("gender", "i", gender);
		// 身份证
		MYSQL_ADD_FIELD("id_card", "s", idCard);
		// 毕业学校
		MYSQL_ADD_FIELD("school", "s", school);
		// 学历
		MYSQL_ADD_FIELD("degree", "i", degree);
		// 备注
		MYSQL_ADD_FIELD("remark", "s", remark);
		// 在职状态
		MYSQL_ADD_FIELD("state", "i", state);
		// 是否是管理者
		MYSQL_ADD_FIELD("is_manager", "i", isManager);
		// 头像
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		// 入职日期
		MYSQL_ADD_FIELD("hire_date", "s", hireDate);
		// 离职日期
		MYSQL_ADD_FIELD("fire_date", "s", fireDate);
		// 介绍
		MYSQL_ADD_FIELD("intro", "s", intro);
		// 创建时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 编辑时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 编辑人
		MYSQL_ADD_FIELD("editor", "i", editor);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 密码
		MYSQL_ADD_FIELD("password", "s", password);
		// 课时费
		MYSQL_ADD_FIELD("class_fee", "d", classFee);
		// 助教费
		MYSQL_ADD_FIELD("assistant_fee", "d", assistantFee);
		// 所属组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
		// 是否内部人员
		MYSQL_ADD_FIELD("is_inner", "i", isInner);
	}
};

typedef std::shared_ptr<StaffDO> PtrStaffDO;

#endif // STAFFDO_H
