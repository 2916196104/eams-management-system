#include "stdafx.h"
#include "AttachmentDAO.h"
#include "AttachmentMapper.h"
#include <iostream>

uint64_t AttachmentDAO::insertAttachment(const AttachmentDO& attachment) {
    std::string sql = R"(
        INSERT INTO attachment 
        (id, file_name, file_size, file_type, name, url, save_path, add_time)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    )";

   

    // 1. 保存所有字符串到局部变量，避免临时对象
    std::string fileName = attachment.getFileName();
    std::string fileType = attachment.getFileType();
    std::string name = attachment.getName();
    std::string url = attachment.getUrl();
    std::string savePath = attachment.getSavePath();
    std::string addTime = attachment.getAddTime();

 

    // 2. 执行插入
    uint64_t newId = sqlSession->executeUpdate(sql,
        "%ll%s%i%s%s%s%s%s",
        attachment.getId(),
        fileName,
        attachment.getFileSize(),  
        fileType,
        name,
        url,
        savePath,
        addTime
    );

    
    return newId;  // 返回自增主键
}