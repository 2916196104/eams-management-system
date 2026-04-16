#pragma once
#ifndef __TEA_JUDGE_STU_QUERY_H__
#define __TEA_JUDGE_STU_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//教评学查询类：接收前端筛选+分页参数（所有字段非必传）
class TeaJudgeStuQuery : public PageQuery
{
    DTO_INIT(TeaJudgeStuQuery, PageQuery);

    // 1. 点评老师ID（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, teacherId, ZH_WORDS_GETTER("TeaJudgeStuDTO.teacherId"));
    // 2. 学员ID（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("TeaJudgeStuDTO.studentId"));
    // 3. 课次标题（模糊查询，非必传）
    API_DTO_FIELD_DEFAULT(String, lessonTitle, ZH_WORDS_GETTER("TeaJudgeStuDTO.lessonTitle"));
    // 4. 点评时间范围（非必传）
    API_DTO_FIELD_DEFAULT(String, startEvaluateTime, ZH_WORDS_GETTER("TeaJudgeStuDTO.startEvaluateTime"));
    API_DTO_FIELD_DEFAULT(String, endEvaluateTime, ZH_WORDS_GETTER("TeaJudgeStuDTO.endEvaluateTime"));
    // 5. 最低点评得分（筛选条件，非必传）
    API_DTO_FIELD_DEFAULT(UInt32, minEvaluateScore, ZH_WORDS_GETTER("TeaJudgeStuDTO.minEvaluateScore"));
};

#include OATPP_CODEGEN_END(DTO)

#endif 