#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeListDTO.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GradeListJsonVO : public JsonVO<GradeListDTO::Wrapper>
{
    DTO_INIT(GradeListJsonVO, JsonVO<GradeListDTO::Wrapper>);
};

class GradeListPageJsonVO : public JsonVO<GradeListPageDTO::Wrapper>
{
    DTO_INIT(GradeListPageJsonVO, JsonVO<GradeListPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)