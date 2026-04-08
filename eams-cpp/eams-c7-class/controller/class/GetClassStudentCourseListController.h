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
#ifndef _GETCLASSSTUDENTCOURSELISTCONTROLLER_
#define _GETCLASSSTUDENTCOURSELISTCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/GlobalInclude.h"
#include "../nacos-register/Macros.h"
#include "domain/query/StudentQuery.h"
#include "domain/vo/StudentVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("class.student.course.list.tag")

/**
 * 获取学员课程列表控制器
 */
class GetClassStudentCourseListController : public oatpp::web::server::api::ApiController
{
    // 添加访问定义
    API_ACCESS_DECLARE(GetClassStudentCourseListController);

public:
    // 定义获取学员课程列表接口描述（分页查询+条件查询）
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("class.get-student-course-list"), // 接口标题
        getStudentCourseList,                                      // 接口方法名
        StudentCourseListQuery,                                    // 查询参数类型
        StudentCoursePageJsonVO::Wrapper,                          // 响应类型
        API_TAG                                                    // 接口标签
    );

    // 定义获取学员课程列表接口端点
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,                                 // 请求方法
        "/c7-class/class/GetClassStudentCourseList",       // 请求路径
        getStudentCourseList,                      // 接口方法名
        StudentCourseListQuery,                    // 查询参数类型
        executeGetStudentCourseList(query, authObject->getPayload())  // 执行方法
    );

private:
    // 获取学员课程列表执行方法
    StudentCoursePageJsonVO::Wrapper executeGetStudentCourseList(const StudentCourseListQuery::Wrapper& query, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _GETCLASSSTUDENTCOURSELISTCONTROLLER_