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
        info->description = ZH_WORDS_GETTER("Announcement.field.id");
    }
    // 2. 标题（varchar(255) → String，NOT NULL）
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("Announcement.field.title");
    }

    // 3. 类型 学生端首页Banner  学生端首页提示  学生端首页弹窗（tinyint(1) → Boolean，DEFAULT '0',默认值1）
    DTO_FIELD(String, type);
    DTO_FIELD_INFO(type) {
        info->description = ZH_WORDS_GETTER("Announcement.field.content");
    }
    //4.发送内容(text)
    DTO_FIELD(String, content);
    DTO_FIELD_INFO(content) {
        info->description = ZH_WORDS_GETTER("Announcement.field.content");
    }//5.?varchar(255)
    DTO_FIELD(String, cover);
    DTO_FIELD_INFO(cover) {
        info->description = ZH_WORDS_GETTER("Announcementfield.cover");
    }
    // 6. 创建人（bigint → Int64，DEFAULT NULL）
    DTO_FIELD(Int64, creator);
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("Announcement.field.creator");
    }
    // 7. 添加时间（datetime → String）
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("Announcement.field.add_time");
    }
    // 8. 删除标记（tinyint(1) → Boolean，DEFAULT '0'）
    DTO_FIELD(Boolean, deleted);
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("Announcement.field.deleted");
    }
    // 9. 编辑时间（datetime → String）
    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("Announcement.field.edit_time");
    }
    // 10. 编辑人（bigint → Int64，DEFAULT NULL）
    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("Announcement.field.editor");
    }
    //11.状态（tinyint(1) → Boolean，DEFAULT '0'）
    DTO_FIELD(Boolean, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("Announcement.field.state");
    }
    //12.?int
    DTO_FIELD(Int64, sort_num);
    DTO_FIELD_INFO(sort_num) {
        info->description = ZH_WORDS_GETTER("Announcement.field.sort_num");
    }
    //13.唯一码varchar(50)
    DTO_FIELD(String, code);
    DTO_FIELD_INFO(code) {
        info->description = ZH_WORDS_GETTER("Announcement.field.code");
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
