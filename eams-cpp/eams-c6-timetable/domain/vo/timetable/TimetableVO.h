#pragma once
#ifndef TIMETABLEVO_H
#define TIMETABLEVO_H
#include "domain/GlobalInclude.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//响应预约的信息
class ReserveVO : public JsonVO<ReserveDTO::Wrapper>
{
    DTO_INIT(ReserveVO, JsonVO<ReserveDTO::Wrapper>);
};

//响应请假的信息
class LeaveVO : public JsonVO<LeaveDTO::Wrapper>
{
    DTO_INIT(LeaveVO, JsonVO < LeaveDTO::Wrapper>);

};


#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLEVO_H