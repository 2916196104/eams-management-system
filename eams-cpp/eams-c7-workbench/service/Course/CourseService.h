#pragma once
#ifndef _COURSE_SERVICE_
#define _COURSE_SERVICE_
#include "../../domain/dto/Course/CourseDTO.h"
#include "../../domain/query/Course/CourseQuery.h"
#include "../../domain/vo/Course/CourseVO.h"

class CourseService
{
public:
    CoursePageDTO::Wrapper listAll(const CourseQuery::Wrapper& query);
    CourseDTO::Wrapper getById(std::string courseId); 
};
#endif