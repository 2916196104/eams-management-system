#pragma once
#ifndef __GRADE_TABLE_PAGE_JSON_VO_H__
#define __GRADE_TABLE_PAGE_JSON_VO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeTableDTO.h"
#include "domain/vo/JsonVO.h"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)




class GradeTableVO : public JsonVO<GradeTableDTO::Wrapper>
{
    DTO_INIT(GradeTableVO, JsonVO<GradeTableDTO::Wrapper>);
};

/* Delete List */
class DeleteListJsonVO : public JsonVO<Vector<Int64>>
{
    DTO_INIT(DeleteListJsonVO, JsonVO<Vector<Int64>>);
};

/* Save List */
class SaveListJsonVO : public JsonVO<Int64>
{
    DTO_INIT(SaveListJsonVO, JsonVO<Int64>);
};

//成绩单分页显示JsonVO对象，用于响应给客户端

class GradeTablePageJsonVO : public JsonVO<GradeTablePageDTO::Wrapper>
{
    DTO_INIT(GradeTablePageJsonVO, JsonVO<GradeTablePageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif 