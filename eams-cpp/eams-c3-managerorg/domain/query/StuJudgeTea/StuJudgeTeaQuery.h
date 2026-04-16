#pragma once
#ifndef _STU_JUDGE_TEA_QUERY_H_
#define _STU_JUDGE_TEA_QUERY_H_

#include "domain/GlobalInclude.h" 
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//学评教查询类：接收前端筛选+分页参数（所有字段非必传)
class StuJudgeTeaQuery : public PageQuery
{
    DTO_INIT(StuJudgeTeaQuery, PageQuery);

    // 1. 授课老师ID（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, teacherId, ZH_WORDS_GETTER("StuJudgeTeaDTO.teacherId"));
    // 2. 学员ID（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("StuJudgeTeaDTO.studentId"));
    // 3. 课次id（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("StuJudgeTeaDTO.lessonId"));
    // 4. 评价时间范围（非必传）
    API_DTO_FIELD_DEFAULT(String, startEvaluateTime, ZH_WORDS_GETTER("StuJudgeTeaDTO.startEvaluateTime"));
    API_DTO_FIELD_DEFAULT(String, endEvaluateTime, ZH_WORDS_GETTER("StuJudgeTeaDTO.endEvaluateTime"));
    // 5. 最低综合评分（筛选条件，非必传）
    //API_DTO_FIELD_DEFAULT(UInt32, minComprehensiveScore, ZH_WORDS_GETTER("StuJudgeTeaDTO.minComprehensiveScore"));
    // 6. 是否匿名
    API_DTO_FIELD_DEFAULT(Int32, anonymity, ZH_WORDS_GETTER("StuJudgeTeaDTO.anonymity"));
};

#include OATPP_CODEGEN_END(DTO)

#endif