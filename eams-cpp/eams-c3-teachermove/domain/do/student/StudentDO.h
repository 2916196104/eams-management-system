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
#ifndef _STUDENT_DO_H_
#define _STUDENT_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 学生表 DO（对应 student 表）
 */
class StudentDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, userId, UserId);
	MYSQL_SYNTHESIZE(int32_t, familyRel, FamilyRel);
	MYSQL_SYNTHESIZE(bool, asDefault, AsDefault);
	MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(std::string, name, Name);
	MYSQL_SYNTHESIZE(int32_t, deleted, Deleted);
	MYSQL_SYNTHESIZE(int32_t, stage, Stage);
	MYSQL_SYNTHESIZE(int32_t, gender, Gender);
	MYSQL_SYNTHESIZE(std::string, birthday, Birthday);
	MYSQL_SYNTHESIZE(std::string, headImg, HeadImg);
	MYSQL_SYNTHESIZE(int64_t, joinWay, JoinWay);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(std::string, graduationDate, GraduationDate);
	MYSQL_SYNTHESIZE(std::string, graduationReason, GraduationReason);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int64_t, counselor, Counselor);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	MYSQL_SYNTHESIZE(std::string, idcard, Idcard);
	MYSQL_SYNTHESIZE(std::string, redpointGrade, RedpointGrade);
	MYSQL_SYNTHESIZE(std::string, redpointEvaluate, RedpointEvaluate);
	MYSQL_SYNTHESIZE(int32_t, grade, Grade);
	MYSQL_SYNTHESIZE(std::string, joinDate, JoinDate);
	MYSQL_SYNTHESIZE(int64_t, wxAccessId, WxAccessId);
	MYSQL_SYNTHESIZE(int32_t, credit, Credit);
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);
	MYSQL_SYNTHESIZE(int32_t, gradeId, GradeId);
	// 来自 user 表的关联字段，不注册为 student 表字段
	MYSQL_SYNTHESIZE(std::string, mobile, Mobile);

public:
	StudentDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("user_id", "ll", userId, false);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("as_default", "b", asDefault);
		MYSQL_ADD_FIELD("school_id", "ll", schoolId);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("stage", "i", stage);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("birthday", "dt", birthday);
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		MYSQL_ADD_FIELD("join_way", "ll", joinWay);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "dt", graduationDate);
		MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("counselor", "ll", counselor);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("idcard", "s", idcard);
		MYSQL_ADD_FIELD("redpoint_grade", "dt", redpointGrade);
		MYSQL_ADD_FIELD("redpoint_evaluate", "dt", redpointEvaluate);
		MYSQL_ADD_FIELD("grade", "i", grade);
		MYSQL_ADD_FIELD("join_date", "dt", joinDate);
		MYSQL_ADD_FIELD("wx_access_id", "ll", wxAccessId);
		MYSQL_ADD_FIELD("credit", "i", credit);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
		MYSQL_ADD_FIELD("grade_id", "i", gradeId);
	}
};

typedef std::shared_ptr<StudentDO> PtrStudentDO;
#endif // !_STUDENT_DO_H_
