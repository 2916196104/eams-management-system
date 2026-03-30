#pragma once

#ifndef _HOMEWORK_MAPPER_
#define _HOMEWORK_MAPPER_
#include "Mapper.h"
#include "../../../domain/do/home/homework/HomeworkDO.h"

class HomeworkMapper : public Mapper<HomeworkDO>
{
public:
    HomeworkDO mapper(ResultSet* resultSet) const override
    {
        HomeworkDO data;

        // 只映射我们需要的三个字段
        data.setClassName(resultSet->getString(1));    // 班级名称
        data.setTitle(resultSet->getString(2));         // 作业标题
        data.setSubmitStatus(resultSet->getInt(3));    // 提交状态

        return data;
    }
};

#endif