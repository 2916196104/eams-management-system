#pragma once
#ifndef _CLASS_STUDENT_MAPPER_
#define _CLASS_STUDENT_MAPPER_
#include "Mapper.h"
#include "../../../domain/do/home/class/ClassStudentDO.h"

class ClassStudentMapper : public Mapper<ClassStudentDO>
{
public:
    ClassStudentDO mapper(ResultSet* resultSet) const override
    {
        ClassStudentDO data;
        data.setName(resultSet->getString(1));
        data.setGender(resultSet->getInt(2));
        return data;
    }
};

#endif