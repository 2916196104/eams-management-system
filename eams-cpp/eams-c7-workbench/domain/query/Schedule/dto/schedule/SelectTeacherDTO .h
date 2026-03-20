#pragma once
#ifndef _SELECTTEACHERDTO_H_
#define _SELECTTEACHERDTO_H_
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
*班级数据传输对象
*/
class SelectTeacherDTO : public oatpp::DTO
{
	DTO_INIT(SelectTeacherDTO, DTO);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("select_teacher.id"));
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("select_teacher.name"), true);
};

/**
*班级分页数据传输对象
*/
class SelectTeacherPageDTO : public PageDTO<SelectTeacherDTO::Wrapper>
{
	DTO_INIT(SelectTeacherPageDTO, PageDTO<SelectTeacherDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif

