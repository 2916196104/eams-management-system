#pragma once

#ifndef _GETALLANNOUNCEMENT_QUERY_
#define _GETALLANNOUNCEMENT_QUERY_
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
// 类名修正+继承PageQuery，符合OATPP DTO规范
class AnnouncementQuery : public PageQuery
{
    DTO_INIT(AnnouncementQuery, PageQuery); // 初始化宏匹配类名

    // ========== 适配homework表的查询字段 ==========
    //// 1. 班级ID（核心查询字段，匹配homework表class_id）
    //DTO_FIELD(Int64, class_id);
    //DTO_FIELD_INFO(class_id) {
    //    info->description = ZH_WORDS_GETTER("Homework.field.class_id");
    //}

    //// 2. 删除标记（可选查询字段，匹配homework表deleted）
    //DTO_FIELD(Boolean, deleted);
    //DTO_FIELD_INFO(deleted) {
    //    info->description = ZH_WORDS_GETTER("Homework.field.deleted");
    //}

    //// 3. 创建人（可选查询字段，匹配homework表creator）
    //DTO_FIELD(Int64, creator);
    //DTO_FIELD_INFO(creator) {
    //    info->description = ZH_WORDS_GETTER("Homework.field.creator");
    //}

    //// 4. 组织ID（可选查询字段，匹配homework表org_id）
    //DTO_FIELD(Int64, org_id);
    //DTO_FIELD_INFO(org_id) {
    //    info->description = ZH_WORDS_GETTER("Homework.field.org_id");
    //}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_GETALLANNOUNCEMENT_QUERY_
