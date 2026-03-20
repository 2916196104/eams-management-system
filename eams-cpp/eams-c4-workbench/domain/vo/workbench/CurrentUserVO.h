#pragma once
#ifndef _CURRENT_USER_VO_H_
#define _CURRENT_USER_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/workbench/CurrentUserDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CurrentUserInfoJsonVO : public JsonVO<CurrentUserInfoDTO::Wrapper>
{
	DTO_INIT(CurrentUserInfoJsonVO, JsonVO<CurrentUserInfoDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif
