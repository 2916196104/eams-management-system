#pragma once
#ifndef _FINISH_STUDENT_DO_H_
#define _FINISH_STUDENT_DO_H_

#include "domain/do/DoInclude.h"

/**
 * 结业学员数据对象，对应 student 表
 */
class FinishStudentDO : public BaseDO
{
public:
	FinishStudentDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		MYSQL_ADD_FIELD("parent_name", "s", parentName);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("counselor", "s", counselor);
		MYSQL_ADD_FIELD("grade", "s", grade);
		MYSQL_ADD_FIELD("school_name", "s", schoolName);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("points", "i", points);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
	}

	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, parentName, ParentName);
	MYSQL_SYNTHESIZE(int32_t, familyRel, FamilyRel);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, counselor, Counselor);
	MYSQL_SYNTHESIZE(string, grade, Grade);
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName);
	MYSQL_SYNTHESIZE(int32_t, lessonCount, LessonCount);
	MYSQL_SYNTHESIZE(int32_t, points, Points);
	MYSQL_SYNTHESIZE(int32_t, gender, Gender);
	MYSQL_SYNTHESIZE(int32_t, age, Age);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
};

#endif // !_FINISH_STUDENT_DO_H_
