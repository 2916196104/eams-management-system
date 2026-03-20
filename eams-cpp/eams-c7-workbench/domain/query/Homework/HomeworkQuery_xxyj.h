#pragma once

#ifndef _HOMEWORKQUERY_XXYJ_H_
#define _HOMEWORKQUERY_XXYJ_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 获取作业详情查询参数
 */
class HomeworkDetailQuery : public oatpp::DTO
{
    DTO_INIT(HomeworkDetailQuery, DTO);

    // 作业ID
    API_DTO_FIELD_REQUIRE(Int64, homeworkId, ZH_WORDS_GETTER("homework.field.id"), true);
};

/**
 * 作业提交记录列表查询参数
 */
class HomeworkRecordListQuery : public oatpp::DTO
{
    DTO_INIT(HomeworkRecordListQuery, DTO);

    // 作业ID
    API_DTO_FIELD_REQUIRE(Int64, homeworkId, ZH_WORDS_GETTER("homework.field.id"), true);

    // 提交状态（可选）
    API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("homework.field.status"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKQUERY_XXYJ_H_