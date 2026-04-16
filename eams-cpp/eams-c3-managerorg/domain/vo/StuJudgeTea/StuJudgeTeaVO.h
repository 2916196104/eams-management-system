#pragma once
#ifndef __STU_JUDGE_TEA_PAGE_JSON_VO_H__
#define __STU_JUDGE_TEA_PAGE_JSON_VO_H__

#include "domain/GlobalInclude.h"

#include "domain/dto/StuJudgeTea/StuJudgeTeaDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


//学评教分页显示JsonVO对象，用于响应给客户端

class StuJudgeTeaPageJsonVO : public JsonVO<StuJudgeTeaPageDTO::Wrapper>
{
    DTO_INIT(StuJudgeTeaPageJsonVO, JsonVO<StuJudgeTeaPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif