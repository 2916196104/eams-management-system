#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:08:56

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
#ifndef _CLASS_STUDENT_SERVICE_
#define _CLASS_STUDENT_SERVICE_

#include "domain/vo/StudentVO.h"
#include "domain/query/StudentQuery.h"
#include "domain/dto/StudentDTO.h"
#include "oatpp/core/Types.hpp"

// 使用 oatpp 命名空间中的类型
using oatpp::UInt64;

/**
 * 班级学员服务类
 */
class ClassStudentService
{
public:
    // ==================== 获取班级学员列表（分页） ====================
    ClassStudentPageDTO::Wrapper getClassStudentList(const ClassStudentListQuery::Wrapper& query);

    // ==================== 获取班级学员详情 ====================
    // 通过学员ID查询单个学员详情
    StudentDetailDTO::Wrapper getStudentDetail(const UInt64& studentId);

    // ==================== 获取班级学员课程列表（分页） ====================
    StudentCoursePageDTO::Wrapper getStudentCourseList(const StudentCourseListQuery::Wrapper& query);
};

#endif // !_CLASS_STUDENT_SERVICE_