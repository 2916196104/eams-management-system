#pragma once
#ifndef _GETTRIALCARDLISTDTO_
#define _GETTRIALCARDLISTDTO_

#include "../../../GlobalInclude.h"
#include "domain/dto/home/trialCard/GetTrialCardListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class GetTrialCardListJsonVO : public JsonVO<GetTrialCardListDTO::Wrapper>
{
	DTO_INIT(GetTrialCardListJsonVO, JsonVO<GetTrialCardListDTO::Wrapper>)
};

class GetTrialCardListPageJsonVO :public JsonVO<GetTrialCardListPageDTO::Wrapper>
{
	DTO_INIT(GetTrialCardListPageJsonVO, JsonVO<GetTrialCardListPageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_GETTRIALCARDLISTDTO_