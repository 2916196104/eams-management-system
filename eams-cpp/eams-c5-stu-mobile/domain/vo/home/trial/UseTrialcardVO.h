#pragma once
#ifndef _USETRIALCARDVO_H_
#define _USETRIALCARDVO_H_
#include "../../../GlobalInclude.h"
#include "../../../dto/home/trial/UseTrialcardDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class UseTrialcardJsonVO :public JsonVO<UseTrialcardDTO::Wrapper>
{
	DTO_INIT(UseTrialcardJsonVO, JsonVO<UseTrialcardDTO::Wrapper>)
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_USETRIALCARDVO_H_
