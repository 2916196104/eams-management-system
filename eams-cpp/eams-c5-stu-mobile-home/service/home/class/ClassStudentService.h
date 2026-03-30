#pragma once
#ifndef _CLASS_STUDENT_SERVICE_
#define _CLASS_STUDENT_SERVICE_
#include "domain/vo/home/class/ClassStudentVO.h"
#include "domain/query/home/class/ClassStudentQuery.h"
#include "domain/dto/home/class/ClassStudentDTO.h"

class ClassStudentService
{
public:
    oatpp::List<ClassStudentDTO::Wrapper> listAll(const ClassStudentQuery::Wrapper& query);
};

#endif