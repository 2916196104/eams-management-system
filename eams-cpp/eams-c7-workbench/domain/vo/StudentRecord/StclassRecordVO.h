#pragma once

#include"../../GlobalInclude.h"
#include"../../dto/StudentRecord/StclassRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StclassRecordJsonVO :public JsonVO<StclassRecordDTO::Wrapper>
{
	DTO_INIT(StclassRecordJsonVO, JsonVO<StclassRecordDTO::Wrapper>);
};

class StclassRecordPageJsonVO :public JsonVO<StclassRecordPageDTO::Wrapper>
{
	DTO_INIT(StclassRecordPageJsonVO, JsonVO<StclassRecordPageDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
