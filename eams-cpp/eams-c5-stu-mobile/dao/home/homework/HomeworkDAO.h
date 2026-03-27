#pragma once

#ifndef _HOMEWORK_DAO_
#define _HOMEWORK_DAO_
#include "BaseDAO.h"
#include "../../../domain/do/home/homework/HomeworkDO.h"
#include "../../../domain/query/home/homework/HomeworkQuery.h"

class HomeworkDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const HomeworkQuery::Wrapper& query, SqlParams& params);
public:
    uint64_t count(const HomeworkQuery::Wrapper& query);
    std::list<HomeworkDO> selectWithPage(const HomeworkQuery::Wrapper& query);
};

#endif