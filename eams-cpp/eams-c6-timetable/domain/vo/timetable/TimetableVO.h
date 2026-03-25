#pragma once
#ifndef TIMETABLEVO_H
#define TIMETABLEVO_H
#include "domain/GlobalInclude.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 获取课表响应
 */
class TimetableVO : public JsonVO<TimetableListDTO::Wrapper>
{
    DTO_INIT(TimetableVO, JsonVO<TimetableListDTO::Wrapper>);
};

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

// 响应签到的信息
class TimetableSignVO : public JsonVO<TimetableSignDTO::Wrapper>
{
    DTO_INIT(TimetableSignVO, JsonVO<TimetableSignDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLEVO_H