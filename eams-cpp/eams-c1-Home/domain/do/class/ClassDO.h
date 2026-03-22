#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _CLASSDO_H_
#define _CLASSDO_H_
#include "../DoInclude.h"

/*
* 班级数据库实体类
*/
class ClassDO : public BaseDO {
	// 班级id
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	//班级名
	MYSQL_SYNTHESIZE(string, class_name, Class);
	//课程id
	MYSQL_SYNTHESIZE(uint64_t, course_id, CourseId);
	//教室id
	MYSQL_SYNTHESIZE(uint64_t, classroom_id, ClassroomId);
	//创建者
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	//添加时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	//编辑时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	//删除标记
	MYSQL_SYNTHESIZE(uint8_t, deleted, Deleted);
	//班级负责人id
	MYSQL_SYNTHESIZE(uint64_t, teacher_id, TeacherId);
	//排课备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//是否完结
	MYSQL_SYNTHESIZE(uint8_t, be_over, BeOver);
	//完结时间
	MYSQL_SYNTHESIZE(string, over_time, OverTime);
	//完结操作人
	MYSQL_SYNTHESIZE(uint64_t, over_operator, OverOperator);
	//计划开班日期
	MYSQL_SYNTHESIZE(string, start_date, StartDate);
	//计划结业日期
	MYSQL_SYNTHESIZE(string, end_date, EndDate);
	//预招人数
	MYSQL_SYNTHESIZE(uint32_t, planned_student_count, PlannedStudentCount);
	//预排课次数
	MYSQL_SYNTHESIZE(uint32_t, planned_lesson_count, PlannedLessonCount);
	//创建者所属学校ID
	MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
	//年级ID
	MYSQL_SYNTHESIZE(uint64_t, grade_id, GradeId);
public:
	ClassDO() : BaseDO("class")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("class_name", "s", class_name);
		MYSQL_ADD_FIELD("course_id", "i", course_id);
		MYSQL_ADD_FIELD("classroom_id", "i", classroom_id);
		MYSQL_ADD_FIELD("creator", "i", creator);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("be_over", "i", be_over);
		MYSQL_ADD_FIELD("over_time", "s", over_time);
		MYSQL_ADD_FIELD("over_operator", "i", over_operator);
		MYSQL_ADD_FIELD("start_date", "s", start_date);
		MYSQL_ADD_FIELD("end_date", "s", end_date);
		MYSQL_ADD_FIELD("planned_student_count", "i", planned_student_count);
		MYSQL_ADD_FIELD("planned_lesson_count", "i", planned_lesson_count);
		MYSQL_ADD_FIELD("school_id", "i", school_id);
		MYSQL_ADD_FIELD("org_id", "i", org_id);
		MYSQL_ADD_FIELD("grade_id", "i", grade_id);
	}
};

// ClassDO智能指针
typedef std::shared_ptr<ClassDO> PtrClassDO;


/*
* 学生数据库实体类
*/
class StudentDO : public BaseDO {
	//学生id
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	//家长id
	MYSQL_SYNTHESIZE(uint64_t, user_id, UserId);
	//家庭关系
	MYSQL_SYNTHESIZE(uint8_t, family_rel, FamilyRel);
	//家长默认查看的学员
	MYSQL_SYNTHESIZE(uint8_t, as_default, AsDefault);
	//所属分校
	MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
	//姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	//逻辑删除
	MYSQL_SYNTHESIZE(uint8_t, deleted, Deleted);
	//阶段状态0意向学员
	MYSQL_SYNTHESIZE(uint8_t, stage, Stage);
	//性别
	MYSQL_SYNTHESIZE(uint8_t, gender, Gender);
	//生日
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	//头像
	MYSQL_SYNTHESIZE(string, head_img, HeadImg);
	//加入方式
	MYSQL_SYNTHESIZE(uint64_t, join_way, JoinWay);
	//备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//结业日期
	MYSQL_SYNTHESIZE(string, graduation_date, GraduationDate);
	//结业原因
	MYSQL_SYNTHESIZE(string, graduation_reason, GraduationReason);
	//加入时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	//顾问
	MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
	//创建者
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	//编辑人
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	//编辑时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	//身份证号
	MYSQL_SYNTHESIZE(string, idcard, Idcard);
	//红点标记成绩最后查看时间
	MYSQL_SYNTHESIZE(string, redpoint_grade, RedpointGrade);
	//红点标记点评最后查看时间
	MYSQL_SYNTHESIZE(string, redpoint_evaluate, RedpointEvaluate);
	//入学年份
	MYSQL_SYNTHESIZE(uint16_t, grade, Grade);
	//入学日期
	MYSQL_SYNTHESIZE(string, join_date, JoinDate);
	//微信登录记录id
	MYSQL_SYNTHESIZE(uint64_t, wx_access_id, WxAccessId);
	//学生积分
	MYSQL_SYNTHESIZE(int, credit, Credit);
	//创建者所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
	//年级ID
	MYSQL_SYNTHESIZE(uint64_t, grade_id, GradeId);
public:
	StudentDO() : BaseDO("student")
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

/*
* 学生DO智能指针
*/
typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif // !_CLASSDO_H_