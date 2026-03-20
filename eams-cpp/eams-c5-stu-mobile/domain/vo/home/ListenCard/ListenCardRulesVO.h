#pragma once
#ifndef LISTEN_CARD_RULES_VO_H
#define LISTEN_CARD_RULES_VO_H

#include"../../../GlobalInclude.h"
#include"../../../dto/home/ListenCard/ListenCardRulesDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class ListenCardRulesJsonVO : public JsonVO<ListenCardRulesDTO::Wrapper> {
	DTO_INIT(ListenCardRulesJsonVO, JsonVO<ListenCardRulesDTO::Wrapper>)
};


#include OATPP_CODEGEN_END(DTO)
#endif 
