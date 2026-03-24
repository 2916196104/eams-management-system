#pragma once
#ifndef _HOMEWORK_MAPPER_H_
#define _HOMEWORK_MAPPER_H_

#include "Mapper.h"
#include "domain/dto/homework/homeworkDTO.h"

class HomeworkMapper : public Mapper<HomeworkDTO::Wrapper>
{
public:
    HomeworkDTO::Wrapper mapper(ResultSet* rs) const override
    {
        auto dto = HomeworkDTO::createShared();
        dto->id = rs->getUInt64("id");
        dto->title = rs->getString("title").asStdString();
        dto->courseName = rs->getString("course_name").asStdString();
        dto->teacherName = rs->getString("teacher_name").asStdString();
        return dto;
    }
};

class HomeworkDetailMapper : public Mapper<HomeworkDetailDTO::Wrapper>
{
public:
    HomeworkDetailDTO::Wrapper mapper(ResultSet* rs) const override
    {
        auto dto = HomeworkDetailDTO::createShared();
        dto->id = rs->getUInt64("id");
        dto->title = rs->getString("title").asStdString();
        dto->courseName = rs->getString("course_name").asStdString();
        dto->startTime = rs->getString("start_time").asStdString();
        dto->endTime = rs->getString("end_time").asStdString();
        dto->teacherName = rs->getString("teacher_name").asStdString();
        return dto;
    }
};

#endif 
