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

/**
 * class表数据库实体类
 */
 /*Field Type Null
 id,bigint unsigned,NO
 name,varchar(50),NO
 course_id,bigint,NO
 classroom_id,bigint,YES
 creator,bigint,YES
 editor,bigint,YES
 add_time,datetime,YES
 edit_time,datetime,YES
 deleted,tinyint(1),YES
 teacher_id,bigint,YES
 remark,varchar(255),YES
 be_over,tinyint(1),YES
 over_time,datetime,YES
 over_operator,bigint,YES
 start_date,date,YES
 end_date,date,YES
 planned_student_count,int,YES
 planned_lesson_count,int,YES
 school_id,bigint,YES
 org_id,bigint,YES
 grade_id,int,YES
 */
/**班级详情
* Field Type Null
* name,varchar(50),YES
start_date,date,YES
end_date,date,YES
remark,varchar(255),YES
classroom,varchar(50),YES
teacher_name,varchar(20),YES
course_name,varchar(50),YES
student_count,bigint,YES
over_lesson_count,bigint,YES
*/
class ClassDO : public BaseDO {
    // 班级id
    MYSQL_SYNTHESIZE(uint64_t, id, Id);
    // 班级名
    MYSQL_SYNTHESIZE(std::string, name, Name);
    // 课程id
    MYSQL_SYNTHESIZE(uint64_t, course_id, CourseId);
    // 教室id
    MYSQL_SYNTHESIZE(uint64_t, classroom_id, ClassroomId);
    // 创建者
    MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
    // 编辑者（你表里有 editor）
    MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
    // 添加时间
    MYSQL_SYNTHESIZE(std::string, add_time, AddTime);
    // 编辑时间
    MYSQL_SYNTHESIZE(std::string, edit_time, EditTime);
    // 删除标记
    MYSQL_SYNTHESIZE(uint8_t, deleted, Deleted);
    // 班级负责人id
    MYSQL_SYNTHESIZE(uint64_t, teacher_id, TeacherId);
    // 排课备注
    MYSQL_SYNTHESIZE(std::string, remark, Remark);
    // 是否完结
    MYSQL_SYNTHESIZE(uint8_t, be_over, BeOver);
    // 完结时间
    MYSQL_SYNTHESIZE(std::string, over_time, OverTime);
    // 完结操作人
    MYSQL_SYNTHESIZE(uint64_t, over_operator, OverOperator);
    // 计划开班日期
    MYSQL_SYNTHESIZE(std::string, start_date, StartDate);
    // 计划结业日期
    MYSQL_SYNTHESIZE(std::string, end_date, EndDate);
    // 预招人数
    MYSQL_SYNTHESIZE(uint32_t, planned_student_count, PlannedStudentCount);
    // 预排课次数
    MYSQL_SYNTHESIZE(uint32_t, planned_lesson_count, PlannedLessonCount);
    // 创建者所属学校ID
    MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
    // 创建者所属组织ID
    MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
    // 年级ID（表里是 int）
    MYSQL_SYNTHESIZE(uint32_t, grade_id, GradeId);
	// 其他字段根据需要继续添加
    // 班级名
	MYSQL_SYNTHESIZE(std::string, classroom, ClassRoom);//classroom_id对应的教室名称 classroom表中的name字段
	// 课程名
	MYSQL_SYNTHESIZE(std::string, course_name, Course_Name);//course_id对应的课程名称 course表中的name字段
	// 教师名称
	MYSQL_SYNTHESIZE(std::string, teacher_name, Teacher_Name);//teacher_id对应的教师名称 staff表中的name字段
	// 班级人数（这个字段是通过 SQL join 和 count 计算出来的，不直接存储在数据库里） 
	MYSQL_SYNTHESIZE(uint32_t, student_count, StudentCount);
	//课次数（这个字段也是通过 SQL join 和 count 计算出来的，不直接存储在数据库里）
	MYSQL_SYNTHESIZE(uint32_t, over_lesson_count, Over_Lesson_Count);
public:
    ClassDO() : BaseDO("class") {
        MYSQL_ADD_FIELD_PK("id", "i", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("course_id", "i", course_id);
        MYSQL_ADD_FIELD("classroom_id", "i", classroom_id);
        MYSQL_ADD_FIELD("creator", "i", creator);
        MYSQL_ADD_FIELD("editor", "i", editor);         
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

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ClassDO> PtrClassDO;


/* Field Type Null
id,bigint unsigned,NO
user_id,bigint,NO
family_rel,tinyint,YES
as_default,tinyint(1),YES
school_id,bigint,YES
name,varchar(20),NO
deleted,int,YES
stage,tinyint,YES
gender,tinyint,YES
birthday,date,YES
head_img,varchar(255),YES
join_way,bigint,YES
remark,varchar(255),YES
graduation_date,date,YES
graduation_reason,varchar(255),YES
add_time,datetime,YES
counselor,bigint,YES
creator,bigint,YES
editor,bigint,YES
edit_time,datetime,YES
idcard,varchar(30),YES
redpoint_grade,datetime,YES
redpoint_evaluate,datetime,YES
grade,year,YES
join_date,date,YES
wx_access_id,bigint,YES
credit,int,YES
org_id,bigint,YES
grade_id,int,YES
*/
// student表数据库实体类
class StudentDO : public BaseDO {
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(uint64_t, user_id, UserId);
	MYSQL_SYNTHESIZE(uint8_t, family_rel, FamilyRel);
	MYSQL_SYNTHESIZE(uint8_t, as_default, AsDefault);
	MYSQL_SYNTHESIZE(uint64_t, school_id, SchoolId);
	MYSQL_SYNTHESIZE(std::string, name, Name);
	MYSQL_SYNTHESIZE(uint8_t, deleted, Deleted);
	MYSQL_SYNTHESIZE(uint8_t, stage, Stage);
	MYSQL_SYNTHESIZE(uint8_t, gender, Gender);
	// date/datetime 统一用 string
	MYSQL_SYNTHESIZE(std::string, birthday, Birthday);
	MYSQL_SYNTHESIZE(std::string, head_img, HeadImg);
	MYSQL_SYNTHESIZE(uint64_t, join_way, JoinWay);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(std::string, graduation_date, GraduationDate);
	MYSQL_SYNTHESIZE(std::string, graduation_reason, GraduationReason);
	MYSQL_SYNTHESIZE(std::string, add_time, AddTime);
	MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	MYSQL_SYNTHESIZE(std::string, edit_time, EditTime);
	MYSQL_SYNTHESIZE(std::string, idcard, Idcard);
	MYSQL_SYNTHESIZE(std::string, redpoint_grade, RedpointGrade);
	MYSQL_SYNTHESIZE(std::string, redpoint_evaluate, RedpointEvaluate);
	// grade: year
	MYSQL_SYNTHESIZE(uint32_t, grade, Grade);
	MYSQL_SYNTHESIZE(std::string, join_date, JoinDate);
	MYSQL_SYNTHESIZE(uint64_t, wx_access_id, WxAccessId);
	MYSQL_SYNTHESIZE(int32_t, credit, Credit);
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
	// grade_id: int
	MYSQL_SYNTHESIZE(uint32_t, grade_id, GradeId);

public:
	StudentDO() : BaseDO("student") {
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

// 给 StudentDO 智能指针设定一个别名方便使用
typedef std::shared_ptr<StudentDO> PtrStudentDO;

#endif // !_CLASSDO_H_
