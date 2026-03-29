/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:19:14

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
#include "stdafx.h"
#include "schedulecontroller.h"
#include "service/schedule/AppointmentService.h"
#include "service/schedule/StudentLeaveService.h"
#include "service/lesson/LessonService.h"

//实现接口执行函数
//家长提交预约申请逻辑
StringJsonVO::Wrapper ScheduleController::execAddAppointment(const ScheduleAppointmentDTO::Wrapper& dto, const PayloadDTO& payload) {
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 基础参数校验 
	std::string errmsg = dto->validate();
	if (errmsg != "") {
		// 如果校验不通过，直接返回错误码 RS_PARAMS_INVALID 和错误信息
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}


	// 核心安全步骤：注入身份令牌
	// 把当前登录用户的 payload（包含真实 userId）塞进 DTO 里，带到 Service 层去
	dto->setPayload(&payload);

	// 执行核心业务逻辑
	AppointmentService service;

	bool isSuccess = service.addAppointment(dto);

	if (isSuccess) {
		jvo->success("预约申请提交成功，请等待老师审核");
	}
	else {
		// 如果由于某些非异常原因失败，返回标准 fail
		jvo->fail("预约申请提交失败，请稍后重试");
	}

	// 5. 响应结果
	return jvo;
}


//家长提交请假申请逻辑 
StringJsonVO::Wrapper ScheduleController::execAddLeave(const ScheduleLeaveDTO::Wrapper& dto, const PayloadDTO& payload) {

	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 基础参数与安全校验 (防空指针、防超长文本)
	std::string errmsg = dto->validate();
	if (errmsg != "") {
		// 校验不通过，直接打回
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	// 注入身份令牌 (极其重要)
	// 把拦截器解密出来的、绝对保真的 payload 塞进 DTO
	dto->setPayload(&payload);

	// 执行核心业务逻辑
	StudentLeaveService service;

	bool isSuccess = service.addLeave(dto);

	if (isSuccess) {
		jvo->success("请假申请提交成功");
	}
	else {
		jvo->fail("请假申请提交失败，请稍后重试");
	}

	// 5. 响应结果
	return jvo;
}

LessonPageJsonVO::Wrapper ScheduleController::execListLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 实例化 Service
	LessonService service;
	auto resultPage = service.listLesson(query, payload);

	// 构造返回对象
	auto jvo = LessonPageJsonVO::createShared();
	jvo->success(resultPage);
	return jvo;
}

// 参数改为 Int64 lessonId，而不是 DTO
StringJsonVO::Wrapper ScheduleController::execSignLesson(const Int64& lessonId, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	if (!lessonId || lessonId <= 0) {
		jvo->init("lessonId invalidate.", RS_PARAMS_INVALID);
		return jvo;
	}

	// 调用 Service
	LessonService service;
	bool isSuccess = service.signLesson(lessonId.getValue(0), payload);

	if (isSuccess) {
		jvo->success(ZH_WORDS_GETTER("lesson.sign.success"));
	}
	else {
		jvo->fail(ZH_WORDS_GETTER("lesson.sign.fail"));
	}

	return jvo;
}