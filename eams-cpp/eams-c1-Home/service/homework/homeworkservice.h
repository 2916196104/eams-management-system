#pragma once
#ifndef _HOMEWORK_SERVICE_H_
#define _HOMEWORK_SERVICE_H_

#include "domain/query/homework/homeworkquery.h"
#include "domain/vo/homework/homeworkVO.h"

class HomeworkService
{
public:
    HomeworkPageJsonVO::Wrapper queryPage(const HomeworkQuery::Wrapper& query);
    HomeworkDetailJsonVO::Wrapper queryDetail(uint64_t id);
};

#endif 
