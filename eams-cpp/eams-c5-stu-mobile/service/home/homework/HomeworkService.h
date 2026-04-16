#pragma once
#ifndef _HOMEWORK_SERVICE_
#define _HOMEWORK_SERVICE_
#include "domain/vo/home/homework/HomeworkVO.h"
#include "domain/query/home/homework/HomeworkQuery.h"
#include "domain/dto/home/homework/HomeworkDTO.h"

class HomeworkService
{
public:
    HomeworkPageDTO::Wrapper listAll(const HomeworkQuery::Wrapper& query);
};
#endif