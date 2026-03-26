#pragma once
#ifndef _CLASS_STUDENT_DO_
#define _CLASS_STUDENT_DO_
#include "../../DoInclude.h"

class ClassStudentDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(int, gender, Gender);

public:
    ClassStudentDO() : BaseDO("class_student")
    {
    }
};

typedef std::shared_ptr<ClassStudentDO> PtrClassStudentDO;
#endif