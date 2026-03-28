#pragma once
#ifndef INTENDSTUDENTSERVICE_H
#define INTENDSTUDENTSERVICE_H


#include "domain/dto/dto-huitailang/intendedstudentdto.h"
class IntendstudentService
{
public:
	//添加意向学生
	uint64_t addintendstudent(const intendedstudentDTO::Wrapper& dto);

};



#endif