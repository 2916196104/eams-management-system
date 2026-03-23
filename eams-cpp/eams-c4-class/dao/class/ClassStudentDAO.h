#pragma once
#ifndef _CLASS_STUDENT_DAO_H_
#define _CLASS_STUDENT_DAO_H_

#include "BaseDAO.h"
#include "domain/do/ClassStudentDO.h"
#include "domain/query/class/ClassStudentQuery.h"

class ClassStudentDAO : public BaseDAO
{
public:
	uint64_t countClassStudentList(const ClassStudentQuery::Wrapper& query);
	std::list<PtrClassStudentDO> selectClassStudentList(const ClassStudentQuery::Wrapper& query);
	PtrClassStudentDO selectClassStudentDetail(uint64_t id);
	uint64_t countClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query);
	std::list<PtrClassStudentCourseDO> selectClassStudentCourseList(const ClassStudentCourseQuery::Wrapper& query);
};

#endif
