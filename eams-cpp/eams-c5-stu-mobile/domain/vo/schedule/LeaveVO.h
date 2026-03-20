#pragma once
#ifndef _LEAVE_VO_
#define  _LEAVE_VO_
#include"../../dto/schedule/LeaveDTO.h"
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class LeaveJsonVO : public JsonVO<LeaveDTO::Wrapper> {
	DTO_INIT(LeaveJsonVO, JsonVO<LeaveDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif // !_LEAVE_VO_
