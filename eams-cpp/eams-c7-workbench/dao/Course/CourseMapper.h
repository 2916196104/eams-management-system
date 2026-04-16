#pragma once
#ifndef _COURSEMAPPER_H_
#define _COURSEMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/Course/CourseDO.h"

class CourseMapper : public Mapper<CourseDO>
{
public:
    CourseDO mapper(ResultSet* resultSet) const override
    {
        CourseDO data;
        data.setCourseId(resultSet->getString(1));
        data.setCourseName(resultSet->getString(2));
        data.setSubjectId(resultSet->getInt(3));
        data.setSubjectName(resultSet->getString(4));
        data.setLessonType(resultSet->getString(5));
        data.setCourseNum(resultSet->getInt(6));
        data.setCoursePrice(resultSet->getInt(7));
        data.setExpireMonths(resultSet->getInt(8));
        data.setStartTime(resultSet->getString(9));
        data.setEndTime(resultSet->getString(10));
        data.setTip(resultSet->getString(11));
        return data;
    }
};

class PtrCourseMapper : public Mapper<PtrCourseDO>
{
public:
    PtrCourseDO mapper(ResultSet* resultSet) const override
    {
        auto data = make_shared<CourseDO>();
        data->setCourseId(resultSet->getString(1));
        data->setCourseName(resultSet->getString(2));
        data->setSubjectId(resultSet->getInt(3));
        data->setSubjectName(resultSet->getString(4));
        data->setLessonType(resultSet->getString(5));
        data->setCourseNum(resultSet->getInt(6));
        data->setCoursePrice(resultSet->getInt(7));
        data->setExpireMonths(resultSet->getInt(8));
        data->setStartTime(resultSet->getString(9));
        data->setEndTime(resultSet->getString(10));
        data->setTip(resultSet->getString(11));
        return data;
    }
};

#endif