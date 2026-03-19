#pragma once
#ifndef ENROLLMENTDO_H
#define ENROLLMENTDO_H

#include"../DoInclude.h"
class Enrollment_studentDO :public BaseDO 
{
	
public:
	Enrollment_stduentDO() :BaseDO("student")
	{

	}
}
class Enrollment_courseDO :public BaseDO
{


public:

	Enrollment_courseDO() :BaseDO("course")
	{

	}
}
#endif