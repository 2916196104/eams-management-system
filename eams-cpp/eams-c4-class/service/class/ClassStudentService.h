#pragma once
#ifndef _CLASS_STUDENT_SERVICE_H_
#define _CLASS_STUDENT_SERVICE_H_

#include "domain/query/class/ClassStudentQuery.h"
#include "domain/dto/class/ClassStudentDTO.h"

class ClassStudentService
{
public:
	ClassStudentListPageDTO::Wrapper listClassStudents(const ClassStudentQuery::Wrapper& query);
	ClassStudentDetailDTO::Wrapper getClassStudentDetail(uint64_t id);
	ClassStudentCoursePageDTO::Wrapper listClassStudentCourses(const ClassStudentCourseQuery::Wrapper& query);
};

#endif
