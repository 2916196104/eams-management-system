#pragma once
#ifndef _HOMEWORK_DAO_H_
#define _HOMEWORK_DAO_H_
#include "BaseDAO.h"
#include "domain/do/homework/HomeworkDO.h"
#include "domain/query/homework/homeworkquery.h"
#include "domain/dto/homework/homeworkDTO.h"
#include <vector>

class HomeworkDAO : public BaseDAO
{
public:
    uint64_t count(const HomeworkQuery::Wrapper& query);
    std::vector<HomeworkDTO::Wrapper> selectPage(const HomeworkQuery::Wrapper& query);
    HomeworkDetailDTO::Wrapper selectDetail(const uint64_t& id);
    PtrHomeworkDO selectById(const uint64_t& id);
};

#endif 
