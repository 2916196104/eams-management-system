#pragma once

#ifndef _HOMEWORKQUERY_H_
#define _HOMEWORKQUERY_H_

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

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORK_QUERY_H_