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
        if (!resultSet->isNull("id")) data.setId(resultSet->getUInt64("id"));
        if (!resultSet->isNull("title")) data.setTitle(resultSet->getString("title"));
        if (!resultSet->isNull("sn")) data.setSn(resultSet->getInt("sn"));
        if (!resultSet->isNull("course_id")) data.setCourseId(resultSet->getInt64("course_id"));
        if (!resultSet->isNull("schedule_id")) data.setScheduleId(resultSet->getInt64("schedule_id"));
        if (!resultSet->isNull("class_id")) data.setClassId(resultSet->getInt64("class_id"));
        if (!resultSet->isNull("room_id")) data.setRoomId(resultSet->getInt64("room_id"));
        if (!resultSet->isNull("date")) data.setDate(resultSet->getString("date"));
        if (!resultSet->isNull("start_time")) data.setStartTime(resultSet->getString("start_time"));
        if (!resultSet->isNull("end_time")) data.setEndTime(resultSet->getString("end_time"));
        if (!resultSet->isNull("creator")) data.setCreator(resultSet->getInt64("creator"));
        if (!resultSet->isNull("editor")) data.setEditor(resultSet->getInt64("editor"));
        if (!resultSet->isNull("add_time")) data.setAddTime(resultSet->getString("add_time"));
        if (!resultSet->isNull("edit_time")) data.setEditTime(resultSet->getString("edit_time"));
        if (!resultSet->isNull("deleted")) data.setDeleted(resultSet->getBoolean("deleted"));
        if (!resultSet->isNull("dec_count")) data.setDecCount(resultSet->getUInt("dec_count"));
        if (!resultSet->isNull("remark")) data.setRemark(resultSet->getString("remark"));
        if (!resultSet->isNull("teach_type")) data.setTeachType(resultSet->getInt("teach_type"));
        if (!resultSet->isNull("on_trial")) data.setOnTrial(resultSet->getBoolean("on_trial"));
        if (!resultSet->isNull("trial_result")) data.setTrialResult(resultSet->getString("trial_result"));
        if (!resultSet->isNull("state")) data.setState(resultSet->getInt("state"));
        if (!resultSet->isNull("close_time")) data.setCloseTime(resultSet->getString("close_time"));
        if (!resultSet->isNull("close_operator")) data.setCloseOperator(resultSet->getInt64("close_operator"));
        if (!resultSet->isNull("teacher_id")) data.setTeacherId(resultSet->getInt64("teacher_id"));
        if (!resultSet->isNull("bookable")) data.setBookable(resultSet->getBoolean("bookable"));
        if (!resultSet->isNull("school_id")) data.setSchoolId(resultSet->getInt64("school_id"));
        if (!resultSet->isNull("org_id")) data.setOrgId(resultSet->getInt64("org_id"));
        return data;
    }
};

class PtrLessonMapper : public Mapper<PtrLessonDO>
{
public:
    PtrLessonDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<LessonDO>();
        if (!resultSet->isNull("id")) data->setId(resultSet->getUInt64("id"));
        if (!resultSet->isNull("title")) data->setTitle(resultSet->getString("title"));
        if (!resultSet->isNull("sn")) data->setSn(resultSet->getInt("sn"));
        if (!resultSet->isNull("course_id")) data->setCourseId(resultSet->getInt64("course_id"));
        if (!resultSet->isNull("schedule_id")) data->setScheduleId(resultSet->getInt64("schedule_id"));
        if (!resultSet->isNull("class_id")) data->setClassId(resultSet->getInt64("class_id"));
        if (!resultSet->isNull("room_id")) data->setRoomId(resultSet->getInt64("room_id"));
        if (!resultSet->isNull("date")) data->setDate(resultSet->getString("date"));
        if (!resultSet->isNull("start_time")) data->setStartTime(resultSet->getString("start_time"));
        if (!resultSet->isNull("end_time")) data->setEndTime(resultSet->getString("end_time"));
        if (!resultSet->isNull("creator")) data->setCreator(resultSet->getInt64("creator"));
        if (!resultSet->isNull("editor")) data->setEditor(resultSet->getInt64("editor"));
        if (!resultSet->isNull("add_time")) data->setAddTime(resultSet->getString("add_time"));
        if (!resultSet->isNull("edit_time")) data->setEditTime(resultSet->getString("edit_time"));
        if (!resultSet->isNull("deleted")) data->setDeleted(resultSet->getBoolean("deleted"));
        if (!resultSet->isNull("dec_count")) data->setDecCount(resultSet->getUInt("dec_count"));
        if (!resultSet->isNull("remark")) data->setRemark(resultSet->getString("remark"));
        if (!resultSet->isNull("teach_type")) data->setTeachType(resultSet->getInt("teach_type"));
        if (!resultSet->isNull("on_trial")) data->setOnTrial(resultSet->getBoolean("on_trial"));
        if (!resultSet->isNull("trial_result")) data->setTrialResult(resultSet->getString("trial_result"));
        if (!resultSet->isNull("state")) data->setState(resultSet->getInt("state"));
        if (!resultSet->isNull("close_time")) data->setCloseTime(resultSet->getString("close_time"));
        if (!resultSet->isNull("close_operator")) data->setCloseOperator(resultSet->getInt64("close_operator"));
        if (!resultSet->isNull("teacher_id")) data->setTeacherId(resultSet->getInt64("teacher_id"));
        if (!resultSet->isNull("bookable")) data->setBookable(resultSet->getBoolean("bookable"));
        if (!resultSet->isNull("school_id")) data->setSchoolId(resultSet->getInt64("school_id"));
        if (!resultSet->isNull("org_id")) data->setOrgId(resultSet->getInt64("org_id"));
        return data;
    }
};

#endif // !_LESSON_MAPPER_