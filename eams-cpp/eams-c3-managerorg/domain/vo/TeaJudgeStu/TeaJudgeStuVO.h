#pragma once
#ifndef __TEA_JUDGE_STU_PAGE_JSON_VO_H__
#define __TEA_JUDGE_STU_PAGE_JSON_VO_H__

#include "domain/GlobalInclude.h"

#include "domain/dto/TeaJudgeStu/TeaJudgeStuDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

 //教评学分页显示JsonVO对象，用于响应给客户端

class TeaJudgeStuPageJsonVO : public JsonVO<TeaJudgeStuPageDTO::Wrapper>
{
    DTO_INIT(TeaJudgeStuPageJsonVO, JsonVO<TeaJudgeStuPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif 