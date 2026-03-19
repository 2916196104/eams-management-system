#pragma once
#include"../../GlobalInclude.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class SchedulingVO : public oatpp::DTO {

    DTO_INIT(SchedulingVO, DTO);

public:
    //≈≈øŒid
    API_DTO_FIELD(Int64, scheduleId, ZH_WORDS_GETTER("schedule.field.schedulingId"), true, 1001);
    //∑¥¿°–≈œ¢
    API_DTO_FIELD(String, message, ZH_WORDS_GETTER("schedule.field.hintMessage"), true, "success");
};

#include OATPP_CODEGEN_END(DTO)