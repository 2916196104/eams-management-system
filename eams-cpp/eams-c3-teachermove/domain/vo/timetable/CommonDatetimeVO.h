#ifndef __COMMON_DATETIME_VO_H__
#define __COMMON_DATETIME_VO_H__

#include "domain/dto/timetable/CommonDatetimeDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CommonDatetimeJsonVO : public JsonVO<CommonDatetimeDTO::Wrapper>
{
	DTO_INIT(CommonDatetimeJsonVO, JsonVO<CommonDatetimeDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
