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
	API_DTO_FIELD_REQUIRE(UInt64, lessonId, ZH_WORDS_GETTER("schedule.appointment.scheduleId"), true);
	//预约学生ID
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("schedule.appointment.studentId"), true);
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		// 1. 校验预约课次 ID
		// !scheduleId 检查前端有没有传这个字段
		// scheduleId.getValue(0) <= 0 检查传过来的数值是不是非法
		if (!lessonId || lessonId.getValue(0) <= 0) {
			return "预约课次ID(scheduleId)无效或不能为空！";
		}

		// 2. 校验预约学生 ID
		if (!studentId || studentId.getValue(0) <= 0) {
			return "预约学生ID(studentId)无效或不能为空！";
		}

		// 3. 所有基础规则通过，返回空字符串表示“放行”
		return "";
	}
};

/**
 * 定义一个课表请假请求数据传输类型
 */
class ScheduleLeaveDTO : public oatpp::DTO {
    DTO_INIT(ScheduleLeaveDTO, DTO);

    // 请假课次ID
    API_DTO_FIELD_REQUIRE(UInt64, lessonId, ZH_WORDS_GETTER("schedule.leave.scheduleId"), true);
    // 请假学生ID
    API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("schedule.leave.studentId"), true);
    // 请假原因
    API_DTO_FIELD_REQUIRE(String, reason, ZH_WORDS_GETTER("schedule.leave.reason"), true);
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	std::string validate()
	{
		// 1. 校验请假课次 ID
		if (!lessonId || lessonId.getValue(0) <= 0) {
			return "请假课次ID无效或不能为空！ ";
		}

		// 2. 校验请假学生 ID
		if (!studentId || studentId.getValue(0) <= 0) {
			return "请假学生ID无效或不能为空！ ";
		}

		// 3. 校验请假原因 (查空 + 防恶意超长文本)
		if (!reason || reason->empty()) {
			return "请假原因不能为空！ ";
		}
		// 假设数据库 reason 字段最大长度是 255，我们在入口处卡死 200
		if (reason->length() > 200) {
			return "请假原因过长，请精简至200字以内！";
		}

		return "";
	}
};

/**
 * 签到请求传输对象
 */
class SignInDTO : public oatpp::DTO
{
	DTO_INIT(SignInDTO, DTO);

	// 排课ID
	API_DTO_FIELD_REQUIRE(UInt64, lessonId, ZH_WORDS_GETTER("schedule.field.scheduleId"), true);

public:
	// 参数校验逻辑
	std::string validate()
	{
		if (!lessonId || lessonId <= 0) {
			return "scheduleId invalidate.";
		}
		return "";
	}
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_SCHEDULEDTO_H_