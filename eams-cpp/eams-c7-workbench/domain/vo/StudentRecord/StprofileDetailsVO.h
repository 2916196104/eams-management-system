#pragma once

#include"../../GlobalInclude.h"
#include"../../dto/StudentRecord/StprofileDetailsDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//传输对象  StprofileDetailsDTO  的 jsonvo
class StprofileDetailsJsonVO :public JsonVO<StprofileDetailsDTO::Wrapper>
{
	DTO_INIT(StprofileDetailsJsonVO, JsonVO<StprofileDetailsDTO::Wrapper>)
};

//分页对象
class StprofileDetailsPageJsonVO :public JsonVO<StprofileDetailsPageDTO::Wrapper>
{
	DTO_INIT(StprofileDetailsPageJsonVO, JsonVO<StprofileDetailsPageDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)