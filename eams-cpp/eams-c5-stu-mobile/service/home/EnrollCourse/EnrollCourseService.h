#pragma once


#ifndef _ENROLLCOURSE_SERVICE_
#define _ENROLLCOURSE_SERVICE_
#include "domain/vo/home/EnrollCourse/EnrollCourseVO.h"
#include "domain/query/home/EnrollCourse/EnrollCourseQuery.h"
#include "domain/dto/home/EnrollCourse/EnrollCourseDTO.h"

class EnrollCourseService
{
public:
	EnrollCoursePageDTO::Wrapper listAll(const EnrollCourseQuery::Wrapper& query);
};


#endif