#ifndef __GRADETABLEVO_H__
#define __GRADETABLEVO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeListDTO.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ�����ͼ��*/


class GradeTableVO : public
{
	DTO_INIT(GradeTableVO, )
};

class GradeListJsonVO : public JsonVO<GradeListDTO::Wrapper>
{
    DTO_INIT(GradeListJsonVO, JsonVO<GradeListDTO::Wrapper>);
};

class GradeListPageJsonVO : public JsonVO<GradeListPageDTO::Wrapper>
{
    DTO_INIT(GradeListPageJsonVO, JsonVO<GradeListPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif