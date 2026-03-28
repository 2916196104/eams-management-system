#pragma once

#ifndef _ATTACHMENTDO_H_
#define _ATTACHMENTDO_H_

#include "../DoInclude.h"

class AttachmentDO : public BaseDO
{
    // 主键ID
    MYSQL_SYNTHESIZE(long long, id, Id);

    // 文件原名
    MYSQL_SYNTHESIZE(string, fileName, FileName);

    // 附件大小
    MYSQL_SYNTHESIZE(int, fileSize, FileSize);

    // 附件类型
    MYSQL_SYNTHESIZE(string, fileType, FileType);

    // 附件名称
    MYSQL_SYNTHESIZE(string, name, Name);

    // 附件地址
    MYSQL_SYNTHESIZE(string, url, Url);

    // 保存路径
    MYSQL_SYNTHESIZE(string, savePath, SavePath);

    // 添加时间
    MYSQL_SYNTHESIZE(string, addTime, AddTime);

    // 创建人
    MYSQL_SYNTHESIZE(long long, creator, Creator);

public:
    AttachmentDO() : BaseDO("attachment")
    {
        MYSQL_ADD_FIELD_PK("id", "i", id);

        MYSQL_ADD_FIELD("file_name", "s", fileName);
        MYSQL_ADD_FIELD("file_size", "i", fileSize);
        MYSQL_ADD_FIELD("file_type", "s", fileType);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("url", "s", url);
        MYSQL_ADD_FIELD("save_path", "s", savePath);
        MYSQL_ADD_FIELD("add_time", "s", addTime);
        MYSQL_ADD_FIELD("creator", "ll", creator);
    }
};

// 智能指针别名
typedef std::shared_ptr<AttachmentDO> PtrAttachmentDO;

#endif // _ATTACHMENTDO_H_