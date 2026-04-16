#pragma once
#ifndef _COURSE_DAO_H_
#define _COURSE_DAO_H_
#include "BaseDAO.h"
#include "domain/do/Schedule/course/CourseDO.h"

class CourseDAO : public BaseDAO
{
public:
	PtrCourseDO selectById(int64_t courseId);
	std::string selectNameById(int64_t courseId);
};

#endif
