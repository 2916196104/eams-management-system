#pragma once 
#ifndef _REPEATEDSCHEDULINGVO_H_
#define _REPEATEDSCHEDULINGVO_H_
#include"ServerInfo.h"
#include"Macros.h"
#include"../../GlobalInclude.h"
#include"../../dto/makabaka-dto/RepeatedSchedulingDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class RepeatedSchedulingVO : public JsonVO<RepeatedSchedulingDTO::Wrapper> {
	DTO_INIT(RepeatedSchedulingVO, JsonVO<RepeatedSchedulingDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_REPEATEDSCHEDULINGVO_H_