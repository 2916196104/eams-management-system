#pragma once

#ifndef _STUDENTSERVICE_H_
#define _STUDENTSERVICE_H_

 
#include "domain/dto/student/StudentDTO.h"
#include "dao/student/StudentDAO.h"
#include "domain/query/Student/IdQuery.h"

class StudentService
{
public:
	// É¾³ýÓÃ»§
	bool deleteStudent(const std::uint64_t & id);


};


#endif