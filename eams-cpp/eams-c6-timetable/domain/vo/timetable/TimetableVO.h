#pragma once
#ifndef TIMETABLEVO_H
#define TIMETABLEVO_H
#include "domain/GlobalInclude.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 获取按天课表响应
 */
class TimetableVO : public JsonVO<TimetableListDTO::Wrapper>
{
    DTO_INIT(TimetableVO, JsonVO<TimetableListDTO::Wrapper>);
};

/**
 * 获取按月课表计数响应
 */
class TimetableMonthVO : public JsonVO<TimetableMonthDTO::Wrapper>
{
    DTO_INIT(TimetableMonthVO, JsonVO<TimetableMonthDTO::Wrapper>);
};

/**
 * 通用动作响应
 * 签到/预约/请假复用
 */
class TimetableActionVO : public JsonVO<TimetableActionResultDTO::Wrapper>
{
    DTO_INIT(TimetableActionVO, JsonVO<TimetableActionResultDTO::Wrapper>);
};

// 为了兼容Controller里的命名，保留这些别名VO
/**
 * 预约响应
 */
class ReserveVO : public JsonVO<TimetableActionResultDTO::Wrapper>
{
    DTO_INIT(ReserveVO, JsonVO<TimetableActionResultDTO::Wrapper>);
};

/**
 * 请假响应
 */
class LeaveVO : public JsonVO<TimetableActionResultDTO::Wrapper>
{
    DTO_INIT(LeaveVO, JsonVO<TimetableActionResultDTO::Wrapper>);
};

/**
 * 签到响应
 */
class TimetableSignVO : public JsonVO<TimetableSignResultDTO::Wrapper>
{
    DTO_INIT(TimetableSignVO, JsonVO<TimetableSignResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLEVO_H