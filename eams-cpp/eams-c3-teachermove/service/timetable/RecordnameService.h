
#pragma once
#ifndef _CLASS_STUDENT_SERVICE_H_
#define _CLASS_STUDENT_SERVICE_H_

#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include "dao/class_student/ClassStudentDAO.h"

/**
 * 班级学员业务逻辑类 (Service大脑)
 */
class ClassStudentService
{
public:
	// 1. 获取学员列表 (条件+分页)
	PageDTO<TimetableStudentDTO::Wrapper>::Wrapper getStudentList(const StuListQuery::Wrapper& query);

	// 2. 添加学员到课次 (批量插入)
	bool addStudentToLesson(const AddStudentToLessonDTO::Wrapper& dto);

	// 3. 获取学员课程列表
	oatpp::List<TimetableStudentCourseDTO::Wrapper> getStudentCourseList(const StuClassQuery::Wrapper& query);
};

#endif // !_CLASS_STUDENT_SERVICE_H_