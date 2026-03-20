#pragma once
#ifndef _MONTHLYDATADTO_H_
#define _MONTHLYDATADTO_H_
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
*班级数据传输对象
*/
class MonthlyDataDTO : public oatpp::DTO
{
	DTO_INIT(MonthlyDataDTO, DTO);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("select_teacher.id"));
	API_DTO_FIELD_REQUIRE(UInt64, class_count, ZH_WORDS_GETTER("monthly_data.monthly_class_count"), true);
	API_DTO_FIELD_REQUIRE(UInt64, checkin_count, ZH_WORDS_GETTER("monthly_data.monthly_check-in_count"), true);
	API_DTO_FIELD_REQUIRE(UInt64, registration_amount, ZH_WORDS_GETTER("monthly_data.monthly_registration_amount"), true);
	API_DTO_FIELD_REQUIRE(UInt64, new_students, ZH_WORDS_GETTER("monthly_data.new_monthly_students"), true);
};

/**
*班级分页数据传输对象
*/
class MonthlyDataPageDTO : public PageDTO<MonthlyDataDTO::Wrapper>
{
	DTO_INIT(MonthlyDataPageDTO, PageDTO<MonthlyDataDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif

