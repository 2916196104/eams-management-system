#pragma once
#ifndef _CREDITMALLLIST_VO_
#define _CREDITMALLLIST_VO_

#include "../../../GlobalInclude.h"
#include "../../../dto/home/credit/CreditmalllistDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class CreditmalllistJsonVO : public JsonVO<CreditMallDTO::Wrapper> {
	DTO_INIT(CreditmalllistJsonVO, JsonVO<CreditMallDTO::Wrapper>)
};

class CreditmalllistPageJsonVO : public JsonVO<CreditMallPageDTO::Wrapper> {
	DTO_INIT(CreditmalllistPageJsonVO, JsonVO<CreditMallPageDTO::Wrapper>)
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDITMALLLIST_VO_