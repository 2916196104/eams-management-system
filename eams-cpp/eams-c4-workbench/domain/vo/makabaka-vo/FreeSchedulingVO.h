#pragma once
#ifndef _FREESCHEDULINGDTO_H_
#define _FREESCHEDULINGDTO_H_
#include"../../GlobalInclude.h"
#include"../../dto/makabaka-dto/FreeSchedulingDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class FreeSchedulingVO: public JsonVO<FreeSchedulingDTO::Wrapper> {
	DTO_INIT(FreeSchedulingVO, JsonVO<FreeSchedulingDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_FREESCHEDULINGDTO_H_