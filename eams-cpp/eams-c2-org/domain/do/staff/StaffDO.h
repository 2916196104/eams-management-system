#pragma once
#pragma once
#ifndef _STAFFDO_H_
#define _STAFFDO_H_
#include "domain/GlobalInclude.h"
#include "BaseDO.h"

/**
 * 员工数据实体（完整版，匹配staff表所有字段）
 */
class StaffDO : public BaseDO
{
	// 基础信息
	MYSQL_SYNTHESIZE(uint64_t, id, Id);          // 主键ID
	MYSQL_SYNTHESIZE(string, name, Name);      // 姓名
	MYSQL_SYNTHESIZE(string, mobile, Mobile);  // 手机号
	MYSQL_SYNTHESIZE(uint64_t, wxAccessId, WxAccessId); // 微信登录ID
	MYSQL_SYNTHESIZE(string, email, Email);    // 邮箱
	MYSQL_SYNTHESIZE(string, birthday, Birthday); // 生日
	MYSQL_SYNTHESIZE(int, gender, Gender);     // 性别
	MYSQL_SYNTHESIZE(string, idCard, IdCard);  // 身份证号
	MYSQL_SYNTHESIZE(string, school, School);  // 毕业学校
	MYSQL_SYNTHESIZE(int, degree, Degree);     // 学历
	MYSQL_SYNTHESIZE(string, remark, Remark);  // 备注
	MYSQL_SYNTHESIZE(int, state, State);       // 在职状态
	MYSQL_SYNTHESIZE(int, isManager, IsManager); // 是否是管理者
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);// 头像
	MYSQL_SYNTHESIZE(string, hireDate, HireDate); // 入职日期
	MYSQL_SYNTHESIZE(string, fireDate, FireDate); // 离职日期
	MYSQL_SYNTHESIZE(string, intro, Intro);    // 介绍

	// 系统字段
	MYSQL_SYNTHESIZE(string, addTime, AddTime); // 创建时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime); // 编辑时间
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator); // 创建人
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);   // 编辑人
	MYSQL_SYNTHESIZE(int, deleted, Deleted);    // 逻辑删除标记

	// 其他字段
	MYSQL_SYNTHESIZE(string, password, Password); // 密码
	MYSQL_SYNTHESIZE(double, classFee, ClassFee); // 课时费
	MYSQL_SYNTHESIZE(double, assistantFee, AssistantFee); // 助教费
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);     // 所属组织ID
	MYSQL_SYNTHESIZE(int, isInner, IsInner);    // 是否内部人员

public:
	// 表名：staff（必须和数据库一致）
	StaffDO() : BaseDO("staff")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "q", id);
		// 基础信息字段映射
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("wx_access_id", "q", wxAccessId);
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
		// 系统字段
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("creator", "q", creator);
		MYSQL_ADD_FIELD("editor", "q", editor);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 其他字段
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("class_fee", "d", classFee);
		MYSQL_ADD_FIELD("assistant_fee", "d", assistantFee);
		MYSQL_ADD_FIELD("org_id", "q", orgId);
		MYSQL_ADD_FIELD("is_inner", "i", isInner);
	}
};

typedef std::shared_ptr<StaffDO> PtrStaffDO;

#endif // !_STAFFDO_H_