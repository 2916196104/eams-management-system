#pragma once
#ifndef _HOMEWORK_MAPPER_H_
#define _HOMEWORK_MAPPER_H_

#include "Mapper.h"
#include "../../domain/do/Homework/HomeworkDO.h"

class HomeworkMapper : public Mapper<HomeworkDO>
{
public:
    HomeworkDO mapper(ResultSet* resultSet) const override
    {
        HomeworkDO data;
        // 使用 getUInt64 或转换
        data.setId(resultSet->getUInt64(1));
        // 如果 ResultSet 没有 getUInt64，改为：
        // data.setId(static_cast<uint64_t>(resultSet->getInt64(1)));
        data.setClassId(resultSet->getInt64(2));
        data.setTitle(resultSet->getString(3));
        data.setContent(resultSet->getString(4));
        data.setCreator(resultSet->getInt64(5));
        data.setEditor(resultSet->getInt64(6));
        data.setAddTime(resultSet->getString(7));
        data.setEditTime(resultSet->getString(8));
        data.setDeleted(resultSet->getBoolean(9));
        data.setOrgId(resultSet->getInt64(10));
        return data;
    }
};

class PtrHomeworkMapper : public Mapper<PtrHomeworkDO>
{
public:
    PtrHomeworkDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<HomeworkDO>();
        data->setId(resultSet->getUInt64(1));           // 同样修改
        data->setClassId(resultSet->getInt64(2));
        data->setTitle(resultSet->getString(3));
        data->setContent(resultSet->getString(4));
        data->setCreator(resultSet->getInt64(5));
        data->setEditor(resultSet->getInt64(6));
        data->setAddTime(resultSet->getString(7));
        data->setEditTime(resultSet->getString(8));
        data->setDeleted(resultSet->getBoolean(9));
        data->setOrgId(resultSet->getInt64(10));
        return data;
    }
};

#endif // _HOMEWORK_MAPPER_H_