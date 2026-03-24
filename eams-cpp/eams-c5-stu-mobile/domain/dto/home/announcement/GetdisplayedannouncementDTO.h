#pragma once

#ifndef _GETALLANNOUNCEMENT_DTO_
#define _GETALLANNOUNCEMENT_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配homework表所有字段，严格匹配数据库规范
class AnnouncementDTO : public oatpp::DTO
{
    DTO_INIT(AnnouncementDTO, DTO);

    // ========== 严格对应homework表字段（按表字段顺序排列） ==========
    // 1. 主键ID（bigint unsigned → Int64）
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.Announcement.field.id");
    }

    // 保留Payload字段（统一业务规范）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配HomeworkDTO，用于分页查询返回
class AnnouncementPageDTO : public PageDTO<AnnouncementDTO::Wrapper>
{
    DTO_INIT(AnnouncementPageDTO, PageDTO<AnnouncementDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_GETALLANNOUNCEMENT_DTO_