#ifndef __GRADETABLEVO_H__
#define __GRADETABLEVO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeTableDTO.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ�����ͼ��*/


class GradeTableVO : public JsonVO<GradeTableDTO::Wrapper>
{
    DTO_INIT(GradeTableVO, JsonVO<GradeTableDTO::Wrapper>);
};

class RecordListJsonVO : public JsonVO<RecordListDTO::Wrapper>
{
    DTO_INIT(RecordListJsonVO, JsonVO<RecordListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif