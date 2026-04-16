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
        dto->classId = rs->isNull("class_id") ? 0 : rs->getUInt64("class_id");
        dto->title = rs->isNull("title") ? "" : rs->getString("title").asStdString();
        dto->addTime = rs->isNull("add_time") ? "" : rs->getString("add_time").asStdString();
        dto->creator = rs->isNull("creator") ? 0 : rs->getUInt64("creator");
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
        dto->title = rs->isNull("title") ? "" : rs->getString("title").asStdString();
        dto->content = rs->isNull("content") ? "" : rs->getString("content").asStdString();
        dto->creator = rs->isNull("creator") ? 0 : rs->getUInt64("creator");
        dto->editor = rs->isNull("editor") ? 0 : rs->getUInt64("editor");
        dto->addTime = rs->isNull("add_time") ? "" : rs->getString("add_time").asStdString();
        dto->editTime = rs->isNull("edit_time") ? "" : rs->getString("edit_time").asStdString();
        dto->orgId = rs->isNull("org_id") ? 0 : rs->getUInt64("org_id");
        return dto;
    }
};

class PtrHomeworkMapper : public Mapper<PtrHomeworkDO>
{
public:
    PtrHomeworkDO mapper(ResultSet* resultSet) const override
    {
        PtrHomeworkDO homeworkDO = std::make_shared<HomeworkDO>();

        homeworkDO->setId(resultSet->getUInt64("id"));

        homeworkDO->setClassId(resultSet->getUInt64("class_id"));
        homeworkDO->setTitle(resultSet->getString("title"));
        homeworkDO->setContent(resultSet->getString("content"));
        homeworkDO->setCreator(resultSet->getUInt64("creator"));
        homeworkDO->setEditor(resultSet->getUInt64("editor"));
        homeworkDO->setAddTime(resultSet->getString("add_time"));
        homeworkDO->setEditTime(resultSet->getString("edit_time"));
        homeworkDO->setDeleted(resultSet->getInt("deleted"));
        homeworkDO->setOrgId(resultSet->getUInt64("org_id"));
        return homeworkDO;
    }
};
#endif 
