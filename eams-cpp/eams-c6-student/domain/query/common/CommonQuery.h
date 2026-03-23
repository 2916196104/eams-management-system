#pragma once
#ifndef COMMOMQUERY_H
#define COMMONQUERY_H
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class RegistrationPageQuery :public PageQuery {
	DTO_INIT(RegistrationPageQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("common.field.student.id"));
};
#include OATPP_CODEGEN_END(DTO)
#endif