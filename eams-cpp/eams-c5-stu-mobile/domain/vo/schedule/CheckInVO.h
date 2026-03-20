#pragma once
#ifndef _CHECK_IN_VO_H
#define  _CHECK_IN_VO_H
#include"../../dto/schedule/CheckInDTO.h"
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class CheckInJsonVO : public JsonVO<CheckInDTO::Wrapper> {
	DTO_INIT(CheckInJsonVO, JsonVO<CheckInDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif 
