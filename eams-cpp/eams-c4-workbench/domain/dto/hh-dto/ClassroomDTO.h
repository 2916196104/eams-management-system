#pragma once

#ifndef _CLASSROOM_DTO_
#define _CLASSROOM_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassroomDTO : public oatpp::DTO {
	DTO_INIT(ClassroomDTO, DTO);
	// 教室唯一ID
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("classroom.field.id"));
	// 教室名称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("classroom.field.name"));
	// 教室地点
	API_DTO_FIELD_DEFAULT(String, address, ZH_WORDS_GETTER("classroom.field.position"));
};

class ClassroomPageDTO : public PageDTO<ClassroomDTO::Wrapper> {
	DTO_INIT(ClassroomPageDTO, PageDTO<ClassroomDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif