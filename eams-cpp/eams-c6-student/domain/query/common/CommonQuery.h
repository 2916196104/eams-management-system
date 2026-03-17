#pragma once
#ifndef COMMOMQUERY_H
#define COMMONQUERY_H
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class RegistrationPageQuery :public PageQuery {
	DTO_INIT(RegistrationPageQuery, PageQuery);
};
#include OATPP_CODEGEN_END(DTO)
#endif