#pragma once

#ifndef _GETALLANNOUNCEMENT_DTO_
#define _GETALLANNOUNCEMENT_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配homework表所有字段，严格匹配数据库规范
class AnnouncementDTO : public oatpp::DTO
{
    DTO_INIT(AnnouncementDTO, DTO);

    // ========== 严格对齐 AnnouncementDO 字段（按DO顺序排列） ==========
    // 1. 公告ID（bigint → Int64，对应DO的id）
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("Announcement.field.id"); // 公告ID
    }

    // 2. 公告标题（varchar → String，对应DO的title）
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("Announcement.field.title"); // 公告标题
    }

    // 3. 公告类型（tinyint → Int32，对应DO的type）
    DTO_FIELD(Int32, type);
    DTO_FIELD_INFO(type) {
        info->description = ZH_WORDS_GETTER("Announcement.field.type"); // 公告类型
    }

    // 4. 公告内容（text → String，对应DO的content）
    DTO_FIELD(String, content);
    DTO_FIELD_INFO(content) {
        info->description = ZH_WORDS_GETTER("Announcement.field.content"); // 公告内容
    }

    // 5. 添加时间（datetime → String，对应DO的add_time）
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("Announcement.field.add_time"); // 添加时间
    }

    // 6. 编辑时间（datetime → String，对应DO的edit_time）
    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("Announcement.field.edit_time"); // 编辑时间
    }

    // 7. 编辑人ID（bigint → Int64，对应DO的editor）
    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("Announcement.field.editor"); // 编辑人ID
    }
    //8.cover(图片地址)varchar(255)
    DTO_FIELD(String, cover);
    DTO_FIELD_INFO(cover) {
        info->description = ZH_WORDS_GETTER("Announcement.field.cover"); // 编辑人ID
    }
    // ========== 保留原有Payload字段（统一业务规范） ==========
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配HomeworkDTO，用于分页查询返回
class AnnouncementPageDTO : public PageDTO<AnnouncementDTO::Wrapper>
{
    DTO_INIT(AnnouncementPageDTO, PageDTO<AnnouncementDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_GETALLANNOUNCEMENT_DTO_
