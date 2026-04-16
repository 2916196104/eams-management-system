#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _STAFF_DO_H_
#define _STAFF_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 教师员工表 DO（对应 staff 表）
 */
class StaffDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(std::string, name, Name);
	MYSQL_SYNTHESIZE(std::string, mobile, Mobile);
	MYSQL_SYNTHESIZE(int64_t, wxAccessId, WxAccessId);
	MYSQL_SYNTHESIZE(std::string, email, Email);
	MYSQL_SYNTHESIZE(std::string, birthday, Birthday);
	MYSQL_SYNTHESIZE(int32_t, gender, Gender);
	MYSQL_SYNTHESIZE(std::string, idCard, IdCard);
	MYSQL_SYNTHESIZE(std::string, school, School);
	MYSQL_SYNTHESIZE(int32_t, degree, Degree);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(int32_t, state, State);
	MYSQL_SYNTHESIZE(bool, isManager, IsManager);
	MYSQL_SYNTHESIZE(std::string, headImg, HeadImg);
	MYSQL_SYNTHESIZE(std::string, hireDate, HireDate);
	MYSQL_SYNTHESIZE(std::string, fireDate, FireDate);
	MYSQL_SYNTHESIZE(std::string, intro, Intro);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	MYSQL_SYNTHESIZE(std::string, password, Password);
	MYSQL_SYNTHESIZE(double, classFee, ClassFee);
	MYSQL_SYNTHESIZE(double, assistantFee, AssistantFee);
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);
	MYSQL_SYNTHESIZE(bool, isInner, IsInner);

public:
	StaffDO() : BaseDO("staff")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("wx_access_id", "ll", wxAccessId);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("birthday", "dt", birthday);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("id_card", "s", idCard);
		MYSQL_ADD_FIELD("school", "s", school);
		MYSQL_ADD_FIELD("degree", "i", degree);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("is_manager", "b", isManager);
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		MYSQL_ADD_FIELD("hire_date", "dt", hireDate);
		MYSQL_ADD_FIELD("fire_date", "dt", fireDate);
		MYSQL_ADD_FIELD("intro", "s", intro);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("deleted", "b", deleted);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("class_fee", "d", classFee);
		MYSQL_ADD_FIELD("assistant_fee", "d", assistantFee);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
		MYSQL_ADD_FIELD("is_inner", "b", isInner);
	}
};

#endif // !_STAFF_DO_H_
