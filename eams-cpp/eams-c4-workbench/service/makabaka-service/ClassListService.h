#pragma once

#ifndef _CLASSLISTSERVICE_H_
#define _CLASSLISTSERVICE_H_
#include"domain/dto/makabaka-dto/class/classDTO.h"
#include"domain/query/makabaka-query/class/classQuery.h"
#include"domain/vo/makabaka-vo/class/classVO.h"

/*
	班级列表服务实现
*/
class ClassListService {
public:
	//分页查询班级
	ClassPageDTO::Wrapper listAll(const ClassQuery::Wrapper& query);
};

#endif  //!_CLASSLISTSERVICE_H_