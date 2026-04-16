#pragma once
#ifndef _CLASS_STUDENT_DAO_
#define _CLASS_STUDENT_DAO_
#include "BaseDAO.h"
#include "../../../domain/do/home/class/ClassStudentDO.h"
#include "../../../domain/query/home/class/ClassStudentQuery.h"

class ClassStudentDAO : public BaseDAO
{
private:
    std::string queryConditionBuilder(const ClassStudentQuery::Wrapper& query, SqlParams& params);
public:
    std::list<ClassStudentDO> selectAll(const ClassStudentQuery::Wrapper& query);
};

#endif