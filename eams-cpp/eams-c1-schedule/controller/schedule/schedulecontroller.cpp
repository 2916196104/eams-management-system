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
// 家长提交预约申请逻辑
StringJsonVO::Wrapper ScheduleController::execAddAppointment(const ScheduleAppointmentDTO::Wrapper& dto, const PayloadDTO& payload) {
	auto jvo = StringJsonVO::createShared();

	std::string errmsg = dto->validate();
	if (errmsg != "") {
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	dto->setPayload(&payload);

	AppointmentService service;

	try {
		bool isSuccess = service.addAppointment(dto);

		if (isSuccess) {
			jvo->success(u8"预约申请提交成功，请等待老师审核");
		}
		else {
			jvo->fail(u8"预约申请提交失败，请稍后重试");
		}
	}
	catch (const std::runtime_error& e) {

		jvo->fail(e.what());
	}
	catch (const std::exception& e) {
		jvo->fail(e.what());
	}

	return jvo;
}

// 家长提交请假申请逻辑 
StringJsonVO::Wrapper ScheduleController::execAddLeave(const ScheduleLeaveDTO::Wrapper& dto, const PayloadDTO& payload) {
	auto jvo = StringJsonVO::createShared();

	std::string errmsg = dto->validate();
	if (errmsg != "") {
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	dto->setPayload(&payload);

	StudentLeaveService service;

	try {
		bool isSuccess = service.addLeave(dto);

		if (isSuccess) {
			jvo->success(u8"请假申请提交成功");
		}
		else {
			jvo->fail(u8"请假申请提交失败，请稍后重试");
		}
	}
	catch (const std::runtime_error& e) {
		// 这样才能捕捉到 addLeave 抛出的异常
		jvo->fail(e.what());
	}
	catch (const std::exception& e) {
		jvo->fail(e.what());
	}

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