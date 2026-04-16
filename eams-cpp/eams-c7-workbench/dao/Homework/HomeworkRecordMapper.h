#pragma once
#ifndef _HOMEWORK_RECORD_MAPPER_H_
#define _HOMEWORK_RECORD_MAPPER_H_

#include "Mapper.h"
#include "../../domain/do/Homework/HomeworkRecordDO.h"

class HomeworkRecordMapper : public Mapper<HomeworkRecordDO>
{
public:
    HomeworkRecordDO mapper(ResultSet* resultSet) const override
    {
        HomeworkRecordDO data;
        data.setId(resultSet->getUInt64(1));           // 假设有 getUInt64
        data.setHomeworkId(resultSet->getUInt64(2));    // 同样
        data.setStudentId(resultSet->getInt64(3));
        data.setAddTime(resultSet->getString(4));
        data.setContent(resultSet->getString(5));
        data.setScore(resultSet->getInt(6));
        data.setComment(resultSet->getString(7));
        data.setCommentTime(resultSet->getString(8));
        data.setCommentTeacher(resultSet->getInt64(9));
        data.setImages(resultSet->getString(10));
        return data;
    }
};

class PtrHomeworkRecordMapper : public Mapper<PtrHomeworkRecordDO>
{
public:
    PtrHomeworkRecordDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<HomeworkRecordDO>();
        data->setId(resultSet->getUInt64(1));
        data->setHomeworkId(resultSet->getUInt64(2));
        data->setStudentId(resultSet->getInt64(3));
        data->setAddTime(resultSet->getString(4));
        data->setContent(resultSet->getString(5));
        data->setScore(resultSet->getInt(6));
        data->setComment(resultSet->getString(7));
        data->setCommentTime(resultSet->getString(8));
        data->setCommentTeacher(resultSet->getInt64(9));
        data->setImages(resultSet->getString(10));
        return data;
    }
};

#endif // _HOMEWORK_RECORD_MAPPER_H_