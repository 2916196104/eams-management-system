#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

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
#ifndef _SCHEDULECONTROLLER_H_
#define _SCHEDULECONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "../../domain/dto/schedule/scheduleDTO.h"
#include "../../domain/query/schedule/schedulequery.h"
#include "../../domain/vo/schedule/scheduleVO.h"
#include "../../domain/query/lesson/LessonQuery.h"
#include "../../domain/vo/lesson/LessonVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
//课表模块控制器
//定义接口分类标签，通过语言包宏获取
#define API_TAG ZH_WORDS_GETTER("schedule.tag")
class ScheduleController : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(ScheduleController);
public:
    // =======================================================
    // 接口 1：家长提交课程预约申请
    // =======================================================
    // 1 定义新增预约接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("schedule.appointment.summary"),      // 接口标题
        addAppointment,                                      // 端点函数名
        StringJsonVO::Wrapper,                               // 响应数据类型
        API_TAG                                              // Swagger 标签
    );
    // 3.2 定义新增预约接口处理
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/c1schedule/sCenter/lesson/appoint",
        addAppointment,
        BODY_DTO(ScheduleAppointmentDTO::Wrapper, dto),
        execAddAppointment(dto, authObject->getPayload()) // 传递 DTO 和 Payload (通常包含当前用户/家长信息)
    );
    // =======================================================
    // 接口 2：家长提交课程请假申请
    // =======================================================
    // 3.1 定义新增请假接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("schedule.leave.summary"),
        addLeave,
        StringJsonVO::Wrapper,
        API_TAG
    );
    // 3.2 定义新增请假接口处理
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/c1schedule/sCenter/lesson/leave",
        addLeave,
        BODY_DTO(ScheduleLeaveDTO::Wrapper, dto),
        execAddLeave(dto, authObject->getPayload())
    );

    // 获取课表列表 (GET)
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("lesson.list.summary"), listLesson, LessonQuery, LessonPageJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c1schedule/sCenter/lesson/list", listLesson, LessonQuery, execListLesson(query, authObject->getPayload()));

    // 学生签到 (POST) - 改用 PATH 参数定义
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("lesson.sign.summary"),
        signLesson,
        StringJsonVO::Wrapper,
        API_TAG,
        API_DEF_ADD_PATH_PARAMS(Int64, "lessonId", ZH_WORDS_GETTER("lesson.field.id"), 1, true);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/c1schedule/sCenter/lesson/sign/{lessonId}",
        signLesson,
        PATH(Int64, lessonId), // 从 URL 路径中提取 lessonId
        execSignLesson(lessonId, authObject->getPayload())
    );
private: // 定义接口执行函数
    // 3.3 家长提交预约申请逻辑
    StringJsonVO::Wrapper execAddAppointment(const ScheduleAppointmentDTO::Wrapper& dto, const PayloadDTO& payload);

    // 3.3 家长提交请假申请逻辑
    StringJsonVO::Wrapper execAddLeave(const ScheduleLeaveDTO::Wrapper& dto, const PayloadDTO& payload);
    
    LessonPageJsonVO::Wrapper execListLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload);
    StringJsonVO::Wrapper execSignLesson(const Int64& lessonId, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_SCHEDULECONTROLLER_H_