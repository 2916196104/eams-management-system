#pragma once
#ifndef _ANNOUNCEMENT_MAPPER_
#define _ANNOUNCEMENT_MAPPER_

#include "Mapper.h"
#include "../../../domain/do/home/announcement/AnnouncementDO.h"

/**
 *  æ¿˝±Ì◊÷∂Œ∆•≈‰”≥…‰
 */
class AnnouncementMapper : public Mapper<AnnouncementDO>
{
public:
    AnnouncementDO mapper(ResultSet* resultSet) const override
    {
        AnnouncementDO data;
        // ”≥…‰À≥–Ú—œ∏Ò∂‘∆Î£∫id °˙ title °˙ type °˙ content °˙ add_time °˙ edit_time °˙ editor
        data.setId(resultSet->getUInt64(1));       // id (bigint °˙ uint64_t)
        data.setTitle(resultSet->getString(2));    // title (varchar °˙ string)
        data.setType(resultSet->getInt(3));        // type (tinyint °˙ int)
        data.setContent(resultSet->getString(4));  // content (text °˙ string)
        data.setAdd_time(resultSet->getString(5)); // add_time (datetime °˙ string)
        data.setEdit_time(resultSet->getString(6));// edit_time (datetime °˙ string)
        data.setEditor(resultSet->getUInt64(7));   // editor (bigint °˙ uint64_t)
        return data;
    }
};

// ÷«ƒ‹÷∏’Î∞Ê Mapper£®  ≈‰ PtrAnnouncementDO£©
class PtrAnnouncementMapper : public Mapper<PtrAnnouncementDO>
{
public:
    PtrAnnouncementDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<AnnouncementDO>();
        // Õ¨ª˘¥°∞Ê”≥…‰¬ﬂº≠£¨À≥–ÚÕÍ»´“ª÷¬
        data->setId(resultSet->getUInt64(1));
        data->setTitle(resultSet->getString(2));
        data->setType(resultSet->getInt(3));
        data->setContent(resultSet->getString(4));
        data->setAdd_time(resultSet->getString(5));
        data->setEdit_time(resultSet->getString(6));
        data->setEditor(resultSet->getUInt64(7));
        return data;
    }
};

#endif // !_ANNOUNCEMENT_MAPPER_