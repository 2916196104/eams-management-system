#pragma once
#ifndef _LESSON_DAO_
#define _LESSON_DAO_

#include "BaseDAO.h"
#include "../../domain/do/lesson/LessonDO.h"
#include "../../domain/query/lesson/LessonQuery.h"

class LessonDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const LessonQuery::Wrapper& query, SqlParams& params);

public:
    uint64_t count(const LessonQuery::Wrapper& query);
    std::list<LessonDO> selectWithPage(const LessonQuery::Wrapper& query);
    PtrLessonDO selectById(long long id);
    int insert(const LessonDO& data);
    int updateById(const LessonDO& data);
    int deleteById(long long id);
};

#endif // !_LESSON_DAO_