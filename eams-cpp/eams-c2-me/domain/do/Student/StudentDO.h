#pragma once

#ifndef _STUDENTDO_H_
#define _STUDENTDO_H_

#include "../DoInclude.h"
 



//学员信息实体 映射student表
class StudentDO :public BaseDO
{  // 宏生成字段的 get/set 方法

	MYSQL_SYNTHESIZE(int, id, Id);
	MYSQL_SYNTHESIZE(int, user_id, User_id);
	MYSQL_SYNTHESIZE(int, family_rel, Family_rel);
	MYSQL_SYNTHESIZE(int, as_default, As_default);
	MYSQL_SYNTHESIZE(int, school_id, School_id);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(int, stage, Stage);
	MYSQL_SYNTHESIZE(int, gender, Gender);
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	MYSQL_SYNTHESIZE(string, head_img, Head_img);
	MYSQL_SYNTHESIZE(int, join_way, Join_way);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, graduation_date, Graduation_date);
	MYSQL_SYNTHESIZE(string, graduation_reason, Graduation_reason);
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	MYSQL_SYNTHESIZE(int, counselor, Counselor);
	MYSQL_SYNTHESIZE(int, creator, Creator);
	MYSQL_SYNTHESIZE(int, editor, Editor);
	MYSQL_SYNTHESIZE(string, edit_time, Edit_time);
	MYSQL_SYNTHESIZE(string, idcard, Idcard);
	MYSQL_SYNTHESIZE(string, redpoint_grade, Redpoint_grade);
	MYSQL_SYNTHESIZE(string, redpoint_evaluate, Redpoint_evaluate);
	MYSQL_SYNTHESIZE(int, grade, Grade);
	MYSQL_SYNTHESIZE(string, join_date, Join_date);
	MYSQL_SYNTHESIZE(int, wx_access_id, Wx_access_id);
	MYSQL_SYNTHESIZE(int, credit, Credit);
	MYSQL_SYNTHESIZE(int, org_id, Org_id);
	MYSQL_SYNTHESIZE(int, grade_id, Grade_id);

public:
	// 构造函数：绑定表名和字段映射

	StudentDO() :BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("user_id", "i", user_id);
		MYSQL_ADD_FIELD("family_rel", "i", family_rel);
		MYSQL_ADD_FIELD("as_default", "i", as_default);
		MYSQL_ADD_FIELD("school_id", "i", school_id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("stage", "i", stage);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("head_img", "s", head_img);
		MYSQL_ADD_FIELD("join_way", "i", join_way);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduation_date);
		MYSQL_ADD_FIELD("graduation_reason", "s", graduation_reason);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("counselor", "i", counselor);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("editor", "i", editor);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("idcard", "s", idcard);
		MYSQL_ADD_FIELD("redpoint_grade", "s", redpoint_grade);
		MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpoint_evaluate);
		MYSQL_ADD_FIELD("grade", "i", grade);
		MYSQL_ADD_FIELD("join_date", "s", join_date);
		MYSQL_ADD_FIELD("wx_access_id", "i", wx_access_id);
		MYSQL_ADD_FIELD("credit", "i", credit);
		MYSQL_ADD_FIELD("org_id", "i", org_id);
		MYSQL_ADD_FIELD("grade_id", "i", grade_id);
	}

};                          



//定义智能指针
typedef std::shared_ptr<StudentDO> PtrStudentDO;


#endif



