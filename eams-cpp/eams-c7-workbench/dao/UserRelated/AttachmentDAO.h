#pragma once
#ifndef _ATTACHMENT_DAO_H_
#define _ATTACHMENT_DAO_H_

#include "BaseDAO.h"
#include "domain/do/UserRelated/AttachmentDO.h"

class AttachmentDAO : public BaseDAO {
public:
    // 插入附件记录，返回新记录的 id（主键），失败返回 0
    uint64_t insertAttachment(const AttachmentDO& attachment);
};

#endif // _ATTACHMENT_DAO_H_