#pragma once

#ifndef _CARD_MAPPER_H_
#define _CARD_MAPPER_H_

#include "Mapper.h"
#include "domain/do/listening-card/cardDO.h"

/**
 * 试听卡表字段匹配映射 - 返回普通对象
 */
class CardMapper : public Mapper<CardDO>
{
public:
    CardDO mapper(ResultSet* resultSet) const override
    {
        CardDO data;
        // 列索引必须与 SELECT 语句中的字段顺序一致
        data.setId(resultSet->getUInt64(1));           // id
        data.setCourseId(resultSet->getUInt64(2));     // course_id
        data.setTitle(resultSet->getString(3));        // title
        data.setQuantity(resultSet->getInt(4));        // quantity
        data.setRemainingQuantity(resultSet->getInt(5)); // remaining_quantity
        data.setLessonCount(resultSet->getInt(6));     // lesson_count
        data.setExpireDays(resultSet->getInt(7));      // expire_days
        data.setEndDate(resultSet->getString(8));      // end_date
        data.setState(resultSet->getInt(9) != 0);      // state (tinyint -> bool)
        data.setCreator(resultSet->getUInt64(10));     // creator
        data.setEditor(resultSet->getUInt64(11));      // editor
        data.setAddTime(resultSet->getString(12));     // add_time
        data.setEditTime(resultSet->getString(13));    // edit_time
        data.setDeleted(resultSet->getInt(14) != 0);   // deleted (tinyint -> bool)
        data.setOrgId(resultSet->getUInt64(15));       // org_id
        return data;
    }
};

/**
 * 试听卡表字段匹配映射 - 返回智能指针对象
 */
class PtrCardMapper : public Mapper<PtrCardDO>
{
public:
    PtrCardDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<CardDO>();
        data->setId(resultSet->getUInt64(1));
        data->setCourseId(resultSet->getUInt64(2));
        data->setTitle(resultSet->getString(3));
        data->setQuantity(resultSet->getInt(4));
        data->setRemainingQuantity(resultSet->getInt(5));
        data->setLessonCount(resultSet->getInt(6));
        data->setExpireDays(resultSet->getInt(7));
        data->setEndDate(resultSet->getString(8));
        data->setState(resultSet->getInt(9) != 0);
        data->setCreator(resultSet->getUInt64(10));
        data->setEditor(resultSet->getUInt64(11));
        data->setAddTime(resultSet->getString(12));
        data->setEditTime(resultSet->getString(13));
        data->setDeleted(resultSet->getInt(14) != 0);
        data->setOrgId(resultSet->getUInt64(15));
        return data;
    }
};

#endif // !_CARD_MAPPER_H_