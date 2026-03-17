#pragma once
#ifndef _PARENTACCOUNTDTO_H_
#define _PARENTACCOUNTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ParentAccountChangeDTO : public oatpp::DTO
{
	DTO_INIT(ParentAccountChangeDTO, DTO);

	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("ParentAccountChange.field.id"), true);

	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("ParentAccountChange.field.name"), true);

	API_DTO_FIELD_REQUIRE(Int32, state, ZH_WORDS_GETTER("ParentAccountChange.field.state"), true);
};

class ParentPasswordChangeDTO : public oatpp::DTO
{
	DTO_INIT(ParentPasswordChangeDTO, DTO);

	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("ParentPasswordChange.field.id"), true);

	API_DTO_FIELD_REQUIRE(String, oldPassword, ZH_WORDS_GETTER("ParentPasswordChange.field.oldPassword"), true);

	API_DTO_FIELD_REQUIRE(String, newPassword, ZH_WORDS_GETTER("ParentPasswordChange.field.newPassword"), true);
};


#include OATPP_CODEGEN_END(DTO)


#endif
