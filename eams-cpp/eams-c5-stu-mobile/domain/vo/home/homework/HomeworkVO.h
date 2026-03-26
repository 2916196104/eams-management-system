#pragma once
#ifndef _HOMEWORK_VO_
#define _HOMEWORK_VO_
#include "../../../GlobalInclude.h"
#include "../../../dto/home/homework/HomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class HomeworkJsonVO : public JsonVO<HomeworkDTO::Wrapper> {
    DTO_INIT(HomeworkJsonVO, JsonVO<HomeworkDTO::Wrapper>)
};

class HomeworkPageJsonVO : public JsonVO<HomeworkPageDTO::Wrapper> {
    DTO_INIT(HomeworkPageJsonVO, JsonVO<HomeworkPageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif