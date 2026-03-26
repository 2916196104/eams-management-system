#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _SCHEDULEDTO_H_
#define _SCHEDULEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个课表预约请求的数据传输类型
 */
class ScheduleAppointmentDTO : public oatpp::DTO {
	DTO_INIT(ScheduleAppointmentDTO, DTO);
	//预约课次ID
	API_DTO_FIELD_REQUIRE(UInt64, scheduleId, ZH_WORDS_GETTER("schedule.appointment.scheduleId"), true);
	//预约学生ID
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("schedule.appointment.studentId"), true);

};

/**
 * 定义一个课表请假请求数据传输类型
 */
class ScheduleLeaveDTO : public oatpp::DTO {
    DTO_INIT(ScheduleLeaveDTO, DTO);

    // 请假课次ID
    API_DTO_FIELD_REQUIRE(UInt64, scheduleId, ZH_WORDS_GETTER("schedule.leave.scheduleId"), true);
    // 请假学生ID
    API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("schedule.leave.studentId"), true);
    // 请假原因
    API_DTO_FIELD_REQUIRE(String, reason, ZH_WORDS_GETTER("schedule.leave.reason"), true);
};

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

#endif // !_SCHEDULEDTO_H_