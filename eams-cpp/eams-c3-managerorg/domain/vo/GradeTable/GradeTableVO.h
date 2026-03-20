#pragma once
#ifndef __GRADE_TABLE_PAGE_JSON_VO_H__
#define __GRADE_TABLE_PAGE_JSON_VO_H__

#include "domain/GlobalInclude.h"

#include "domain/dto/GradeTable/GradeTableDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)


 //成绩单分页显示JsonVO对象，用于响应给客户端

class GradeTablePageJsonVO : public JsonVO<GradeTablePageDTO::Wrapper>
{
    DTO_INIT(GradeTablePageJsonVO, JsonVO<GradeTablePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif 