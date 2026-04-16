#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

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
#ifndef _GETCLASSSTUDENTDETAILSCONTROLLER_
#define _GETCLASSSTUDENTDETAILSCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/GlobalInclude.h"
#include "../nacos-register/Macros.h"
#include "domain/vo/StudentVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("class.student.details.tag")

/**
 * 获取班级学员详情控制器
 */
class GetClassStudentDetailsController : public oatpp::web::server::api::ApiController
{
    // 添加访问定义
    API_ACCESS_DECLARE(GetClassStudentDetailsController);

public:
    // 定义获取班级学员详情接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("class.get-class-student-details"), // 接口标题
        getClassStudentDetails,                                      // 接口方法名
        StudentDetailJsonVO::Wrapper,                                // 响应类型
        API_TAG,                                                     // 接口标签
        API_DEF_ADD_PATH_PARAMS(String, "studentId", ZH_WORDS_GETTER("class.field.studentId"), "sample_student_id", true);
    );

    // 定义获取班级学员详情接口端点
    // 定义获取班级学员详情接口端点
    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,                                    // 请求方法
        "/c7-class/class/GetClassStudentDetails/{studentId}", // 请求路径 ← 添加了 {studentId}
        getClassStudentDetails,                       // 接口方法名
        PATH(String, studentId, "studentId"),         // 路径参数
        executeGetClassStudentDetails(studentId, authObject->getPayload())  // 执行方法
    );

private:
    // 获取班级学员详情执行方法
    StudentDetailJsonVO::Wrapper executeGetClassStudentDetails(const String& studentId, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _GETCLASSSTUDENTDETAILSCONTROLLER_