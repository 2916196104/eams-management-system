#pragma once


#ifndef _ENROLLCOURSE_SERVICE_
#define _ENROLLCOURSE_SERVICE_
#include "domain/vo/EnrollCourse/EnrollCourseVO.h"
#include "domain/query/EnrollCourse/EnrollCourseQuery.h"
#include "domain/dto/EnrollCourse/EnrollCourseDTO.h"

class EnrollCourseService
{
public:
	EnrollCoursePageDTO::Wrapper listAll(const EnrollCourseQuery::Wrapper& query);
};


#endif