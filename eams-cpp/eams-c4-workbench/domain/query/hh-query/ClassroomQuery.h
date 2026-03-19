#pragma once
#ifndef _CLASSROOM_QUERY_
#define _CLASSROOM_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassroomQuery : public PageQuery {
	DTO_INIT(ClassroomQuery, PageQuery);
	// ฝฬสาร๛ณฦ
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("classroom.field.name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif