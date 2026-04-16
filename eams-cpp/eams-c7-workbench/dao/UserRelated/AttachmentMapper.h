#pragma once
#ifndef _ATTACHMENT_MAPPER_H_
#define _ATTACHMENT_MAPPER_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/AttachmentDO.h"

class AttachmentMapper : public Mapper<PtrAttachmentDO> {
public:
    PtrAttachmentDO mapper(ResultSet* resultSet) const override {
        auto attachment = std::make_shared<AttachmentDO>();
        attachment->setId(resultSet->getInt64("id"));
        attachment->setFileName(resultSet->getString("file_name"));
        attachment->setFileSize(resultSet->getInt("file_size"));
        attachment->setFileType(resultSet->getString("file_type"));
        attachment->setName(resultSet->getString("name"));
        attachment->setUrl(resultSet->getString("url"));
        attachment->setSavePath(resultSet->getString("save_path"));
        attachment->setAddTime(resultSet->getString("add_time"));
        attachment->setCreator(resultSet->getInt64("creator"));
        return attachment;
    }
};

#endif // _ATTACHMENT_MAPPER_H_