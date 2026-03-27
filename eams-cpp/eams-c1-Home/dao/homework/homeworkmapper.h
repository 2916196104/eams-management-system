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
        dto->classId = rs->getUInt64("class_id");
        dto->title = rs->getString("title").asStdString();
        dto->addTime = rs->getString("add_time").asStdString();
        dto->creator = rs->getUInt64("creator");
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
        dto->classId = rs->getUInt64("class_id");
        dto->title = rs->getString("title").asStdString();
        dto->content = rs->getString("content").asStdString();
        dto->creator = rs->getUInt64("creator");
        dto->editor = rs->getUInt64("editor");
        dto->addTime = rs->getString("add_time").asStdString();
        dto->editTime = rs->getString("edit_time").asStdString();
        dto->orgId = rs->getUInt64("org_id");
        return dto;
    }
};

#endif 
