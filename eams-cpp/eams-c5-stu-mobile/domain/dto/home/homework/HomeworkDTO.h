#pragma once

#ifndef _HOMEWORK_DTO_
#define _HOMEWORK_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配homework表所有字段，严格匹配数据库规范
class HomeworkDTO : public oatpp::DTO
{
    DTO_INIT(HomeworkDTO, DTO);

    // ========== 严格对应homework表字段（按表字段顺序排列） ==========
    // 1. 主键ID（bigint unsigned → Int64）
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("Homework.field.id");
    }

    // 2. 班级ID（bigint → Int64，NOT NULL）
    DTO_FIELD(Int64, class_id);
    DTO_FIELD_INFO(class_id) {
        info->description = ZH_WORDS_GETTER("Homework.field.class_id");
    }

    // 3. 标题（varchar(255) → String，NOT NULL）
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("Homework.field.title");
    }

    // 4. 内容（text → String，NOT NULL）
    DTO_FIELD(String, content);
    DTO_FIELD_INFO(content) {
        info->description = ZH_WORDS_GETTER("Homework.field.content");
    }

    // 5. 创建人（bigint → Int64，DEFAULT NULL）
    DTO_FIELD(Int64, creator);
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("Homework.field.creator");
    }

    // 6. 编辑人（bigint → Int64，DEFAULT NULL）
    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("Homework.field.editor");
    }

    // 7. 添加时间（datetime → String）
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("Homework.field.add_time");
    }

    // 8. 编辑时间（datetime → String）
    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("Homework.field.edit_time");
    }

    // 9. 删除标记（tinyint(1) → Boolean，DEFAULT '0'）
    DTO_FIELD(Boolean, deleted);
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("Homework.field.deleted");
    }

    // 10. 创建者所属组织ID（bigint → Int64，DEFAULT NULL）
    DTO_FIELD(Int64, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("Homework.field.org_id");
    }

    // 保留Payload字段（统一业务规范）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配HomeworkDTO，用于分页查询返回
class HomeworkPageDTO : public PageDTO<HomeworkDTO::Wrapper>
{
    DTO_INIT(HomeworkPageDTO, PageDTO<HomeworkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_HOMEWORK_DTO_