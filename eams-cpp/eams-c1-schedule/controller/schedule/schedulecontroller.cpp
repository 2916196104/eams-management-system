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
//实现接口执行函数
//家长提交预约申请逻辑
StringJsonVO::Wrapper ScheduleController::execAddAppointment(const ScheduleAppointmentDTO::Wrapper& dto, const PayloadDTO& payload) {

    // 包装并返回成功响应
    auto jvo = StringJsonVO::createShared();
    jvo->success("预约申请提交成功，请等待老师审核");

    return jvo;
}


//家长提交请假申请逻辑 
StringJsonVO::Wrapper ScheduleController::execAddLeave(const ScheduleLeaveDTO::Wrapper& dto, const PayloadDTO& payload) {

    // 包装并返回成功响应
    auto jvo = StringJsonVO::createShared();
    jvo->success("请假申请提交成功");

    return jvo;
}