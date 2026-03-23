#pragma once

#ifndef _CLASSDO_H_
#define _CLASSDO_H_

#include"DoInclude.h"

/*
	班级用户数据实体
*/
class ClassDO :public BaseDO {
	//班级id(主键)
	MYSQL_SYNTHESIZE(string, id, Id);
	//班级名
	MYSQL_SYNTHESIZE(string, name, Name);
	//课程
	MYSQL_SYNTHESIZE(string, course_id, Course_id);
	//教室
	MYSQL_SYNTHESIZE(string, classroom_id, Classroom_id);
	//创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	//编辑人
	MYSQL_SYNTHESIZE(string, editor, Editor);
	//添加时间
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	//编辑时间
	MYSQL_SYNTHESIZE(string, edit_time, Edit_time);
	//删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//班级负责人
	MYSQL_SYNTHESIZE(string, teacher_id, Teacher_id);
	//排课备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//是否完结
	MYSQL_SYNTHESIZE(int, be_over, Be_over);
	//完结时间
	MYSQL_SYNTHESIZE(string, over_time, Over_time);
	//完结操作人
	MYSQL_SYNTHESIZE(string, over_operator, Over_operator);
	//计划开班日期
	MYSQL_SYNTHESIZE(string, start_date, Start_date);
	//计划结业日期
	MYSQL_SYNTHESIZE(string, end_date, End_date);
	//预招人数
	MYSQL_SYNTHESIZE(int, planned_student_count, Planned_student_count);
	//预排课次数
	MYSQL_SYNTHESIZE(int, planned_lesson_count, Planned_lesson_count);
	//创建者所属学校id
	MYSQL_SYNTHESIZE(string, school_id, School_id);
	//创建者所属组织id
	MYSQL_SYNTHESIZE(string, org_id, Org_id);
	//年级id
	MYSQL_SYNTHESIZE(int, grade_id, Grade_id);
public:
	ClassDO : BaseDO("class") {
		//主键 班级id
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("course_id", "s", course_id, false);
		MYSQL_ADD_FIELD("classroom_id", "s", classroom_id);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("be_over", "i", be_over);
		MYSQL_ADD_FIELD("over_time", "s", over_time);
		MYSQL_ADD_FIELD("over_operator", "s", over_operator);
		MYSQL_ADD_FIELD("start_date", "s", start_date);
		MYSQL_ADD_FIELD("end_date", "s", end_date);
		MYSQL_ADD_FIELD("planned_student_count", "i", planned_student_count);
		MYSQL_ADD_FIELD("planned_lesson_count", "i", planned_lesson_count);
		MYSQL_ADD_FIELD("school_id", "s", school_id);
		MYSQL_ADD_FIELD("org_id", "s", org_id);
		MYSQL_ADD_FIELD("grade_id", "i", grade_id);
	}
};

//定义一个班级实体的智能指针
typedef std::shared_ptr<ClassDO> PtrClassDO;

#endif //!_CLASSDO_H_