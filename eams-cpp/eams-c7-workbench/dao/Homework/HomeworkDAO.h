#pragma once
#ifndef _HOMEWORK_DAO_H_
#define _HOMEWORK_DAO_H_

#include "BaseDAO.h"
#include "domain/do/Homework/HomeworkDO.h"

class HomeworkDAO : public BaseDAO
{
public:
    // 插入作业
    bool insert(HomeworkDO& homework);
    // 根据ID查询作业
    PtrHomeworkDO selectById(uint64_t id);
    // 更新作业
    bool update(const HomeworkDO& homework);
    // 逻辑删除
    bool deleteById(uint64_t id);
};

#endif // _HOMEWORK_DAO_H_