#pragma once
#ifndef _LESSON_MAPPER_
#define _LESSON_MAPPER_

#include "Mapper.h"
#include "../../domain/do/lesson/LessonDO.h"

class LessonMapper : public Mapper<LessonDO>
{
public:
    LessonDO mapper(ResultSet* resultSet) const override
    {
        LessonDO data;
        // 按 SELECT 语句中的字段顺序取值
        data.setId(resultSet->getInt64(1));
        data.setTitle(resultSet->getString(2));
        data.setSn(resultSet->getInt(3));
        data.setCourseId(resultSet->getInt64(4));
        data.setScheduleId(resultSet->getInt64(5));
        data.setClassId(resultSet->getInt64(6));
        data.setRoomId(resultSet->getInt64(7));
        data.setDate(resultSet->getString(8));
        data.setStartTime(resultSet->getString(9));
        data.setEndTime(resultSet->getString(10));
        data.setCreator(resultSet->getInt64(11));
        data.setEditor(resultSet->getInt64(12));
        data.setAddTime(resultSet->getString(13));
        data.setEditTime(resultSet->getString(14));
        data.setDeleted(resultSet->getInt(15));
        data.setDecCount(resultSet->getUInt(16));
        data.setRemark(resultSet->getString(17));
        data.setTeachType(resultSet->getInt(18));
        data.setOnTrial(resultSet->getInt(19));
        data.setTrialResult(resultSet->getString(20));
        data.setState(resultSet->getInt(21));
        data.setCloseTime(resultSet->getString(22));
        data.setCloseOperator(resultSet->getInt64(23));
        data.setTeacherId(resultSet->getInt64(24));
        data.setBookable(resultSet->getInt(25));
        data.setSchoolId(resultSet->getInt64(26));
        data.setOrgId(resultSet->getInt64(27));
        return data;
    }
};

class PtrLessonMapper : public Mapper<PtrLessonDO>
{
public:
    PtrLessonDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<LessonDO>();
        data->setId(resultSet->getInt64(1));
        data->setTitle(resultSet->getString(2));
        data->setSn(resultSet->getInt(3));
        data->setCourseId(resultSet->getInt64(4));
        data->setScheduleId(resultSet->getInt64(5));
        data->setClassId(resultSet->getInt64(6));
        data->setRoomId(resultSet->getInt64(7));
        data->setDate(resultSet->getString(8));
        data->setStartTime(resultSet->getString(9));
        data->setEndTime(resultSet->getString(10));
        data->setCreator(resultSet->getInt64(11));
        data->setEditor(resultSet->getInt64(12));
        data->setAddTime(resultSet->getString(13));
        data->setEditTime(resultSet->getString(14));
        data->setDeleted(resultSet->getInt(15));
        data->setDecCount(resultSet->getUInt(16));
        data->setRemark(resultSet->getString(17));
        data->setTeachType(resultSet->getInt(18));
        data->setOnTrial(resultSet->getInt(19));
        data->setTrialResult(resultSet->getString(20));
        data->setState(resultSet->getInt(21));
        data->setCloseTime(resultSet->getString(22));
        data->setCloseOperator(resultSet->getInt64(23));
        data->setTeacherId(resultSet->getInt64(24));
        data->setBookable(resultSet->getInt(25));
        data->setSchoolId(resultSet->getInt64(26));
        data->setOrgId(resultSet->getInt64(27));
        return data;
    }
};

#endif // !_LESSON_MAPPER_