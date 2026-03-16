#ifndef __GET_DETAIL_CS_VO_H__
#define __GET_DETAIL_CS_VO_H__

#include "domain/dto/timetable/GetDetailCSDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetDetailCSJsonVO : public JsonVO<GetDetailCSDTO::Wrapper>
{
	DTO_INIT(GetDetailCSJsonVO, JsonVO<GetDetailCSDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
