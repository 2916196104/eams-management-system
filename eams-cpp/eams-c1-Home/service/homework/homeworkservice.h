#pragma once
#ifndef _HOMEWORK_SERVICE_H_
#define _HOMEWORK_SERVICE_H_
#include <string>
#include "oatpp/core/Types.hpp"
#include "domain/query/homework/homeworkquery.h"
#include "domain/vo/homework/homeworkVO.h"
#include "domain/dto/homework/homeworkDTO.h"
class HomeworkService
{
public:
    HomeworkPageJsonVO::Wrapper queryPage(const HomeworkQuery::Wrapper& query);
    HomeworkDetailJsonVO::Wrapper queryDetail(uint64_t id);
    HomeworkSubmitJsonVO::Wrapper submitHomework(const HomeworkSubmitDTO::Wrapper& dto);
    HomeworkDeleteJsonVO::Wrapper deleteHomework(const HomeworkDeleteQuery::Wrapper& query);
private:
    static std::string getCurrentDateTime();
};

#endif 
