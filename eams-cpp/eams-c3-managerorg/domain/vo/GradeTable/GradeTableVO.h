#ifndef __GRADETABLEVO_H__
#define __GRADETABLEVO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeTableDTO.h"
#include "domain/vo/JsonVO.h"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ�����ͼ��*/


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
class SaveListJsonVO : public JsonVO<Vector<Int64>>
{
    DTO_INIT(SaveListJsonVO, JsonVO<Vector<Int64>>);
};

#include OATPP_CODEGEN_END(DTO)

#endif