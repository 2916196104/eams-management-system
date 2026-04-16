#pragma once
#ifndef _NOTICE_MAPPER_H_
#define _NOTICE_MAPPER_H_

#include "Mapper.h"
#include "../../domain/do/Board/NoticeDO.h"

/**
 * 公告表字段映射器
 */
class NoticeMapper : public Mapper<NoticeDO>
{
public:
    NoticeDO mapper(ResultSet* resultSet) const override
    {
        NoticeDO data;
        data.setId(resultSet->getInt64("id"));
        data.setTitle(resultSet->getString("title"));
        data.setContent(resultSet->getString("content"));
        data.setViewNum(resultSet->getInt("view_num"));
        data.setCreator(resultSet->getInt64("creator"));
        data.setEditor(resultSet->getInt64("editor"));
        data.setAddTime(resultSet->getString("add_time"));
        data.setEditTime(resultSet->getString("edit_time"));
        data.setDeleted(resultSet->getInt("deleted"));
        return data;
    }
};

/**
 * 智能指针版本映射器
 */
class PtrNoticeMapper : public Mapper<PtrNoticeDO>
{
public:
    PtrNoticeDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<NoticeDO>();
        data->setId(resultSet->getInt64("id"));
        data->setTitle(resultSet->getString("title"));
        data->setContent(resultSet->getString("content"));
        data->setViewNum(resultSet->getInt("view_num"));
        data->setCreator(resultSet->getInt64("creator"));
        data->setEditor(resultSet->getInt64("editor"));
        data->setAddTime(resultSet->getString("add_time"));
        data->setEditTime(resultSet->getString("edit_time"));
        data->setDeleted(resultSet->getInt("deleted"));
        return data;
    }
};

#endif // _NOTICE_MAPPER_H_