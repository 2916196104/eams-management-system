#pragma once
#ifndef _PARENTACCOUNTVO_H_
#define _PARENTACCOUNTVO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ParentAccountChangeJsonVO : public JsonVO<oatpp::String> {
	DTO_INIT(ParentAccountChangeJsonVO, JsonVO<oatpp::String>);
};

class ParentPasswordChangeJsonVO : public JsonVO<oatpp::String> {
	DTO_INIT(ParentPasswordChangeJsonVO, JsonVO<oatpp::String>);
};


#include OATPP_CODEGEN_END(DTO)


#endif
