#pragma once
#ifndef _SCHEDULE_DTO_H
#define _SCHEDULE_DTO_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 签到请求传输对象
 */
class SignInDTO : public oatpp::DTO
{
	DTO_INIT(SignInDTO, DTO);

	// 排课ID
	API_DTO_FIELD_REQUIRE(UInt64, scheduleId, ZH_WORDS_GETTER("schedule.field.scheduleId"), true);

public:
	// 参数校验逻辑
	std::string validate()
	{
		if (!scheduleId || scheduleId <= 0) {
			return "scheduleId invalidate.";
		}
		return "";
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SCHEDULE_DTO_H