#pragma once
#ifndef TIME_TABLEVO_H
#define TIME_TABLEVO_H
#include "../../GlobalInclude.h"
#include ".././../dto/timetable/TimetableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//分页显示课表情况
class TimetablePageVO : public PageDTO<TimetableDTO::Wrapper>
{
    DTO_INIT(TimetablePageVO, PageDTO<TimetableDTO::Wrapper>);
};


using TimetablePageJsonVO = JsonVO<TimetablePageVO::Wrapper>;
#include OATPP_CODEGEN_END(DTO)
#endif // TIME_TABLEVO_H