#pragma once
#ifndef _CURRENT_USER_DTO_H_
#define _CURRENT_USER_DTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CurrentUserInfoDTO : public oatpp::DTO
{
	DTO_INIT(CurrentUserInfoDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("workbench-he.current-user.field.id"));
	API_DTO_FIELD_DEFAULT(String, username, ZH_WORDS_GETTER("workbench-he.current-user.field.username"));
	API_DTO_FIELD_DEFAULT(List<String>, authorities, ZH_WORDS_GETTER("workbench-he.current-user.field.authorities"));
public:
	CurrentUserInfoDTO()
	{
		authorities = {};
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif
