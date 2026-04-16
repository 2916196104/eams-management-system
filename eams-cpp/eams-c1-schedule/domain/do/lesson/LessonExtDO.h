#pragma once
#include "domain/do/lesson/LessonDO.h"

/**
 * 课表扩展数据对象 (专门用于联表查询)
 * 继承了 LessonDO 的所有基础字段，并增加了联表带出来的名字字段
 */
class LessonExtDO : public LessonDO
{
public:
	LessonExtDO() : LessonDO()
	{
		MYSQL_ADD_FIELD("course_name", "s", courseName);
		MYSQL_ADD_FIELD("class_name", "s", className);
		MYSQL_ADD_FIELD("teacher_name", "s", teacherName);
		MYSQL_ADD_FIELD("classroom_name", "s", classroomName);
		MYSQL_ADD_FIELD("sign_state", "i", signState);
	}

	MYSQL_SYNTHESIZE(std::string, courseName, CourseName)
	MYSQL_SYNTHESIZE(std::string, className, ClassName)
	MYSQL_SYNTHESIZE(std::string, teacherName, TeacherName)
	MYSQL_SYNTHESIZE(std::string, classroomName, ClassroomName)
	MYSQL_SYNTHESIZE(int, signState, SignState)
};