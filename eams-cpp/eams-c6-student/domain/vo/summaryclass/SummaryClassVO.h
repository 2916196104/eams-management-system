#pragma once
#ifndef _SUMMARYCLASSVO_H_
#define _SUMMARYCLASSVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/summaryclass/SummaryClassDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 课时汇总分页显示对象
*/
class SummaryClassPageJsonVO : public JsonVO<SummaryClassPageDTO::Wrapper>
{
	DTO_INIT(SummaryClassPageJsonVO, JsonVO<SummaryClassPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif
