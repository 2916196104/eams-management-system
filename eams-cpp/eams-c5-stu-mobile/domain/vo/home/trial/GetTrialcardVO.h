#pragma once
#ifndef _GETTRIALCARDVO_H_
#define _GETTRIALCARDVO_H_
#include "../../../GlobalInclude.h"
#include "../../../dto/home/trial/GetTrialcardDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class GetTrialcardJsonVO :public JsonVO<GetTrialcardDTO::Wrapper>
{
	DTO_INIT(GetTrialcardJsonVO, JsonVO<GetTrialcardDTO::Wrapper>)
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_GETTRIALCARDVO_H_
