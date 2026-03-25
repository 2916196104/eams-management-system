#pragma once
#include "oatpp/core/Types.hpp"
#include "../lib-oatpp/include/ApiHelper.h"
#include "oatpp/core/macro/codegen.hpp"
#include "domain/dto/manual/ManualDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// JsonVO是模板类，包装任意数据类型

//帮助列表信息响应的VO
class UsageGuideJsonVO : public JsonVO<UsageListDTO::Wrapper> {
	DTO_INIT(UsageGuideJsonVO, JsonVO<UsageListDTO::Wrapper>);
};

//帮助列表中某一数据详细信息响应的VO
class UsageDetailJsonVO : public JsonVO<UsageGuideDetailDto::Wrapper> {
	DTO_INIT(UsageDetailJsonVO, JsonVO<UsageGuideDetailDto::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)