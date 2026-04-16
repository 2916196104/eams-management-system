#pragma once
#ifndef _HOMEWORK_DO_
#define _HOMEWORK_DO_
#include "../../DoInclude.h"

class HomeworkDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, className, ClassName);
    MYSQL_SYNTHESIZE(string, title, Title);
    MYSQL_SYNTHESIZE(int, submitStatus, SubmitStatus);

public:
    HomeworkDO() : BaseDO("homework")
    {
    }
};

typedef std::shared_ptr<HomeworkDO> PtrHomeworkDO;
#endif