#pragma once
#ifndef _PARENT_ACCOUNT_VO_H_
#define _PARENT_ACCOUNT_VO_H_

#include "domain/GlobalInclude.h"
#include "domain/vo/JsonVO.h"
#include "domain/dto/PageDTO.h"
#include "domain/dto/parentaccount/ParentAccountDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 家长账号分页列表响应对象
 */
using ParentAccountPageDTO = PageDTO<ParentAccountDTO::Wrapper>::Wrapper ;
class ParentAccountPageJsonVO : public JsonVO<ParentAccountPageDTO>
{
	DTO_INIT(ParentAccountPageJsonVO, JsonVO<ParentAccountPageDTO>);
};
class ParentAccountChangeJsonVO : public JsonVO<oatpp::String> {
	DTO_INIT(ParentAccountChangeJsonVO, JsonVO<oatpp::String>);
};

class ParentPasswordChangeJsonVO : public JsonVO<oatpp::String> {
	DTO_INIT(ParentPasswordChangeJsonVO, JsonVO<oatpp::String>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PARENT_ACCOUNT_VO_H_
