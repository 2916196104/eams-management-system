#pragma once

#include "../../GlobalInclude.h"
#include "domain/dto/StudentRecord/StlistDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)
//显示jsonVO，用于响应给客户端的json对象
class StlistJsonVO :public JsonVO<StlistDTO::Wrapper>
{
	DTO_INIT(StlistJsonVO, JsonVO<StlistDTO::Wrapper>);
};

//分页展示JsonVO
class StlistPageJsonVO :public JsonVO<StlistPageDTO::Wrapper>
{
	DTO_INIT(StlistPageJsonVO, JsonVO<StlistPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)		
