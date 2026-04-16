#pragma once
#ifndef _CLASSROOMSERVICE_H_
#define _CLASSROOMSERVICE_H_

#include "domain/dto/Schedule/ClassroomDTO.h"
#include "domain/query/Schedule/ClassroomQuery.h"

class ClassroomService
{
public:
	//获取点名列表
	ClassroomPageDTO::Wrapper listAll(const ClassroomQuery::Wrapper& query);
	
};

#endif