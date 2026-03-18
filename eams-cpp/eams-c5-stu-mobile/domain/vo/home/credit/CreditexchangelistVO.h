#pragma once
#ifndef _CREDITEXCHANGELIST_VO_
#define _CREDITEXCHANGELIST_VO_

#include "../../../GlobalInclude.h"
#include "../../../dto/home/credit/CreditexchangelistDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class CreditexchangelistJsonVO : public JsonVO<CreditexchangelistDTO::Wrapper> {
	DTO_INIT(CreditexchangelistJsonVO, JsonVO<CreditexchangelistDTO::Wrapper>)
};

class CreditexchangelistPageJsonVO : public JsonVO<CreditexchangelistPageDTO::Wrapper> {
	DTO_INIT(CreditexchangelistPageJsonVO, JsonVO<CreditexchangelistPageDTO::Wrapper>)
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDITEXCHANGELIST_VO_