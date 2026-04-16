#ifndef __GET_STU_LIST_VO_H__
#define __GET_STU_LIST_VO_H__

#include "domain/dto/timetable/GetStuListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetStuListJsonVO : public JsonVO<GetStuListDTO::Wrapper>
{
	DTO_INIT(GetStuListJsonVO, JsonVO<GetStuListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
