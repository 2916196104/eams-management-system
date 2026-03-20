#pragma once
#ifndef _SELECTCLASSDTO_H_
#define _SELECTCLASSDTO_H_
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
*班级数据传输对象
*/
class SelectClassDTO : public oatpp::DTO
{
	DTO_INIT(SelectClassDTO, DTO);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("select_class.id"));
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("select_class.name"), true);
};

/**
*班级分页数据传输对象
*/
class SelectClassPageDTO : public PageDTO<SelectClassDTO::Wrapper>
{
	DTO_INIT(SelectClassPageDTO, PageDTO<SelectClassDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif

